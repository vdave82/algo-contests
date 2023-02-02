// Number Theory algorithms.
//
// 1) Euclid algorithm (simple and extended).

// Returns the greated common divisor of 'a' and 'b'.
template<typename IntType>
IntType gcd(IntType a, IntType b) {
    while (b != 0) {
        IntType next_b = a % b;
        a = b;
        b = next_b;
    }

    return a;
}

// Returns the least common multiple of 'a' and 'b', works even if
// 'a' * 'b' would overflow the type.
template<typename IntType>
IntType lcm(IntType a, IntType b) {
    return (a / gcd(a, b)) * b;
}

// Returns the integer factors needed to produce the gcd(a,b) as a linear
// combination of 'a' and 'b', ie. gcd(a, b) = x * a + y * b
template<typename IntType>
IntType egcd(IntType a, IntType b, IntType* px, IntType* py) {
    IntType x = 0;
    IntType y = 1;
    IntType last_x = 1;
    IntType last_y = 0;

    while (b != 0) {
        IntType q = a / b;
        // TODO: Check if "r = a - (q * b)"" would be any faster.
        IntType next_b = a % b;
        IntType next_x = last_x - x * q;
        IntType next_y = last_y - y * q;
        a = b;
        b = next_b;
        last_x = x;
        last_y = y;
        x = next_x;
        y = next_y;
    }

    *px = last_x;
    *py = last_y;
    return a;
}
