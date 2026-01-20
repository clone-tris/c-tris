#pragma once

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>

typedef struct AppState {
  struct Screen *screen;
} AppState;

extern SDL_Window *App_window;
extern SDL_Renderer *App_renderer;

extern TTF_Font *smallFont;
extern TTF_Font *largeFont;

typedef struct Cell {
  int row;
  int column;
} Cell;
