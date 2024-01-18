
#include "gtest/gtest.h"

#include "galois_number.h"

using namespace Galois;

TEST(GetPolynomialDegree, TestDegree) {
  // A polynomial x^4 + x + 1 has degree 4.
  EXPECT_EQ(4, get_polynomial_degree(std::bitset<1024>(0b10011)));

  // 1 is a polynomial of degree 0.
  EXPECT_EQ(0, get_polynomial_degree(std::bitset<1024>(0b1)));

  // This is not a valid polynomial.
  EXPECT_EQ(0, get_polynomial_degree(std::bitset<1024>(0)));
}

TEST(TestSimplifyPrimitiveElementCoefficients, TestCoefficients) {
  // We use a polynomial of x^4 + x + 1.
  const auto polynomial = std::bitset<1024>(0b10011);

  // From now on, we use a as a synonym for alpha (the primitive element).
  // Use a component a + 1: No simplification should happen.
  EXPECT_EQ(std::bitset<1024>(0b11),
            simplify_coefficients(polynomial, std::bitset<1024>(0b11)));

  // a^4 is the same as a + 1.
  // The reason can be found in the documentation of simplify_coefficients().
  EXPECT_EQ(std::bitset<1024>(0b11),
            simplify_coefficients(polynomial, std::bitset<1024>(0b10000)));
}