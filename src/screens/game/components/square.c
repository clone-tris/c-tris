#include "screens/game/components/square.h"
#include "app.h"

Square Square_relativeCopy(Square square, Cell cell) {
  // clang-format off
  return (Square){
    .row = square.row + cell.row,
    .column = square.column + cell.column,
    .color = square.color
  };
  // clang-format on
}
