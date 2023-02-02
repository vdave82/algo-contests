#include <cstdint>
#include <iostream>
#include <string>

#include "number_theory.h"

using namespace std;

void NumberTheory() {
    int64_t a = 15;
    int64_t b = 25;

    int64_t x, y, g;
    g = egcd(a, b, &x, &y);

    cout << "A = " << a << ", B = " << b << endl;
    cout << "GCD = " << g << " = " << x << " * " << a << " + " << y << " * " << b << " = " << x * a + y * b << endl;
}

int main(int argc, char* argv[]) {
    NumberTheory();

    return 0;
}
