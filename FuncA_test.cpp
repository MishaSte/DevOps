#include <iostream>
#include <cmath>
#include "FuncA.h"

int main() {
    FuncA func;

    double x = 0.5;
    int n = 5;
    // expected results
    double exactValue = 1.234;
    double tolerance = 0.01;

    double result = func.calculate(x, n);

    if (std::abs(result - exactValue) <= tolerance) {
        std::cout << "Test passed: Result = " << result
                  << " (within tolerance of " << tolerance << ")" << std::endl;
    } else {
        std::cerr << "Test failed: Result = " << result
                  << " (expected " << exactValue << ")" << std::endl;
    }

    return 0;
}
