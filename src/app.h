#pragma once

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

typedef struct AppState {
  struct Screen *screen;
} AppState;

extern SDL_Window *App_window;
extern SDL_Renderer *App_renderer;

typedef struct Cell {
  int row;
  int column;
} Cell;
