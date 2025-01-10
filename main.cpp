#include <iostream>
#include "FuncA.h"

int main() {
FuncA func;
double result = func.calculate(0);
std::cout << "Result: " << result << std::endl;
return 0;
}
