#include "galois_number.h"
#include <stdexcept>

namespace Galois {
int get_polynomial_degree(const std::bitset<1024> &primitivePoly) {
  if (primitivePoly.none()) {
    return 0;
  }

  // get highest bit position in the primitive polynomial
  std::bitset<1024> primPoly(primitivePoly);
  int GF_m = 0;
  while (!primPoly.none()) {
    GF_m++;
    primPoly >>= 1;
  }
  return GF_m - 1;
}

std::bitset<1024>
simplify_coefficients(const std::bitset<1024> &poly_coefficients,
                      std::bitset<1024> primitive_ele_coeff) {
  int GF_m = get_polynomial_degree(poly_coefficients);
  if (primitive_ele_coeff.none()) {
    return primitive_ele_coeff;
  }

  /*
  Handle vector coefficients higher than the polynomial length.
  for each bit in `number` which is higher or equal
  to the highest bit position in the primitive polynomial,
  add the value of alpha to the output.
  */
  for (int i = 1023; i >= GF_m; i--) {
    if (primitive_ele_coeff[i]) {
      // add the value of the primitive polynomial using some magic.
      primitive_ele_coeff = primitive_ele_coeff ^ poly_coefficients
                                                      << (i - GF_m);
    }
  }
  // Return the simplified coefficients.
  return primitive_ele_coeff;
}

std::bitset<1024> ExponentialToBinary(const std::bitset<1024> &primitivePoly,
                                      int exponent) {
  const int GF_m = get_polynomial_degree(primitivePoly);
  std::bitset<1024> number(0);
  if (exponent == -999) {
    // exp is minus INF - return 0
    return number;
  }

  exponent %= (2 << GF_m) - 1;
  number[exponent] = 1;
  return simplify_coefficients(primitivePoly, number);
}

int BinaryToExponential(const std::bitset<1024> &primitivePoly,
                        const std::bitset<1024> &binary) {
  if (binary.none()) {
    return -999;
  }
  // brute-force search the right exponential.
  for (int i = 0; i != 1023; i++) {
    if (binary == ExponentialToBinary(primitivePoly, i)) {
      return i;
    }
  }
  throw std::invalid_argument("polynomial exponent could not be determined");
}

GaloisNumber::GaloisNumber(std::bitset<1024> primPoly)
    : primitivePoly(primPoly) {}

GaloisNumber::GaloisNumber(std::bitset<1024> primPoly, std::bitset<1024> number)
    : primitivePoly(primPoly) {
  this->SetNumber(number);
}

std::bitset<1024> GaloisNumber::GetNumber() const { return this->value; }

int GaloisNumber::SetNumber(int value) {
  std::bitset<1024> number(value);
  this->value = simplify_coefficients(this->primitivePoly, number);
  return 0;
}

int GaloisNumber::SetNumber(std::bitset<1024> number) {
  this->value = simplify_coefficients(this->primitivePoly, number);
  return 0;
}

int GaloisNumber::GetExponent() const {
  return BinaryToExponential(this->primitivePoly, this->GetNumber());
}

int GaloisNumber::SetExponent(int exponent) {
  this->SetNumber(ExponentialToBinary(this->primitivePoly, exponent));
  return 0;
}

GaloisNumber GaloisNumber::operator+(const GaloisNumber &rhs) const {
  return GaloisNumber(this->primitivePoly, this->GetNumber() ^ rhs.GetNumber());
}

GaloisNumber GaloisNumber::operator*(const GaloisNumber &rhs) const {
  int exp1 = this->GetExponent();
  int exp2 = rhs.GetExponent();

  GaloisNumber result(this->primitivePoly);
  if (exp1 == -999 || exp2 == -999) {
    result.SetExponent(-999);
  } else {
    result.SetExponent(exp1 + exp2);
  }
  return result;
}

} // namespace Galois