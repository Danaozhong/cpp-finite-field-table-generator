#include "galois_number.h"

namespace Galois
{
	int GetGFExtendedExponent(const std::bitset<1024> &primitivePoly)
	{
		if (0 == primitivePoly.to_ulong())
		{
			return 0;
		}

		// get highest bit position in the primitive polynomial
		std::bitset<1024> primPoly(primitivePoly);

		int GF_m = 0;

		while (false == primPoly.none())
		{
			GF_m++;
			primPoly >>= 1;
		}
		return GF_m - 1;
	}

	/// @brief Evaluates a primitive polyonmial.
	/// @param primitivePoly The polynomial coefficients.
	/// @param number The number to evaluate.
	/// @return The evaluated number.
	std::bitset<1024> ToBinary(std::bitset<1024> primitivePoly, std::bitset<1024> number)
	{
		int GF_m = GetGFExtendedExponent(primitivePoly);
		std::bitset<1024> primPolyValue(primitivePoly);
		primPolyValue[GF_m] = 0;

		if (number.none())
		{
			return number;
		}

		/*
		for each bit in `number` which is higher or equal
		to the highest bit position in the primitive polynomial,
		add the value of alpha to the output.
		*/
		for (int i = 1023; i >= GF_m; i--)
		{
			if (number[i])
			{
				// add the value of the primitive polynomial
				number[i] = 0;
				number = number ^ primPolyValue << (i - GF_m);
			}
		}
		return number;
	}

	std::bitset<1024> ExponentialToBinary(const std::bitset<1024> &primitivePoly, int exponent)
	{
		int GF_m = GetGFExtendedExponent(primitivePoly);
		std::bitset<1024> number(0);
		if (exponent == -999)
		{
			// exp is minus INF - return 0
			return number;
		}

		exponent %= ((int)std::pow(2.0, (double)GF_m) - 1);
		number[exponent] = 1;
		return ToBinary(primitivePoly, number);
	}

	int BinaryToExponential(const std::bitset<1024> &primitivePoly, const std::bitset<1024> &binary)
	{
		if (binary.none())
		{
			return -999;
		}
		// brute-force search the right exponential
		std::bitset<1024> currentExponent(0);
		for (int i = 0; i != 1023; i++)
		{
			if (binary == ExponentialToBinary(primitivePoly, i))
			{
				return i;
			}
		}
		throw std::invalid_argument("polynomial exponent could not be determined");
	}

	GaloisNumber::GaloisNumber(std::bitset<1024> primPoly)
		: primitivePoly(primPoly) {}

	GaloisNumber::GaloisNumber(std::bitset<1024> primPoly, std::bitset<1024> number)
		: primitivePoly(primPoly)
	{
		this->SetNumber(number);
	}

	std::bitset<1024> GaloisNumber::GetNumber() const
	{
		return this->value;
	}

	int GaloisNumber::SetNumber(int value)
	{
		std::bitset<1024> number(value);
		this->value = ToBinary(this->primitivePoly, number);
		return 0;
	}

	int GaloisNumber::SetNumber(std::bitset<1024> number)
	{
		this->value = ToBinary(this->primitivePoly, number);
		return 0;
	}

	int GaloisNumber::GetExponent() const
	{
		return BinaryToExponential(this->primitivePoly, this->GetNumber());
	}

	int GaloisNumber::SetExponent(int exponent)
	{
		this->SetNumber(ExponentialToBinary(this->primitivePoly, exponent));
		return 0;
	}

	GaloisNumber GaloisNumber::operator+(const GaloisNumber &rhs) const
	{
		return GaloisNumber(this->primitivePoly, this->GetNumber() ^ rhs.GetNumber());
	}

	GaloisNumber GaloisNumber::operator*(const GaloisNumber &rhs) const
	{
		int exp1 = this->GetExponent();
		int exp2 = rhs.GetExponent();

		GaloisNumber result(this->primitivePoly);
		if (exp1 == -999 || exp2 == -999)
		{
			result.SetExponent(-999);
		}
		else
		{
			result.SetExponent(exp1 + exp2);
		}
		return result;
	}

}