//#include <TXLib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>


void entering_values(double values_coefficients[3]);
void cleaning_buffer();
void print_type_equation(double values_coefficients[3]);
void print_def_quantity(double values_coefficients[3]);
double calc_disc(double values_coefficients[3]);
bool compare_doubles(double num1, double num2);
void calculations(double values_coefficients[3], int det, double solutions[2]);


const double EPSILON = 1e-9;
const char name_coefficients[] = "abc";
const int one_root = 1;
const int two_roots = 2;


//Основная программа
int main()
{
    setlocale(LC_ALL, "Russian");
    double values_coefficients[3];
    entering_values(values_coefficients);
    print_type_equation(values_coefficients);
    print_def_quantity(values_coefficients);
    //    for (int i = 0; i < 3; i++)
    //    {
    //        printf("%lf ", values_coefficients[i]);
    //    }
    return 0;
}


//Ввод коэффициентов
void entering_values(double values_coefficients[3])
{
    for (int i = 0; i < 3; i++)
    {
        char tmp = 0;
        int res = 0;
        do
        {
            printf("Введите коэффициент %c: ", name_coefficients[i]);
            res = scanf("%lf%c", &values_coefficients[i], &tmp);
            if (tmp != '\n' || res != 2)
            {
                printf("Ошибка!\nМожно вводить только числа.\n");
                cleaning_buffer();
            }
        } while (tmp != '\n' || res != 2);
    }
}


//Очистка буффера ввода
void cleaning_buffer()
{
    int ch = 0;
    while ((ch = getchar()) != '\n') {}
}


//Вывод типа уравнения
void print_type_equation(double values_coefficients[3])
{
    if (values_coefficients[0] == 0)
        printf("Это линейное уравнение!\n");
    else
        printf("Это квадратное уравнение!\n");
}


//Вывод решения
void print_def_quantity(double values_coefficients[3])
{
    double a, b, c;
    double solutions[2];
    a = values_coefficients[0];
    b = values_coefficients[1];
    c = values_coefficients[2];
    double disc = calc_disc(values_coefficients);
    if (a == 0 && b == 0 && c == 0)
        printf("Количество решений - INF.");
    if ((a == 0 && b == 0 && c != 0) || (disc < 0 && a != 0))
        printf("Количество решений - 0.");
    if ((a == 0 && b != 0) || (compare_doubles(disc, 0) && a != 0))
    {
        printf("Количество решений - 1.\n");
        calculations(values_coefficients, one_root, solutions);
        printf("x = %lf", solutions[0]);
    }
    if (disc > 0 && a != 0)
    {
        printf("Количество решений - 2.\n");
        calculations(values_coefficients, two_roots, solutions);
        printf("x1 = %lf\nx2 = %lf", solutions[0], solutions[1]);
    }
}


//Вычисление дискриминанта
double calc_disc(double values_coefficients[3])
{
    double disc = values_coefficients[1] * values_coefficients[1] - 4 * values_coefficients[0] * values_coefficients[2];
    return disc;
}


//Сравнение чисел с плавающей точкой (Если числа равны, то возвращается 1)
bool compare_doubles(double num1, double num2)
{
    if (fabs(num1 - num2) < EPSILON)
        return true;
    else
        return false;
}


//Вычисление корней уравнения
void calculations(double values_coefficients[3], int det, double solutions[2])
{
    switch (det)
    {
    case one_root:
        if (values_coefficients[0] == 0)
            solutions[0] = ((-1) * values_coefficients[2]) / values_coefficients[1];
        else
            solutions[0] = ((-1) * values_coefficients[1]) / (2 * values_coefficients[0]);
        break;
    case two_roots:
        double disc = calc_disc(values_coefficients);
        solutions[0] = ((-1) * values_coefficients[1] - sqrt(disc)) / (2 * values_coefficients[0]);
        solutions[1] = ((-1) * values_coefficients[1] + sqrt(disc)) / (2 * values_coefficients[0]);
        break;
    }
}
