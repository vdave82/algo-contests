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

// Returns a ^ (-1) modulo n, assuming gcd(a, n) == 1.
template<typename IntType>
IntType modulo_inverse(IntType a, IntType n) {
    IntType x, y;
    IntType g = egcd(a, n, &x, &y);
    if (g != 1) return 0;
    return x;
}

// Solves a system of congruences using the Chinese Remainder Theorem.
template <typename IntType>
IntType chinese_remainder_theorem(const std::vector<std::pair<IntType, IntType>>& remainders_and_moduli) {
    IntType product = 1;
    IntType solution = 0;

    std::vector<IntType> moduli;
    for (const auto& pair : remainders_and_moduli) {
        moduli.push_back(pair.second);
    }
    std::vector<IntType> remainders;
    for (const auto& pair : remainders_and_moduli) {
        remainders.push_back(pair.first);
    }
    if (remainders.size() != moduli.size()) return 0;
    
    std::vector<IntType> inverses;
    std::vector<IntType> partial_products;

    for (size_t i = 0; i < moduli.size(); ++i) {
        product *= moduli[i];
        partial_products.push_back(product / moduli[i]);
    }

    for (size_t i = 0; i < moduli.size(); ++i) {
        IntType inv = modulo_inverse(partial_products[i], moduli[i]);
        if (inv == 0) return 0;
        inverses.push_back(inv);
    }

    for (size_t i = 0; i < remainders.size(); ++i) {
        solution += remainders[i] * inverses[i] * partial_products[i];
    }
    return solution % product;
}
