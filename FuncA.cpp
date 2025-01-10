#include "FuncA.h"
#include <cmath>
#include <iostream>

unsigned long long factorial(int num) {
unsigned long long result = 1;
for (int i = 1; i <= num; ++i) {
result *= i;
}
return result;
}

double FuncA::calculate(double x, int n) {
double sum = 0.0;
for (int i = 0; i < n; ++i) {
// Чисельник: (-1)^n * (2n)!
long long numerator = pow(-1, i) * factorial(2 * i);
// Знаменник: (1 - 2n) * (n!)^2 * 4^n
long long denominator = (1 - 2 * i) * pow(factorial(i), 2) * pow(4, i);
// Обчислюємо член ряду
double term = static_cast<double>(numerator) / denominator * pow(x, i);
// Додаємо член до суми
sum += term;
}

return sum;
}

