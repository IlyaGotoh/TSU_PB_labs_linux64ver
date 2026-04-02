#include <iostream>
using namespace std;

/*
Задан упорядоченный целочисленный массив длины N>>1000.
Значения элементов массива находятся в числовом интервале [0, 17].
А. Напишите функцию с параметрами, которая «упаковывает» данные, т.е. размещает
информацию о числах из массива, используя как можно меньше памяти.
Б. Напишите функцию с параметрами, которая «распаковывает» данные, т.е. по информации,
полученной при выполнении задания А, восстанавливает исходное состояние массива.
*/


int* pack(int *array, int array_len)
{
	int *packed_arr = new int [18];
	int packed_i = 0;
	int count = 1;
	for (int i = 0; i < array_len-1; i++) {
		while (array[i] == array[i+1]) {
			count++;
			i++;
		}
		packed_arr[packed_i] = count;
		count = 1;
		packed_i++;
	}

	return packed_arr;
}

int* unpack(int *packed_arr)
{
	int unpacked_len = 0;
	for (int i = 0; i <= 17; i++) {
		unpacked_len = unpacked_len + packed_arr[i];
	}
	int *unpacked_arr = new int [unpacked_len];

	int unpacked_i = 0;
	for (int i = 0; i <= 17; i++) {
		for (int k = 1; k <= packed_arr[i]; k++) {
			unpacked_arr[unpacked_i] = i;
			unpacked_i++;
		}
	}

	return unpacked_arr;
}

int main(void)
{
	int n = 1000;
	int *array = new int [n];

	int c = 0;
	for (int i = 0; i <= 17; i++) {
		if (n == 0) break;
		for (int k = 56; k > 0; k--) {
			if (c == n) break;
			array[c] = i;
			++c;
		}
	}

	for (int i = 0; i < n; i++)
		printf("%d ", array[i]);
	printf("\n\n");

	int *packed = pack(array, n);
	delete [] array;

	for (int i = 0; i <= 17; i++)
		printf("%d ", packed[i]);
	printf("\n\n");

	int *unpacked = unpack(packed);

	for (int i = 0; i < n; i++)
		printf("%d ", unpacked[i]);
	printf("\n");

	delete [] packed;
	delete [] unpacked;

	return 0;
}
