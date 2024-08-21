//#include <TXLib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

void entering_values(double mass[3]);
void cleaning_buffer();
//int def_quantity();

#define EPSILON = 1e-9;


//Основная программа
int main ()
{
    setlocale(LC_ALL, "Russian");
    double values_coefficients[3];
    entering_values(values_coefficients);
    for (int i = 0; i < 3; i++)
    {
        printf("%lf ", values_coefficients[i]);
    }
    return 0;
}


//Ввод коэффициентов
void entering_values(double values_coefficients[3])
{
    char name_coefficients[] = "abc";
    for (int i = 0; i < 3; i++)
    {
        char tmp;
        int res;
        while (tmp != '\n' || res != 2)
        {
            printf("Введите коэффициент %c: ", name_coefficients[i]);
            res = scanf("%lf%c", &values_coefficients[i], &tmp);
            if (tmp != '\n' || res != 2)
            {
                printf("Ошибка!\nМожно вводить только числа.\n");
                cleaning_buffer();
            }
        }
        tmp = '\0';
        res = 0;
    }
}


//Очистка буффера ввода
void cleaning_buffer()
{
    int ch = 0;
    while ((ch = getchar()) != '\n') {}
}


//Определение количества решений
//int def_quantity(values_coefficients)
//{
//    double discriminant;
//    int amount = 3;
//    if (a == 0)
//    {
//        printf("Это линейное уравнение!\n");
//        if (b == 0)
//        {
//            if (c == 0)
//            {
//                amount = 3;
//                printf("Количесвто решений - INF.\n");
//            }
//            else
//                amount = 0;
//                printf("Количесвто решений - 0.\n");
//        }
//        else
//            amount = -1;
//            printf("Количесвто решений - 1.\n");
//    }
//    else
//    {
//        printf("Это квадратное уравнение!\n");
//        discriminant = values_coefficients[1] * values_coefficients[1] - 4 * values_coefficients[0] * values_coefficients[2];
//        if (discriminant < 0)
//            amount = 0;
//            printf("Количесвто решений - 0.\n");
//        else if (abs(discriminant - 0) < EPSILON)
//            amount = 1;
//            printf("Количесвто решений - 1.\n");
//        else if (discriminant > 0)
//            amount = 2;
//            printf("Количесвто решений - 2.\n");
//    }
//    return amount;
//}
//
//
//Вычисление решений
//void calculations()
//{
//    double x1, x2;
//    switch(amount)
//    {
//        case -1:
//            x1 = ((-1) * values_coefficients[2]) / values_coefficients[1];
//            printf("x = %lf", x1)
//            break;
//        case 1:
//            x = ((-1) * values_coefficients[1]) / ();
//    }
//}
