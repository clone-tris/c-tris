#pragma once

#include "app.h"
#include "screens/game/components/square.h"
#include <stdint.h>

typedef struct SquaresPair {
  Square *a;
  Square *b;
} SquaresPair;

typedef struct Shape {
  int32_t row;
  int32_t column;
  int32_t width;
  int32_t height;
  Square *squares;
} Shape;

Shape Shape_create(Cell, const Square *);
Shape Shape_copy(const Shape *);
Square *Shape_absoluteSquares(const Shape *);
void Shape_translate(Shape *, Cell);
void Shape_rotate(Shape *);
bool Shape_overlapsSquares(const Shape *, const Square *);
bool Shape_withinBounds(const Shape *);
