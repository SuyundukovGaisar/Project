#define _CRT_SECURE_NO_WARNINGS
#include <cstddef>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <locale.h>

const double M_PI = 3.14159265358979323846;

int summa(int n) {
    int result = 0;
    for (int i = 1; i < n; i++) {
        result += i;
    }
    return result;
}

double produ(int n) {
    if (n < 0) return 0;
    double result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

double powwe(double x, int n) {
    if (n == 0) return 1;
    if (n < 0) return 1 / powwe(x, -n);
    double result = 1;
    for (int i = 0; i < n; i++) {
        result *= x;
    }
    return result;
}

double sqrtt(double x) {
    if (x < 0) return 0;
    double left = 0, right = x > 1 ? x : 1;
    double mid, precision = 1e-14;
    while ((right - left) > precision) {
        mid = (left + right) / 2;
        if (mid * mid < x) {
            left = mid;
        }
        else {
            right = mid;
        }
    }
    return (left + right) / 2;
}

double abss(double x) {
    return x < 0 ? -x : x;
}

double mod(double x, double y) {
    while (x >= y) {
        x -= y;
    }
    while (x < 0) {
        x += y;
    }
    return x;
}

double expp(double x) {
    double result = 1, term = 1;
    for (int i = 1; abss(term) > 1e-14; i++) {
        term *= x / i;
        result += term;
    }
    return result;
}

double sinus(double x) {
    x = mod(x, 2 * M_PI);
    double result = 0, term = x;
    int n = 1;
    while (abss(term) > 1e-14) {
        result += term;
        term *= -x * x / ((2 * n) * (2 * n + 1));
        n++;
    }
    return result;
}

double cosinus(double x) {
    x = mod(x, 2 * M_PI);
    double result = 1, term = 1;
    int n = 1;
    while (abss(term) > 1e-14) {
        term *= -x * x / ((2 * n - 1) * (2 * n));
        result += term;
        n++;
    }
    return result;
}

double lnn(double x) {
    if (x <= 0) return 0;
    if (x == 1) return 0;

    double result = 0;
    double term = (x - 1) / (x + 1);
    double square = term * term;
    double numerator = term;

    for (int n = 1; abss(numerator / n) > 1e-14; n += 2) {
        result += numerator / n;
        numerator *= square;
    }
    return 2 * result;
}

double log10n(double x) {
    return lnn(x) / lnn(10);
}

double pow2(double x, double b) {
    if (x < 0) {
        if ((int)b == b) {
            return (int)b % 2 == 0 ? pow2(-x, b) : -pow2(-x, b);
        }
        else {
            return 0;
        }
    }
    if (x == 0) {
        if (b == 0) {
            return 1.0;
        }
        else if (b > 0) {
            return 0.0;
        }
        else {
            return 0;
        }
    }
    return expp(b * lnn(x));
}

void compare() {
    double x = 2.0;

    printf("Сравнение sqrt:\n");
    printf("мой: %.14lf\n", sqrtt(x));
    printf("math.h: %.14lf\n", sqrt(x));

    printf("\nСравнение exp:\n");
    printf("мой: %.14lf\n", expp(x));
    printf("math.h: %.14lf\n", exp(x));

    printf("\nСравнение sin:\n");
    printf("мой: %.14lf\n", sinus(x));
    printf("math.h: %.14lf\n", sin(x));

    printf("\nСравнение cos:\n");
    printf("мой: %.14lf\n", cosinus(x));
    printf("math.h: %.14lf\n", cos(x));

    printf("\nСравнение ln:\n");
    printf("мой: %.14lf\n", lnn(x));
    printf("math.h: %.14lf\n", log(x));

    printf("\nСравнение log10:\n");
    printf("мой: %.14lf\n", log10n(x));
    printf("math.h: %.14lf\n", log10(x));

    printf("\nСравнение abs:\n");
    printf("мой: %.14lf\n", abss(-x));
    printf("math.h: %.14lf\n", fabs(-x));

    double base = 2.0, exponent = 3.0;
    printf("\nСравнение pow:\n");
    printf("мой для N: %.14lf\n", powwe(base, exponent));
    printf("мой для R: %.14lf\n", pow2(base, exponent));
    printf("math.h: %.14lf\n", pow(base, exponent));
}

int main() {
    setlocale(LC_ALL, "Russian");

    printf("Сравнение: \n");
    compare();

    return 0;
}