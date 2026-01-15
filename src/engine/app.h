
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

typedef struct AppState {
  SDL_Window *window;
  SDL_Renderer *renderer;
  struct Screen *screen;
} AppState;
