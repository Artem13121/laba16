#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>
#define N 200  // Óâåëè÷èë ðàçìåð äëÿ âñòàâêè

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

// Íîâàÿ ôóíêöèÿ: ïîèñê èíäåêñà ìèíèìàëüíîãî ýëåìåíòà
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

// Íîâàÿ ôóíêöèÿ: âñòàâêà k ýëåìåíòîâ -999 ïîñëå ìèíèìàëüíîãî ýëåìåíòà
void insert_after_min(double* a, int* n, int k) {
    if (*n + k > N) {
        printf("Îøèáêà: íåâîçìîæíî âñòàâèòü %d ýëåìåíòîâ, ïðåâûøåí ìàêñèìàëüíûé ðàçìåð %d\n", k, N);
        return;
    }

    // Íàõîäèì èíäåêñ ìèíèìàëüíîãî ýëåìåíòà
    int min_index = find_min_element_index(a, *n);

    if (min_index == -1) {
        printf("Îøèáêà: ìàññèâ ïóñò\n");
        return;
    }

    printf("Ìèíèìàëüíûé ýëåìåíò: %.2f íà ïîçèöèè %d\n", a[min_index], min_index);

    // Ñäâèãàåì ýëåìåíòû âïðàâî, íà÷èíàÿ ñ ïîçèöèè ïîñëå ìèíèìàëüíîãî
    for (int i = *n - 1; i > min_index; i--) {
        a[i + k] = a[i];
    }

    // Âñòàâëÿåì k ýëåìåíòîâ -999
    for (int i = 1; i <= k; i++) {
        a[min_index + i] = -999.0;
    }

    // Óâåëè÷èâàåì ðàçìåð ìàññèâà
    *n += k;

    printf("Âñòàâëåíî %d ýëåìåíòîâ -999 ïîñëå ìèíèìàëüíîãî ýëåìåíòà\n", k);
}

int main() {
    setlocale(LC_ALL, "Russian");

    double a[N];
    int n;

    printf("Ââåäèòå ðàçìåð ìàññèâà n (íå áîëåå %d): ", N);
    scanf("%d", &n);

    if (n <= 0 || n > N) {
        printf("Îøèáêà: n äîëæíî áûòü îò 1 äî %d\n", N);
        return 1;
    }

    full_elements(a, n);
    printf("\nÈñõîäíûé ìàññèâ: ");
    put_elements(a, n);

    // Âñòàâêà ýëåìåíòîâ ïîñëå ìèíèìàëüíîãî
    int k;
    printf("\n--- Âñòàâêà ýëåìåíòîâ ---\n");
    printf("Ââåäèòå êîëè÷åñòâî ýëåìåíòîâ -999 äëÿ âñòàâêè ïîñëå ìèíèìàëüíîãî ýëåìåíòà: ");
    scanf("%d", &k);

    insert_after_min(a, &n, k);
    printf("Ìàññèâ ïîñëå âñòàâêè: ");
    put_elements(a, n);

    // Îñòàëüíûå îïåðàöèè
    printf("\n--- Äðóãèå îïåðàöèè ---\n");
    int b, e;
    printf("îò äî (èíäåêñû îò 0 äî %d): ", n - 1);
    scanf("%d %d", &b, &e);

    if (b < 0) b = 0;
    if (e >= n) e = n - 1;
    if (b > e) {
        printf("Íåêîððåêòíûå ãðàíèöû\n");
    }
    else {
        printf("Ñóììà ýëåìåíòîâ [%d..%d]: %.2f\n", b, e, sum_elements(a, b, e));
    }

    double v;
    printf("Íàéòè ýëåìåíò: ");
    scanf("%lf", &v);
    int pos = find_element(a, n, v);
    if (pos != -1) {
        printf("Ïîçèöèÿ: %d\n", pos);
    }
    else {
        printf("Ýëåìåíò íå íàéäåí\n");
    }

    calc_elements(a, n);
    printf("Ìàññèâ ïîñëå äîáàâëåíèÿ ïîñëåäíåãî ýëåìåíòà: ");
    put_elements(a, n);

    double A;
    printf("Ââåäèòå çíà÷åíèå A: ");
    scanf("%lf", &A);
    int index = find_min_positive_greater_than_A(a, n, A);

    if (index != -1) {
        printf("Èíäåêñ ìèíèìàëüíîãî ïîëîæèòåëüíîãî ýëåìåíòà > %.2f: %d\n", A, index);
        printf("Çíà÷åíèå ýòîãî ýëåìåíòà: %.2f\n", a[index]);
    }
    else {
        printf("Íå íàéäåí ïîëîæèòåëüíûé ýëåìåíò áîëüøå %.2f\n", A);
    }

    return 0;
}
