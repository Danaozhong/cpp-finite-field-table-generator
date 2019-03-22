#ifndef _GALOIS_NUMBER_H_
#define _GALOIS_NUMBER_H_

#include <cstdint>
#include <bitset>
#include <cmath>

namespace Galois
{
	int GetGFExtendedExponent(std::bitset<1024> primitivePoly)
	{
		if (0 == primitivePoly.to_ulong())
		{
			return 0;
		}

		// get highest bit position in the primitive polynomial
		std::bitset<1024> primPoly(primitivePoly);
			
		int  GF_m = 0;
			
		while(false == primPoly.none())
		{
			GF_m++;
			primPoly >>= 1;
		}
		return GF_m - 1;
	}

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
		for each bit in number which is higher or equal to the highest bit position in the primitive polynomial d
		add the value of alpha to the
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

	std::bitset<1024> ExponentialToBinary(std::bitset<1024> primitivePoly, int exponent)
	{
		int GF_m = GetGFExtendedExponent(primitivePoly);
		std::bitset<1024> number(0);
		if (exponent == -999)
		{
			// exp is minus INF - return null
			return number;
		}

		exponent %= ((int)std::pow(2.0, (double)GF_m) - 1); 
		number[exponent] = 1;
		return ToBinary(primitivePoly, number);
	}

	int BinaryToExponential(std::bitset<1024> primitivePoly, std::bitset<1024> binary)
	{
		if (binary.none())
		{
			return -999;
		}
		std::bitset<1024> currentExponent(0);
		for (int i = 0; i != 1023; i++)
		{
			if (binary == ExponentialToBinary(primitivePoly, i))
			{
				return i;
			}
		}
		throw;
	}

	class GaloisNumber
	{
	private:
		std::bitset<1024> primitivePoly;
		std::bitset<1024> value;
	public:
		GaloisNumber(std::bitset<1024> primPoly)
			: primitivePoly(primPoly)
		{}

		GaloisNumber(std::bitset<1024> primPoly, std::bitset<1024> number)
			: primitivePoly(primPoly)
		{
			this->SetNumber(number);
		}

		std::bitset<1024> GetNumber() const
		{
			return this->value;
		}

		int SetNumber(int value)
		{
			std::bitset<1024> number(value);

			this->value = ToBinary(this->primitivePoly, number);
			return 0;
		}

		int SetNumber(std::bitset<1024> number)
		{
			this->value = ToBinary(this->primitivePoly, number);
			return 0;
		}

		
		int GetExponent() const
		{
			return BinaryToExponential(this->primitivePoly, this->GetNumber());
		}

		
		int SetExponent(int exponent)
		{
			this->SetNumber(ExponentialToBinary(this->primitivePoly, exponent));
			return 0;
		}
		/**
		Adds two numbers in a GF field
		*/
		GaloisNumber operator+(const GaloisNumber &rhs) const
		{
			return GaloisNumber(this->primitivePoly, this->GetNumber() ^ rhs.GetNumber());
		}

 
		/**
		Mutliply two numbers in GF field
		*/
		GaloisNumber operator*(const GaloisNumber &rhs) const
		{
			int exp1 = this->GetExponent();
			int exp2 = rhs.GetExponent();


			GaloisNumber result(this->primitivePoly);
			if(exp1 == -999 || exp2 == -999)
			{
				result.SetExponent(-999);
			}
			else
			{
				result.SetExponent(exp1 + exp2);
			}
			return result;
		}
	};


	namespace IO
	{
		enum PrimitiveObjectOperation
		{
			OPERATION_ADD,
			OPERATION_MULTIPLY
		};

		void DrawOperationTable(std::bitset<1024> primitivePoly, std::ostream& os, PrimitiveObjectOperation operation)
		{			
			if (OPERATION_MULTIPLY == operation)
			{
				os << "MULTIPLICATION TABLE" << std::endl;
			}
			else
			{
				os << "ADDITION TABLE" << std::endl;
			}
			os << "g(x)=";
			bool started = false;
			for (int i = GetGFExtendedExponent(primitivePoly); i >= 0; i--)
			{
				if (primitivePoly[i] == 0)
				{
					continue;
				}
				if (true == started)
				{
					os << " + ";
				}
				started = true;

				os << "x^" << i;
			}

			os << std::endl << std::endl;

			GaloisNumber currentColumn(primitivePoly);
			GaloisNumber currentRow(primitivePoly);

			int tableSize = (int)std::pow(2.0, (double)GetGFExtendedExponent(primitivePoly));
	
			if (OPERATION_MULTIPLY == operation)
			{
				os << "*\t";
			}
			else
			{
				os << "+\t";
			}

			for (int i = 0; i != tableSize; i++)
			{
				currentColumn.SetNumber(i);
				os << "a^" << currentColumn.GetExponent() << "\t";
			}
			os << std::endl;

			for (int i = 0; i != tableSize; i++)
			{

				currentRow.SetNumber(i);

				os << "a^" << currentRow.GetExponent() << "\t";
				for (int k = 0; k != tableSize; k++)
				{
					currentColumn.SetNumber(k);
					if (OPERATION_MULTIPLY == operation)
					{
						GaloisNumber currentProduct = currentColumn * currentRow;
						os << currentProduct.GetNumber().to_ullong() << "\t";
					}
					else
					{
						GaloisNumber currentSum = currentColumn + currentRow;
						os << currentSum.GetNumber().to_ullong() << "\t";
					}
				}
				os << std::endl;
			}

			os << std::endl;
		}


		void DrawAdditionTable(std::bitset<1024> primitivePoly, std::ostream& os)
		{
			DrawOperationTable(primitivePoly, os, OPERATION_ADD);
		}
		

		void DrawMultiplicationTable(std::bitset<1024> primitivePoly, std::ostream& os)
		{
			DrawOperationTable(primitivePoly, os, OPERATION_MULTIPLY);
		}

	}
}

#endif