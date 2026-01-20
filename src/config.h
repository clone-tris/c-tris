#pragma once

#include <stdint.h>

static constexpr int32_t SQUARE_WIDTH = 24;
static constexpr int32_t SQUARE_BORDER_WIDTH = 3;
static constexpr int32_t PUZZLE_HEIGHT = 20;
static constexpr int32_t PUZZLE_WIDTH = 10;

static constexpr int32_t SIDEBAR_WIDTH = SQUARE_WIDTH * 6;
static constexpr int32_t WAR_ZONE_WIDTH = PUZZLE_WIDTH * SQUARE_WIDTH;

static constexpr int32_t CANVAS_WIDTH = SIDEBAR_WIDTH + WAR_ZONE_WIDTH;
static constexpr int32_t CANVAS_HEIGHT = PUZZLE_HEIGHT * SQUARE_WIDTH;

static constexpr int32_t FONT_SIZE_SMALL = 14;
static constexpr int32_t FONT_SIZE_LARGE = 34;

static constexpr int32_t INITIAL_FALL_RATE = 1000;
static constexpr int32_t FLOOR_LOCK_RATE = 500;
static constexpr int32_t FALL_RATE_REDUCTION_FACTOR = 3;
static constexpr int32_t LINES_PER_LEVEL = 10;

static constexpr int32_t BUTTON_PADDING_LEFT = 8;
static constexpr int32_t BUTTON_PADDING_TOP = 8;
static const char *FONT_NAME = "jetbrainsmono";
