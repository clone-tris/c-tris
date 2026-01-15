#define SDL_MAIN_USE_CALLBACKS 1
//
#include "config.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include "SDL3/SDL_video.h"
#include "engine/app.h"
#include "engine/screen.h"
#include "screens/game/game_screen.h"
#include "screens/menu/menu_screen.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

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

  as->screen = MenuScreen_create();

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState *as = (AppState *)appstate;

  as->screen->vtable->draw(as->screen, as);

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  AppState *as = (AppState *)appstate;

  if (event->type == SDL_EVENT_KEY_DOWN &&
      event->key.scancode == SDL_SCANCODE_P) {

    as->screen->vtable->draw(as->screen, as);

    return SDL_APP_CONTINUE;
  }

  if (event->type == SDL_EVENT_KEY_DOWN &&
      event->key.scancode == SDL_SCANCODE_G) {

    as->screen->vtable->cleanup(as->screen, as);
    as->screen = GameScreen_create();

    return SDL_APP_CONTINUE;
  }

  if (event->type == SDL_EVENT_KEY_DOWN &&
      event->key.scancode == SDL_SCANCODE_M) {

    as->screen->vtable->cleanup(as->screen, as);
    as->screen = MenuScreen_create();

    return SDL_APP_CONTINUE;
  }

  if (event->type == SDL_EVENT_KEY_DOWN &&
      event->key.scancode == SDL_SCANCODE_Q) {
    return SDL_APP_SUCCESS;
  }
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  (void)result;
  AppState *as = (AppState *)appstate;
  as->screen->vtable->cleanup(as->screen, as);
  SDL_DestroyRenderer(as->renderer);
  SDL_DestroyWindow(as->window);
  SDL_free(as);
}
