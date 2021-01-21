#pragma once

#include "mod.hpp"

// This solves the equation $ax + by = gcd(a, b)$
// Input: $a$, $b$
// Output: $g$ (returned), $x$, $y$ (passed by ref)
int64_t extGcd(int64_t a, int64_t b, int64_t& x, int64_t& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int64_t x1, y1;
    int64_t g = extGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    assert(g == 1);
    return g;
}