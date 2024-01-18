#ifndef _GALOIS_NUMBER_H_
#define _GALOIS_NUMBER_H_

#include <bitset>
#include <cmath>
#include <cstdint>

namespace Galois {
/// @brief Returns the exponent of the primitive polynomial.
/// @param primitivePoly
/// @return
int get_polynomial_degree(const std::bitset<1024> &primitivePoly);

/// @brief Simplifies the primitive element coefficients.
/// @details
/// For example, for a polynomial p(x) = x^4 + x + 1, a coefficient at index 4
/// (or higher) can be simplified. An exponent of 4 = 1000b (component binary)
/// should be simplified to (0011b). This is because for a^4: a^4^4 + a^4 + 1 =
/// 0 (because a^4 is a root of p(x)). a^16 + a^4 + 1 = 0 a^4 = -a^16 - 1 a^4 =
/// -a^1
/// - 1 = a + 1 (= 0011b in coefficient representation).
/// @param poly_coefficients The polynomial coefficients.
/// @param vector_coefficients The vector representation of the primitive
/// element coefficients, e.g. 3 = 0x11b = alpha + 1.
/// @return The simplified primitive element vector coefficients.
std::bitset<1024>
simplify_coefficients(const std::bitset<1024> &poly_coefficients,
                      std::bitset<1024> primitive_ele_coeff);

class GaloisNumber {
private:
  /// @brief The primitive polynomial, with one bit per exponent.
  std::bitset<1024> primitivePoly;

  /// @brief
  std::bitset<1024> value;

public:
  /// @brief Creates a Galois number from a primitive polynomial.
  /// @param primPoly The primitive polynomial coefficients.
  GaloisNumber(std::bitset<1024> primPoly);

  /// @brief Creates a Galois number from a polynomial and a number.
  /// @param primPoly The primitive polynomial coefficients.
  /// @param number
  GaloisNumber(std::bitset<1024> primPoly, std::bitset<1024> number);

  std::bitset<1024> GetNumber() const;
  int SetNumber(int value);

  int SetNumber(std::bitset<1024> number);

  /// @brief Returns the exponent of the galois number.
  /// @return The exponent as an integer.
  int GetExponent() const;

  int SetExponent(int exponent);
  /**
  Adds two numbers in a Galois field.
  */
  GaloisNumber operator+(const GaloisNumber &rhs) const;

  /**
  Multiplies two numbers in a Galois field.
  */
  GaloisNumber operator*(const GaloisNumber &rhs) const;
};
} // namespace Galois

#endif