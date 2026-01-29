#include "screens/game/components/square.h"
#include "app.h"

Square Square_relativeCopy(const Square *self, Cell cell) {
  // clang-format off
  return (Square){
    .row = self->row + cell.row,
    .column = self->column + cell.column,
    .color = self->color
  };
  // clang-format on
}
