#include "colors.h"
#include "helpers.h"
#include "screens/game/components/shape.h"
#include <assert.h>
#include <stb_ds.h>

typedef enum Type {
  T,
  Z,
  S,
  L,
  J,
  O,
  I,
} Type;

uint32_t color(const Type type) {
  switch (type) {
    case T:
      return TETROMINO_PURPLE;
    case Z:
      return TETROMINO_RED;
    case S:
      return TETROMINO_GREEN;
    case L:
      return TETROMINO_ORANGE;
    case J:
      return TETROMINO_BLUE;
    case O:
      return TETROMINO_YELLOW;
    case I:
      return TETROMINO_CYAN;
    default:
      assert(type);
      return SQUARE_DEFAULT;
  }
}

static const int GRIDS[][4][2] = {
  {{0, 0}, {0, 1}, {0, 2}, {1, 1}}, // T
  {{0, 0}, {0, 1}, {1, 1}, {1, 2}}, // Z
  {{0, 1}, {0, 2}, {1, 0}, {1, 1}}, // S
  {{0, 0}, {0, 1}, {0, 2}, {1, 0}}, // L
  {{0, 0}, {1, 0}, {1, 1}, {1, 2}}, // J
  {{0, 0}, {0, 1}, {1, 0}, {1, 1}}, // O
  {{0, 0}, {0, 1}, {0, 2}, {0, 3}}, // I
};

void makeSquares(Type type, Square **squares) {
  auto shapeColor = color(type);
  auto grid = GRIDS[type];
  for (int i = 0; i < 4; i++) {
    // clang-format off
    arrput(*squares, ((Square) {
      .row = grid[i][0],
      .column = grid[i][1],
      .color = shapeColor
    }));
    // clang-format on
  }
}

Shape Tetromino_random() {
  Square *squares = nullptr;
  Type type = randomInRange((Range){.start = 0, .end = 6});
  makeSquares(type, &squares);

  return Shape_create((Cell){.row = 0, .column = 0}, squares);
}
