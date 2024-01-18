#include "galois_number.h"
#include <stdexcept>

namespace Galois {
int get_polynomial_degree(const std::bitset<1024> &primitivePoly) {
  if (0 == primitivePoly.to_ulong()) {
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

/// @brief Evaluates a primitive polynomial.
/// @param primitivePoly The polynomial coefficients.
/// @param x The vector representation of the coefficients, e.g. 3 = 0x11b =
/// alpha + 1.
/// @return The simplified vector coefficients.
std::bitset<1024> simplify_coefficients(std::bitset<1024> primitivePoly,
                                        std::bitset<1024> vector_coefficients) {
  int GF_m = get_polynomial_degree(primitivePoly);
  std::bitset<1024> primPolyValue(primitivePoly);

  if (vector_coefficients.none()) {
    return vector_coefficients;
  }

  /*
  Handle vector coefficients higher than the polynomial length.
  For example, for a polynomial p(x) = x^4 + x + 1, a coefficient at index 4 (or
  higher) can be simplified. An exponent of 4 = 1000b (component binary) should
  be simplified to (0011b). This is because for a^4: a^4^4 + a^4 + 1 = 0
  (because a^4 is a root of p(x)). a^16 + a^4 + 1 = 0 a^4 = -a^16 - 1 a^4 = -a^1
  - 1 = a + 1 (= 0011b in coefficient representation).

  for each bit in `number` which is higher or equal
  to the highest bit position in the primitive polynomial,
  add the value of alpha to the output.
  */
  for (int i = 1023; i >= GF_m; i--) {
    if (vector_coefficients[i]) {
      // add the value of the primitive polynomial using some magic.
      vector_coefficients = vector_coefficients ^ primPolyValue << (i - GF_m);
    }
  }
  return vector_coefficients;
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