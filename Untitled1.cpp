//#include <TXLib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <windows.h>


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


struct run_tests
{
    double a = NAN;
    double b = NAN;
    double c = NAN;
    double x1 = NAN;
    double x2 = NAN;
    int roots_numb = -1;
};


//Объявление функций программы
void solver_quad_equation();
void entering_values(struct params_eq* const coefficients);
void working_eq(struct params_eq coefficients, struct ans_eq* const solutions);
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
void print_quant_eq(int numb_iter);
void unit_tests();
void transf_data_struc(const struct run_tests data[13], struct params_eq* const test_p, const int num);
bool compare_sol(const double a, const double b);
double round_decimals(const double value);


const double EPSILON = 1e-9;
const char NAME_COEFFICIENTS[] = "abc";
const double MULTIPLIER = 1e5;

enum roots_count
{
    NO_ROOT = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2,
    INF_ROOTS = 3,
};


enum color_codes
{
    RED = 4,
    GREEN = 10,
    WHITE = 15,
};


int main()
{
    setlocale(LC_ALL, "Russian");
    //printf("Хотитие ли вы запустить автоматическое тестирование программы? - (1 - Да, 0- Нет) - ");
    //scanf();
    unit_tests(); /*Функция, тестирующая программу уравнениями*/
    int selector = -1;
    int numb_iter = 0;
    do
    {
        solver_quad_equation(); /*Главная функция по решению квадратных уравнений*/
        next_eq(&selector); /*Функция перехода к следующему уравнению*/
        numb_iter++;
    } while (selector);
    print_quant_eq(numb_iter); /*Вывод количества решённых уравнений*/
    printf("\nКонец программы!");
    return 0;
}


//Главная функция по решению квадратных уравнений
void solver_quad_equation()
{
    struct params_eq coefficients;
    struct ans_eq solutions;
    entering_values(&coefficients); /*Ввод коэффициентов*/
    working_eq(coefficients, &solutions); /*Вычисления для уравнения с уже имеющимися коэффициентами*/
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
            if (/*isnan(*values_coefficients[i]) || isinf(*values_coefficients[i]) ||*/ tmp != '\n')
                printf("Ошибка!\nМожно вводить только числа.\n");
            if ((res != 2 || tmp != '\n') && tmp != 26)
                cleaning_buffer();
        } while (tmp != '\n' || res != 2 /*|| isnan(*values_coefficients[i]) || isinf(*values_coefficients[i])*/);
    }
}


//Вычисления для уравнения с уже имеющимися коэффициентами
void working_eq(struct params_eq coefficients, struct ans_eq* const solutions)
{
    is_eq_linear(coefficients, solutions); /*Считать ли дискриминант???*/
    double disc = NAN;
    if (!((*solutions).is_linear))
        disc = calc_disc(coefficients); /*Вычисление дискриминанта*/
    (*solutions).roots_numb = def_quantity(coefficients, solutions, disc); /*Определение количества решений*/
    calculations(coefficients, solutions, disc); /*Вычисление корней уравнения*/
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
        printf("x1 = %.9lf\nx2 = %lf\n", solutions.x1, solutions.x2);
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
        const double tmp = (*solutions).x1;
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
    assert(selector != NULL);

    char tmp = 0;
    const int flag = 1;
    int res = 0;
    do
    {
        printf("\nХотите ли вы ввести новое уравнене? (1 - Да, 0- Нет) - ");
        res = scanf_s("%d%c", selector, &tmp);
        if (!(tmp == '\n' && ((*selector) == 0 || (*selector) == 1)))
            printf("Ошибка!\nМожно вводить 0 или 1.\n");
        if (res != 2 || tmp!= '\n')
            cleaning_buffer();
    } while (tmp != '\n' || res != 2 || (*selector != 1 && *selector != 0));
    printf("\n");
}


//Вывод количества решённых уравнений
void print_quant_eq(const int numb_iter)
{
    if (numb_iter % 100 >= 11 && numb_iter % 100 <= 19)
        printf("Вы решили %d уравнений!\n", numb_iter);
    else if (numb_iter % 10 == 1)
        printf("Вы решили %d уравнение!\n", numb_iter);
    else if (numb_iter % 10 == 2 || numb_iter % 10 == 3 || numb_iter % 10 == 4)
        printf("Вы решили %d уравнения!\n", numb_iter);
    else
        printf("Вы решили %d уравнений!\n", numb_iter);
}


//Функция, тестирующая программу уравнениями
void unit_tests()
{
    const struct run_tests data[] = {{0, 0, 0, NAN, NAN, INF_ROOTS},
                                {5, 0, 0, 0, NAN, ONE_ROOT},
                                {0, 5, 0, 0, NAN, ONE_ROOT},
                                {0, 0, 5, NAN, NAN, NO_ROOT},
                                {0, 2, 5, -2.5, NAN, ONE_ROOT},
                                {2, 0, 5, NAN, NAN, NO_ROOT},
                                {2, 5, 0, -2.5, 0, TWO_ROOTS},
                                {1, 3, 2, -2, -1, TWO_ROOTS},
                                {1, 2, 1, -1, NAN, ONE_ROOT}, 
                                {1, -5, -7, -1.14005, 6.14005, TWO_ROOTS},
                                {0.2, -0.25, -0.258, -0.67139, 1.92139, TWO_ROOTS}, 
                                {0.582, 0, -0.256, -0.66322, 0.66322, TWO_ROOTS},
                                {2, -0.525, 0.26, NAN, NAN, NO_ROOT} };
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
    {
        struct params_eq test_p;
        struct ans_eq test_a;
        int flag = 0;
        transf_data_struc(data, &test_p, i);
        working_eq(test_p, &test_a);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (test_a.roots_numb == data[i].roots_numb)
            flag++;
        if (compare_sol(test_a.x1, data[i].x1))
            flag++;
        if (compare_sol(test_a.x2, data[i].x2))
            flag++;
        if (flag == 3)
        {
            SetConsoleTextAttribute(hConsole, GREEN);
            printf("Test №%d is successful\n", i + 1);
        }
        else
        {
            SetConsoleTextAttribute(hConsole, RED);
            printf("Test №%d failed\n", i + 1);
        }
        SetConsoleTextAttribute(hConsole, WHITE);
    }
}


//Перенос данных тестов в структуры программы
void transf_data_struc(const struct run_tests data[13], struct params_eq* const test_p, const int num)
{
    assert(test_p != NULL);

    (*test_p).a = data[num].a;
    (*test_p).b = data[num].b;
    (*test_p).c = data[num].c;
}


//Сравнение корней с тестовыми данными
bool compare_sol(const double a, const double b)
{
    if (isnan(a) || isnan(b) || isinf(a) || isinf(b))
        return ((isnan(a) && isnan(b)) || (isinf(a) && isinf(b)));
    else
    {
        assert(isfinite(a) && isfinite(b));

        return compare_doubles(round_decimals(a), round_decimals(b));
    }
}


// Функция для округления числа до заданного количества знаков после запятой
double round_decimals(const double value) 
{
    assert(isfinite(value));

    return round(value * MULTIPLIER) / MULTIPLIER;
}
