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