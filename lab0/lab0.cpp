
#include <iostream>
#include <cmath>
using namespace std;

//test
/*
Напишите программу вычисления значений функции f(x)=sin(x)/x в десяти равноотстоящих друг от друга
точках интервала (0, 4] возможных значений аргумента x.

На входе программы задается начальная точка интервала возможных значений аргумента.
Результаты вычислений выводятся на экран в удобном для чтения виде без использования параметров форматирования.
*/

void sinx_calc(float x)
{
  if (x > 4)
    cout << "Начальное значение аргумента должно быть меньше 4" << endl;
  else
    {
    float step_x = x;
    float eps = {(4 - x) / 10};
    step_x = step_x + eps;
    int i = 0;
    printf("%s\t\t %s\n", "x", "f(x)");
    while (++i <= 10)
      {
        printf("%f\t %f\n", step_x, sin(step_x)/step_x);
        step_x = step_x + eps;
      }
    }
}


/*
Напишите программу вычисления S - суммы N первых чисел Фибоначчи. Вычисления следует проводить,
пока сумма чисел не превысит наперед заданного большого числа MAX.
Реализация с рекурсией НЕ допускается. 

На входе программы задается значение MAX.
Результаты вычислений: значения N и S.
*/

void fib_calc(unsigned int max)
{
  unsigned int sum = 1;
  unsigned int n = 2;
  unsigned int i = 0;
  unsigned int val1 = 0;
  unsigned int val2 = 1;
  while (sum < max)
    {
    i = val1;
    val1 = val2;
    val2 = val2 + i;
    ++n;
    sum = sum + val2;
    }
  cout << "N: " << n << ", S: " << sum << endl; 
}



/*
Напишите программу, которая выводит таблицу ежемесячных платежей по кредиту. Исходные данные
для расчета: сумма кредита, срок в месяцах и процентная ставка. Предполагается, что кредит
возвращается (выплачивается) ежемесячно равными долями. Проценты начисляются ежемесячно на величину долга. 
		
На входе программы задаются сумма кредита, срок и процентная ставка. 
*/

void debt_calc(float debt, int time, float percent)
{
  percent = {percent / time};
  float payment = {debt / time};
  int current_time = 1;
  float current_percent = {debt/100*percent};
  float percent_sum = current_percent;
  printf("-----------------------------------------------------\n");
  printf("%s\t %s\t\t %s\t %s\n", " ", "Долг", "Процент", "Платёж");
  printf("-----------------------------------------------------\n");
  while (current_time <= time)
    {
    printf("%d\t %f\t %f\t %f\n", current_time, debt, current_percent, payment+current_percent);
    debt = {debt - payment};
    current_percent = {debt/100*percent};
    percent_sum += current_percent;
    ++current_time;
    }
  printf("-----------------------------------------------------\n");
  printf("%s %f\n", "Всего процентов:", percent_sum);
}

int main()
{
  setlocale(LC_ALL, "Russian");

  cout << "1)Функция\nНачальное значение аргумента: ";
  float input_var_1;
  cin >> input_var_1;
  sinx_calc(input_var_1);
  
  cout << "\n2)Числа Фибоначчи\nМаксимальное число: ";
  unsigned int input_var_2;
  cin >> input_var_2;
  fib_calc(input_var_2);
  
  cout << "\n3)Кредит\nСумма, срок, процент: ";
  float debt_var;
  int time_var;
  float percent_var;
  scanf("%f %d %f", &debt_var, &time_var, &percent_var);
  debt_calc(debt_var, time_var, percent_var);
  //cout << endl; debt_calc(150000, 12, 14);

  return 0;
}
