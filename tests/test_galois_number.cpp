
#include "gtest/gtest.h"

#include "galois_number.h"

using namespace Galois;

TEST(GetPolynomialDegree, TestDegree) {
    // A polynomial x^4 + x + 1 has degree 4.
    EXPECT_EQ(4, get_polynomial_degree(std::bitset<1024>(0b10011)));
}