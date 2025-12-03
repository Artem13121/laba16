#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include "array.h"

double func(double x) {
    return 5 * x * x * x + 2 * x * x + 15 * x - 6;
}

double* full_elements(double* a, int n) {
    double x, dx;
    printf("x dx: ");
    scanf("%lf %lf", &x, &dx);
    for (int i = 0; i < n; i++) {
        a[i] = func(x);
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

void insert_after_min(double* a, int* n, int k) {
    if (*n + k > N) {
        printf("Ошибка: невозможно вставить %d элементов, превышен максимальный размер %d\n", k, N);
        return;
    }

    int min_index = find_min_element_index(a, *n);

    if (min_index == -1) {
        printf("Ошибка: массив пуст\n");
        return;
    }

    printf("Минимальный элемент: %.2f на позиции %d\n", a[min_index], min_index);

    for (int i = *n - 1; i > min_index; i--) {
        a[i + k] = a[i];
    }

    for (int i = 1; i <= k; i++) {
        a[min_index + i] = -999.0;
    }

    *n += k;

    printf("Вставлено %d элементов -999 после минимального элемента\n", k);
}
