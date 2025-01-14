#include <iostream>
#include <chrono>
#include "FuncA.h"

int main() {
    FuncA func;

    int n = 200000000;

    // Замір часу
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; ++i) {
        func.calculate(0.5, 3);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    if (duration >= 10 && duration <= 30) {
        std::cout << "Test passed: Execution time is " << duration << " seconds (within range)." << std::endl;
    } else {
        std::cerr << "Test failed: Execution time is " << duration << " seconds (out of range)." << std::endl;
        return 1;
    }

    return 0;
}

