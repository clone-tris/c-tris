#pragma once

#include "screens/game/components/shape.h"

Shape Tetromino_random();

static const TetrominoColor COLORS[] = {
  TETROMINO_CYAN, // I
  TETROMINO_YELLOW, // O
  TETROMINO_PURPLE, // T
  TETROMINO_BLUE, // J
  TETROMINO_ORANGE, // L
  TETROMINO_GREEN, // S
  TETROMINO_RED, // Z
};
