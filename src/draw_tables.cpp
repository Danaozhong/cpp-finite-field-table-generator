#include <ostream>

#include "draw_tables.h"
#include "galois_number.h"

namespace Galois
{
	namespace IO
	{
		void DrawOperationTable(std::bitset<1024> primitivePoly, std::ostream &os, PrimitiveObjectOperation operation)
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
				if (started)
				{
					os << " + ";
				}
				started = true;
				os << "x^" << i;
			}

			os << std::endl
			   << std::endl;

			GaloisNumber currentColumn(primitivePoly);
			GaloisNumber currentRow(primitivePoly);

			int tableSize = (int)std::pow(2.0, static_cast<double>(GetGFExtendedExponent(primitivePoly)));

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

		void DrawAdditionTable(std::bitset<1024> primitivePoly, std::ostream &os)
		{
			DrawOperationTable(primitivePoly, os, OPERATION_ADD);
		}

		void DrawMultiplicationTable(std::bitset<1024> primitivePoly, std::ostream &os)
		{
			DrawOperationTable(primitivePoly, os, OPERATION_MULTIPLY);
		}
	}
}
