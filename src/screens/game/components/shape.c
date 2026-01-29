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

  const int32_t len = arrlen(self->squares);
  if (len == 0) {
    return;
  }

  int32_t minRow = PUZZLE_HEIGHT;
  int32_t maxRow = 0;
  int32_t minColumn = PUZZLE_WIDTH;
  int32_t maxColumn = 0;

  for (int i = 0; i < len; i++) {
    const Square square = self->squares[i];
    maxRow = max(square.row, maxRow);
    minRow = min(square.row, minRow);
    maxColumn = max(square.column, maxColumn);
    minColumn = min(square.column, minColumn);
  }

  self->height = maxRow - minRow + 1;
  self->width = maxColumn - minColumn + 1;
}

Shape Shape_copy(const Shape *self) {
  Shape copy = *self;

  copy.squares = nullptr;
  for (int i = 0; i < arrlen(self->squares); i++) {
    arrput(copy.squares, self->squares[i]);
  }

  return copy;
}

Square *Shape_absoluteSquares(const Shape *self) {
  Square *absolutes = nullptr;
  arraddnptr(absolutes, arrlen(self->squares));

  const Cell origin = {.row = self->row, .column = self->column};
  for (int i = 0; i < arrlen(self->squares); i++) {
    absolutes[i] = Square_relativeCopy(&self->squares[i], origin);
  }
  return absolutes;
}

void Shape_translate(Shape *self, const Cell cell) {
  self->row += cell.row;
  self->column += cell.column;
}

void Shape_rotate(Shape *self) {
  Square *squares = nullptr;

  for (int i = 0; i < arrlen(self->squares); i++) {
    const Square square = self->squares[i];
    const Square rotated = {
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

bool Shape_overlapsSquares(const Shape *self, const Square *squares) {
  const Square *absolutes = Shape_absoluteSquares(self);

  for (int i = 0; i < arrlen(absolutes); i++) {
    for (int j = 0; j < arrlen(squares); j++) {
      if (absolutes[i].row == squares[j].row &&
          absolutes[i].column == squares[j].column) {
        arrfree(absolutes);
        return true;
      }
    }
  }
  arrfree(absolutes);
  return false;
}

bool Shape_withinBounds(const Shape *self) {
  const Square *absolutes = Shape_absoluteSquares(self);

  for (int i = 0; i < arrlen(absolutes); i++) {
    if (absolutes[i].column < 0 || absolutes[i].column >= PUZZLE_WIDTH ||
        absolutes[i].row >= PUZZLE_HEIGHT) {
      arrfree(absolutes);
      return false;
    }
  }
  arrfree(absolutes);
  return true;
}
