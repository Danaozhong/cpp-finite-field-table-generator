#ifndef _DRAW_TABLES_H_
#define _DRAW_TABLES_H_

#include <bitset>

namespace Galois {
namespace IO {
enum PrimitiveObjectOperation { OPERATION_ADD, OPERATION_MULTIPLY };

/// @brief Draws a Galois table.
/// @param primitivePoly The primitive polynomial coefficients.
/// @param os The stream to write the table to.
/// @param operation Configures if addition or multiply tables should be
/// written.
void DrawOperationTable(std::bitset<1024> primitivePoly, std::ostream &os,
                        PrimitiveObjectOperation operation);

void DrawAdditionTable(std::bitset<1024> primitivePoly, std::ostream &os);

void DrawMultiplicationTable(std::bitset<1024> primitivePoly, std::ostream &os);
} // namespace IO
} // namespace Galois

#endif