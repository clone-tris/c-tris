#include "config.h"
#include <raylib.h>

int main(void) {
  SetTraceLogLevel(LOG_WARNING);
  InitWindow(CANVAS_WIDTH, CANVAS_HEIGHT, "Ray-Tris");
  SetTargetFPS(60);

  Font font = LoadFont("jetbrainsmono.ttf");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground((Color){.r = 0x33, .g = 0x33, .b = 0x33, .a = 0xFF});
    DrawTextEx(
      font,
      "Hold my font",
      (Vector2){.x = (float)SQUARE_WIDTH, .y = (float)SQUARE_WIDTH},
      (float)font.baseSize,
      0,
      (Color){.r = 0xF0, .g = 0xA0, 0x00, 0xFF}
    );
    EndDrawing();
  }
}
