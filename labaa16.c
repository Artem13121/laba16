#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>
#define N 200  // Увеличил размер для вставки

double* full_elements(double* a, int n) {
    double x, dx;
    printf("x dx: ");
    scanf("%lf %lf", &x, &dx);
    for (int i = 0; i < n; i++) {
        a[i] = 5 * x * x * x + 2 * x * x + 15 * x - 6;
        x += dx;
    }
    return a;
}

int put_elements(double* a, int n) {
    for (int i = 0; i < n; i++) printf("%.2f ", a[i]);
    printf("\n");
    return 0;
}

double sum_elements(double* a, int b, int e) {
    double s = 0;
    for (int i = b; i <= e; i++) s += a[i];
    return s;
}

int find_element(double* a, int n, double v) {
    for (int i = 0; i < n; i++)
        if (fabs(a[i] - v) < 0.001) return i;
    return -1;
}

double* calc_elements(double* a, int n) {
    double last_value = a[n - 1];
    for (int i = 0; i < n; i++) {
        a[i] += last_value;
    }
    return a;
}

int find_min_positive_greater_than_A(double* a, int n, double A) {
    int min_index = -1;
    double min_value;

    for (int i = 0; i < n; i++) {
        if (a[i] > 0 && a[i] > A) {
            if (min_index == -1 || a[i] < min_value) {
                min_value = a[i];
                min_index = i;
            }
        }
    }
    return min_index;
}

// Новая функция: поиск индекса минимального элемента
int find_min_element_index(double* a, int n) {
    if (n <= 0) return -1;

    int min_index = 0;
    double min_value = a[0];

    for (int i = 1; i < n; i++) {
        if (a[i] < min_value) {
            min_value = a[i];
            min_index = i;
        }
    }
    return min_index;
}

// Новая функция: вставка k элементов -999 после минимального элемента
void insert_after_min(double* a, int* n, int k) {
    if (*n + k > N) {
        printf("Ошибка: невозможно вставить %d элементов, превышен максимальный размер %d\n", k, N);
        return;
    }

    // Находим индекс минимального элемента
    int min_index = find_min_element_index(a, *n);

    if (min_index == -1) {
        printf("Ошибка: массив пуст\n");
        return;
    }

    printf("Минимальный элемент: %.2f на позиции %d\n", a[min_index], min_index);

    // Сдвигаем элементы вправо, начиная с позиции после минимального
    for (int i = *n - 1; i > min_index; i--) {
        a[i + k] = a[i];
    }

    // Вставляем k элементов -999
    for (int i = 1; i <= k; i++) {
        a[min_index + i] = -999.0;
    }

    // Увеличиваем размер массива
    *n += k;

    printf("Вставлено %d элементов -999 после минимального элемента\n", k);
}

int main() {
    setlocale(LC_ALL, "Russian");

    double a[N];
    int n;

    printf("Введите размер массива n (не более %d): ", N);
    scanf("%d", &n);

    if (n <= 0 || n > N) {
        printf("Ошибка: n должно быть от 1 до %d\n", N);
        return 1;
    }

    full_elements(a, n);
    printf("\nИсходный массив: ");
    put_elements(a, n);

    // Вставка элементов после минимального
    int k;
    printf("\n--- Вставка элементов ---\n");
    printf("Введите количество элементов -999 для вставки после минимального элемента: ");
    scanf("%d", &k);

    insert_after_min(a, &n, k);
    printf("Массив после вставки: ");
    put_elements(a, n);

    // Остальные операции
    printf("\n--- Другие операции ---\n");
    int b, e;
    printf("от до (индексы от 0 до %d): ", n - 1);
    scanf("%d %d", &b, &e);

    if (b < 0) b = 0;
    if (e >= n) e = n - 1;
    if (b > e) {
        printf("Некорректные границы\n");
    }
    else {
        printf("Сумма элементов [%d..%d]: %.2f\n", b, e, sum_elements(a, b, e));
    }

    double v;
    printf("Найти элемент: ");
    scanf("%lf", &v);
    int pos = find_element(a, n, v);
    if (pos != -1) {
        printf("Позиция: %d\n", pos);
    }
    else {
        printf("Элемент не найден\n");
    }

    calc_elements(a, n);
    printf("Массив после добавления последнего элемента: ");
    put_elements(a, n);

    double A;
    printf("Введите значение A: ");
    scanf("%lf", &A);
    int index = find_min_positive_greater_than_A(a, n, A);

    if (index != -1) {
        printf("Индекс минимального положительного элемента > %.2f: %d\n", A, index);
        printf("Значение этого элемента: %.2f\n", a[index]);
    }
    else {
        printf("Не найден положительный элемент больше %.2f\n", A);
    }

    return 0;
}