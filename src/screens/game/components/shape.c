#include "screens/game/components/shape.h"
#include "app.h"
#include "config.h"
#include "helpers.h"
#include "screens/game/components/square.h"
#include <assert.h>
#include <stb_ds.h>
#include <stdint.h>

void computeSize(Shape *self);

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

void computeSize(Shape *self) {
  assert(self);

  int32_t len = arrlen(self->squares);
  if (len == 0) {
    return;
  }

  int32_t minRow = PUZZLE_HEIGHT;
  int32_t maxRow = 0;
  int32_t minColumn = PUZZLE_WIDTH;
  int32_t maxColumn = 0;

  for (int i = 0; i < len; i++) {
    Square square = self->squares[i];
    maxRow = max(square.row, maxRow);
    minRow = min(square.row, minRow);
    maxColumn = max(square.column, maxColumn);
    minColumn = min(square.column, minColumn);
  }

  self->height = maxRow - minRow + 1;
  self->width = maxColumn - minColumn + 1;
}

Shape Shape_copy(const Shape *shape) {
  Shape copy = *shape;

  copy.squares = nullptr;
  for (int i = 0; i < arrlen(shape->squares); i++) {
    arrput(copy.squares, shape->squares[i]);
  }

  return copy;
}

void Shape_absoluteSquares(Shape *self, Square *absolute) {
  const int32_t len = arrlen(self->squares);
  const Cell origin = {.row = self->row, .column = self->column};
  for (int i = 0; i < len; i++) {
    absolute[i] = Square_relativeCopy(self->squares[i], origin);
  }
}

void Shape_translate(Shape *self, Cell cell) {
  self->row += cell.row;
  self->column += cell.column;
}

void Shape_rotate(Shape *self) {
  Square *squares = nullptr;

  for (int i = 0; i < arrlen(self->squares); i++) {
    Square square = (*self).squares[i];
    Square rotated = {
      .row = square.column,
      .column = self->height - square.row - 1,
      .color = square.color
    };
    arrput(squares, rotated);
  }
  arrfree(self->squares);
  self->squares = squares;
  computeSize(self);
}

bool squaresCollide(SquaresPair p) {
  const int32_t aLen = arrlen(p.a);
  const int32_t bLen = arrlen(p.b);
  for (int i = 0; i < aLen; i++) {
    for (int j = 0; j < bLen; j++) {
      if (p.a[i].row == p.b[j].row && p.a[i].column == p.b[j].column) {
        return true;
      }
    }
  }
  return false;
}
