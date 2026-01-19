#include "screens/game/components/shape.h"
#include "app.h"
#include "screens/game/components/square.h"
#include <stb_ds.h>
#include <stdint.h>

Shape Shape_create(Cell cell, Square *squares) {
  Shape shape = {
    .row = cell.row,
    .column = cell.column,
    .width = 0,
    .height = 0,
    .squares = squares
  };

  return shape;
}
