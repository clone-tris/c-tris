#include "screens/game/components/shape.h"
#include "app.h"
#include "screens/game/components/square.h"
#include <assert.h>

Shape Shape_create(const Cell cell, Square *squares) {
  assert(squares);
  const Shape shape = {
    .row = cell.row,
    .column = cell.column,
    .width = 0,
    .height = 0,
    .squares = squares
  };

  return shape;
}
