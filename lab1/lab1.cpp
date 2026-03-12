#include <iostream>
#include <random>
using namespace std;


/*
1) Напишите 4 варианта алгоритма заполнения каждого из 10-и элементов целочисленного массива
значением квадрата индекса этого элемента. Оформите вывод результатов из заполненного массива,
используя тот же способ адресации, что и при заполнении массива. 
Требования к вариантам:
    1) статический массив, индексная адресация;
    2) статический массив, адресация  с помощью указателя (косвенная адресация);
    3) динамический массив, индексная адресация;
    4) динамический массив, адресация  с помощью указателя (косвенная адресация).
*/

void square_arrays(void)
{
  int array1[9]; // инициализация массива
  printf("%s\n", "статический массив, индексная адресация:");
  for(int i = 0; i < 10; i++) // инициализатор; условие; итерация
    {
      array1[i] = i*i;
      printf("%d ", array1[i]);
    }
  printf("\n");

  printf("%s\n", "статический массив, адресация  с помощью указателя (косвенная адресация):");
  int *array1_pointer = array1; // *pointer = array - имя (адрес) массива в указатель
  for(int i = 0; i < 10; i++)
    {
      *array1_pointer = i*i; // *pointer - обращение к данным по адресу
      printf("%d ", *array1_pointer);
      array1_pointer++; // инкрементация адреса
    }
  printf("\n");

  printf("%s\n", "динамический массив, индексная адресация:");
  int *array2 = new int [9]; // создание объекта (new) и запись адреса в указатель
  for(int i = 0; i < 10; i++)
    {
      array2[i] = i*i;
      printf("%d ", array2[i]);
    }
  delete [] array2; // освобождение памяти
  printf("\n");

  printf("%s\n", "динамический массив, адресация  с помощью указателя (косвенная адресация):");
  array2 = new int [9];
  for(int i = 0; i < 10; i++)
    {
      *array2 = i*i;
      printf("%d ", *array2);
      array2++;
      if (i == 9) array2 = array2 - 10; // delete работает для указателей на массив, т.е.
                                        // в указателе должен быть адрес первого элемента
    }
  delete [] array2;
  printf("\n");
}

/*
Напишите программу, которая объединяет два упорядоченных по возрастанию массива в один, который также должен быть упорядочен по возрастанию. 
Используйте динамические массивы разной длины (для отладки достаточно взять до 15 элементов). 
При объединении используйте оба типа адресации к массивам – индексную и косвенную.

К выходному массиву НЕ нужно применять алгоритм сортировки!
Исходные массивы можно задать начальными значениями / отсортировать алгоритмом / придумать способ заполнения с использованием функции rand() –
как угодно на ваше усмотрение.
*/


void sort_array(int *array, int array_size_index)
{
  int k = 0;

  for (int i = 0; i < array_size_index; i++)
    {
      for (int j = 0; j < array_size_index - i; j++)
        {
          if (array[j] > array[j+1])
            {
              k = array[j];
              array[j] = array[j+1];
              array[j+1] = k;
            }
        }
    }
}


void merge_arrays(void)
{
  int array1_length = 15;
  int array2_length = 16;
  int *array1 = new int [array1_length];
  int *array2 = new int [array2_length];
  
  srand(time(0));
  for (int i = 0; i < array1_length; i++) array1[i] = rand() % 1000;
  sort_array(array1, array1_length - 1);
  //for (int i = 0; i < array1_length; i++) printf("%d ", array1[i]);
  //printf("\n");

  srand(time(0)+1);
  for (int i = 0; i < array2_length; i++) array2[i] = rand() % 1000;
  sort_array(array2, array2_length - 1);
  //for (int i = 0; i < array2_length; i++) printf("%d ", array2[i]);
  //printf("\n");

  int merged_length = array1_length + array2_length;
  int *merged_array = new int [merged_length];
  //for (int i = 0; i < merged_length; i++) merged_array[i] = -1;
  //for (int i = 0; i < merged_length; i++) printf("%d ", merged_array[i]);

  int *primary_array;
  int *secondary_array;
  int primary_array_length;
  int secondary_array_length;
  if (array1[0] < array2[0])
    {  
      primary_array = array1;
      secondary_array = array2;
      secondary_array_length = array2_length;
      primary_array_length = array1_length;
    }
  else
    {  
      primary_array = array2;
      secondary_array = array1;
      secondary_array_length = array1_length;
      primary_array_length = array2_length;
    }
  for (int i = 0; i < primary_array_length; i++) printf(" %d", primary_array[i]);
  printf("\n");
  for (int i = 0; i < secondary_array_length; i++) printf(" %d", secondary_array[i]);

  printf("\n");
  for (int i = 0; i < merged_length; i++)
    {
      merged_array[i] = *primary_array;
      for (int j = 0; j < secondary_array_length; j++)
        {
          //printf("prim %d next %d j %d sec %d\n", *primary_array, *(primary_array+1), j, secondary_array[j]);
          if (secondary_array[j] >= *primary_array && secondary_array[j] < *(primary_array+1) || secondary_array[j] >= *primary_array && *(primary_array+1) <= 0)
            {
              i++;
              merged_array[i] = secondary_array[j];
              //printf(" GOT %d \n", secondary_array[j]);
              secondary_array[j] = -1;
            }
        }
      primary_array++;
    }


  printf("\n");
  for (int i = 0; i < array1_length + array2_length; i++) printf("%d ", merged_array[i]);
  printf("\n");
}



int main(void)
{
  square_arrays();
  merge_arrays();
  return 0;
}
