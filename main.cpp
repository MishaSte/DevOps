#include <iostream>
#include "FuncA.h"
int main() {
    FuncA func;


int n = 3;
double x = 0.5;
double r = func.calculate (x, n);
std::cout << "For x = " << x << " and n = " << n << ", the result is: " << r << std::endl;

return 0;
}
