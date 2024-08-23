//#include <TXLib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <assert.h>


struct params_eq
{
    double a = NAN;
    double b = NAN;
    double c = NAN;
};


struct ans_eq
{
    bool is_linear = false;
    int roots_numb = -1;
    double x1 = NAN;
    double x2 = NAN;
};


void solver_quad_equation();
void entering_values(struct params_eq* const coefficients);
void cleaning_buffer();
int def_quantity(const struct params_eq coefficients, const struct ans_eq* const solutions, const double disc);
double calc_disc(const struct params_eq coefficients);
bool compare_doubles(const double num1, const double num2);
void calculations(const struct params_eq coefficients, struct ans_eq* const solutions, const double disc);
void print_solutions(const struct params_eq coefficients, struct ans_eq solutions);
void is_eq_linear(const struct params_eq coefficients, struct ans_eq* const solutions);
void sort_roots(struct ans_eq* const solutions);
double zero_mistake(const double x);
void next_eq(int* const selector);


const double EPSILON = 1e-9;
const char NAME_COEFFICIENTS[] = "abc";
enum roots
{
    NO_ROOT = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2,
    INF_ROOTS = 3,
};


int main()
{
    setlocale(LC_ALL, "Russian");
    int selector = -1;
    do
    {
        solver_quad_equation(); /*Главная функция по решению квадратных уравнений*/
        next_eq(&selector); /*Функция перехода к следующему уравнению*/
    } while (selector);
    printf("Конец программы!");
    return 0;
}


//Главная функция по решению квадратных уравнений
void solver_quad_equation()
{
    struct params_eq coefficients;
    struct ans_eq solutions;
    entering_values(&coefficients); /*Ввод коэффициентов*/
    is_eq_linear(coefficients, &solutions); /*Считать ли дискриминант???*/
    double disc = NAN;
    if (!(solutions.is_linear))
        disc = calc_disc(coefficients); /*Вычисление дискриминанта*/
    solutions.roots_numb = def_quantity(coefficients, &solutions, disc); /*Определение количества решений*/
    calculations(coefficients, &solutions, disc); /*Вычисление корней уравнения*/
    print_solutions(coefficients, solutions); /*Вывод ответа*/
}


//Ввод коэффициентов
void entering_values(struct params_eq* const coefficients)
{
    assert(coefficients != NULL);

    double* values_coefficients[3] = { &((*coefficients).a), &((*coefficients).b), &((*coefficients).c) };
    for (int i = 0; i < 3; i++)
    {
        char tmp = 0;
        int res = 0;
        do
        {
            printf("Введите коэффициент %c: ", NAME_COEFFICIENTS[i]);
            res = scanf_s("%lf%c", values_coefficients[i], &tmp);
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
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}


//Определение количества решений
int def_quantity(const struct params_eq coefficients, const struct ans_eq* const solutions, const double disc)
{
    assert(solutions != NULL);

    if ((*solutions).is_linear)
    {
        if (compare_doubles(coefficients.b, 0) && compare_doubles(coefficients.c, 0))
            return INF_ROOTS;
        else if (compare_doubles(coefficients.b, 0) && !(compare_doubles(coefficients.c, 0)))
            return NO_ROOT;
        else
            return ONE_ROOT;
    }
    else
    {
        assert(isfinite(disc));

        if (disc > 0)
            return TWO_ROOTS;
        if (disc < 0)
            return NO_ROOT;
        else
            return ONE_ROOT;
    }
}


//Вычисление дискриминанта
double calc_disc(const struct params_eq coefficients)
{
    return coefficients.b * coefficients.b - 4 * coefficients.a * coefficients.c;
}


//Сравнение чисел с плавающей точкой (Если числа равны, то возвращается 1)
bool compare_doubles(const double num1, const double num2)
{
    assert(isfinite(num1) && isfinite(num2));

    return (fabs(num1 - num2) < EPSILON);
}


//Вычисление корней уравнения
void calculations(const struct params_eq coefficients, struct ans_eq* const solutions, const double disc)
{
    assert(solutions != NULL);

    switch ((*solutions).roots_numb)
    {
    case ONE_ROOT:
        if ((*solutions).is_linear)
            (*solutions).x1 = ((-1) * coefficients.c) / coefficients.b;
        else
            (*solutions).x1 = ((-1) * coefficients.b) / (2 * coefficients.a);
        break;
    case TWO_ROOTS:
        assert(isfinite(disc));

        const double sqrt_disc = sqrt(disc);
        (*solutions).x1 = ((-1) * coefficients.b - sqrt_disc) / (2 * coefficients.a);
        (*solutions).x2 = ((-1) * coefficients.b + sqrt_disc) / (2 * coefficients.a);
        break;
    }
}


//Вывод ответа
void print_solutions(const struct params_eq coefficients, struct ans_eq solutions)
{
    if (solutions.is_linear)
        printf("Это линейное уравнение!\n");
    else
        printf("Это квадратное уравнение!\n");
    switch (solutions.roots_numb)
    {
    case NO_ROOT:
        printf("Количество решений - 0.\n");
        break;
    case INF_ROOTS:
        printf("Количество решений - INF.\n");
        break;
    case ONE_ROOT:
        solutions.x1 = zero_mistake(solutions.x1);
        printf("Количество решений - 1.\n");
        printf("x = %lf\n", solutions.x1);
        break;
    case TWO_ROOTS:
        solutions.x1 = zero_mistake(solutions.x1);
        solutions.x2 = zero_mistake(solutions.x2);
        sort_roots(&solutions);
        printf("Количество решений - 2.\n");
        printf("x1 = %lf\nx2 = %lf\n", solutions.x1, solutions.x2);
        break;
    }
}


//Считать ли дискриминант???
void is_eq_linear(const struct params_eq coefficients, struct ans_eq* const solutions)
{
    assert(solutions != NULL);

    if (compare_doubles(coefficients.a, 0))
        (*solutions).is_linear = 1;
    else
        (*solutions).is_linear = 0;
}


//Функция для вывода от меньшего к большего
void sort_roots(struct ans_eq* const solutions)
{
    assert(solutions != NULL);

    if ((*solutions).x1 > (*solutions).x2)
    {
        double tmp = (*solutions).x1;
        (*solutions).x1 = (*solutions).x2;
        (*solutions).x2 = tmp;
    }
}


//Проверка на ошибку с нулём
double zero_mistake(const double x)
{
    assert(isfinite(x));

    if (compare_doubles(x, 0))
        return fabs(x);
    else
        return x;
}


//Функция перехода к следующему уравнению
void next_eq(int* const selector)
{
    char tmp = 0;
    const int flag = 1;
    int res = 0;
    do
    {
        printf("\nХотите ли вы ввести новое уравнене? (1 - Да, 0- Нет) - ");
        res = scanf_s("%d%c", selector, &tmp);
        if (!(tmp == '\n' && ((*selector) == 0 || (*selector) == 1)))
            printf("Ошибка!\nМожно вводить 0 или 1.\n");
        if (res != 2)
            cleaning_buffer();
    } while (tmp != '\n' || res != 2 || (*selector != 1 && *selector != 0));
    printf("\n");
}
