#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include <stdio.h>
#define SDL_MAIN_USE_CALLBACKS 1
#include "config.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "screens/game_screen/components/square.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <time.h>

typedef struct AppState {
  SDL_Window *window;
  SDL_Renderer *renderer;
} AppState;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  SDL_SetAppMetadata("C-tris", "1.0", "com.clone-tris.c-tris");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  AppState *as = (AppState *)SDL_calloc(1, sizeof(AppState));
  if (!as) {
    SDL_Log("Couldn't allocate space for AppState");
    return SDL_APP_FAILURE;
  }

  *appstate = as;

  if (!SDL_CreateWindowAndRenderer(
        "c-tris", CANVAS_WIDTH, CANVAS_HEIGHT, 0, &as->window, &as->renderer
      )) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState *as = (AppState *)appstate;

  SDL_SetRenderDrawColor(as->renderer, 0, 0, 0, 255);
  SDL_RenderClear(as->renderer);

  SDL_SetRenderDrawColor(as->renderer, 69, 69 * 2, 69 * 3, 255);
  SDL_FRect rect = {
    (float)2 * (float)SQUARE_WIDTH,
    (float)2 * (float)SQUARE_WIDTH,
    (float)SQUARE_WIDTH,
    (float)SQUARE_WIDTH
  };
  SDL_RenderFillRect(as->renderer, &rect);

  SDL_RenderPresent(as->renderer);

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  (void)appstate;
  if (event->type == SDL_EVENT_QUIT || event->type == SDL_EVENT_KEY_DOWN) {
    return SDL_APP_SUCCESS;
  }
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  (void)result;
  AppState *as = (AppState *)appstate;
  SDL_DestroyRenderer(as->renderer);
  SDL_DestroyWindow(as->window);
  SDL_free(as);
}
