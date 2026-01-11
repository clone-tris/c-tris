#pragma once

#include <stdint.h>

static const int32_t SQUARE_WIDTH = 24;
static const int32_t SQUARE_BORDER_WIDTH = 3;
static const int32_t PUZZLE_HEIGHT = 20;
static const int32_t PUZZLE_WIDTH = 10;
static const int32_t SIDEBAR_WIDTH = SQUARE_WIDTH * 6;
static const int32_t WAR_ZONE_WIDTH = PUZZLE_WIDTH * SQUARE_WIDTH;
static const int32_t CANVAS_WIDTH = SIDEBAR_WIDTH + WAR_ZONE_WIDTH;
static const int32_t CANVAS_HEIGHT = PUZZLE_HEIGHT * SQUARE_WIDTH;
