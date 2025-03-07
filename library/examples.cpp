#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

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

void TestChineseRemainderTheorem() {
    vector<pair<int64_t, int64_t>> congruences;

    congruences.push_back({2, 3});
    congruences.push_back({3, 5});
    assert(chinese_remainder_theorem(congruences) == 8);
    congruences.clear();
    congruences.push_back({2, 4});
    congruences.push_back({4, 6});
    assert(chinese_remainder_theorem(congruences) == 10);
    congruences.clear();
    congruences.push_back({1, 3});
    assert(chinese_remainder_theorem(congruences) == 1);
    congruences.clear();
}

int main(int argc, char* argv[]) {
    NumberTheory();
    TestChineseRemainderTheorem();

    return 0;
}
