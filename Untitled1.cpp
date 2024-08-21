//#include <TXLib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

void entering_values(double values_coefficients[3]);
void cleaning_buffer();
int def_quantity(double values_coefficients[3]);
void calculations(double values_coefficients[3], int amount);

const double EPSILON = 1e-9;


//Основная программа
int main()
{
    setlocale(LC_ALL, "Russian");
    double values_coefficients[3];
    entering_values(values_coefficients);
    calculations(values_coefficients, def_quantity(values_coefficients));
//    for (int i = 0; i < 3; i++)
//    {
//        printf("%lf ", values_coefficients[i]);
//    }
    return 0;
}


//Ввод коэффициентов
void entering_values(double values_coefficients[3])
{
    char name_coefficients[] = "abc";
    for (int i = 0; i < 3; i++)
    {
        char tmp = 0;
        int res = 0;
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
int def_quantity(double values_coefficients[3])
{
    double discriminant;
    int amount = 3;
    if (values_coefficients[0] == 0)
    {
        printf("Это линейное уравнение!\n");
        if (values_coefficients[1] == 0)
        {
            if (values_coefficients[2] == 0)
            {
                amount = 3;
                printf("Количесвто решений - INF.\n");
            }
            else
            {
                amount = 0;
                printf("Количесвто решений - 0.\n");
            }
        }
        else
        {
            amount = -1;
            printf("Количесвто решений - 1.\n");
        }
    }
    else
    {
        printf("Это квадратное уравнение!\n");
        discriminant = values_coefficients[1] * values_coefficients[1] - 4 * values_coefficients[0] * values_coefficients[2];
        if (discriminant < 0)
        {
            amount = 0;
            printf("Количесвто решений - 0.\n");

        }
        else if (fabs(discriminant - 0) < EPSILON)
        {
            amount = 1;
            printf("Количесвто решений - 1.\n");
        }
        else if (discriminant > 0)
        {
            amount = 2;
            printf("Количесвто решений - 2.\n");
        }
    }
    return amount;
}


//Вычисление решений и их вывод
void calculations(double values_coefficients[3], int amount)
{
    double x1, x2;
    switch (amount)
    {
    case -1:
        x1 = ((-1) * values_coefficients[2]) / values_coefficients[1];
        printf("x = %lf", x1);
        break;
    case 1:
        x1 = ((-1) * values_coefficients[1]) / (2 * values_coefficients[0]);
        printf("x = %lf", x1);
        break;
    case 2:
        double discriminant = values_coefficients[1] * values_coefficients[1] - 4 * values_coefficients[0] * values_coefficients[2];
        x1 = ((-1) * values_coefficients[1] - sqrt(discriminant)) / (2 * values_coefficients[0]);
        x2 = ((-1) * values_coefficients[1] + sqrt(discriminant)) / (2 * values_coefficients[0]);
        printf("x1 = %lf\n", x1);
        printf("x2 = %lf", x2);
        break;
    }
}
