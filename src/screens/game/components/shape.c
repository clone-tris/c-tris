#include "screens/game/components/shape.h"
#include "app.h"
#include "config.h"
#include "helpers.h"
#include "screens/game/components/square.h"
#include <assert.h>
#include <stb_ds.h>
#include <stdint.h>

void computeSize(Shape *shape);

Shape Shape_create(const Cell cell, Square *squares) {
  Shape shape = {
    .row = cell.row,
    .column = cell.column,
    .width = 0,
    .height = 0,
    .squares = squares
  };

  computeSize(&shape);
  return shape;
}

void computeSize(Shape *shape) {
  assert(shape);

  int32_t len = arrlen(shape->squares);
  if (len == 0) {
    return;
  }

  int32_t minRow = PUZZLE_HEIGHT;
  int32_t maxRow = 0;
  int32_t minColumn = PUZZLE_WIDTH;
  int32_t maxColumn = 0;

  for (int i = 0; i < len; i++) {
    Square square = shape->squares[i];
    maxRow = max(square.row, maxRow);
    minRow = min(square.row, minRow);
    maxColumn = max(square.column, maxColumn);
    minColumn = min(square.column, minColumn);
  }

  shape->height = maxRow - minRow + 1;
  shape->width = maxColumn - minColumn + 1;
}
