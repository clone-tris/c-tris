#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <stdio.h>
#define STB_DS_IMPLEMENTATION
#define SDL_MAIN_USE_CALLBACKS 1
//
#include "app.h"
#include "config.h"
#include "engine/screen.h"
#include "screens/game/game_screen.h"
#include "screens/menu/menu_screen.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stb_ds.h>
#include <time.h>

SDL_Window *App_window = nullptr;
SDL_Renderer *App_renderer = nullptr;

TTF_Font *smallFont;
TTF_Font *largeFont;

bool switchScreen(AppState *as, bool (*create)(Screen **)) {
  Screen_destroy(&as->screen);
  if (!create(&as->screen)) {
    SDL_Log("Couldn't alloate and switch to Screen");
    return false;
  }
  return true;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  SDL_srand((Uint64)time(nullptr));

  SDL_SetAppMetadata("C-tris", "1.0", "com.clone-tris.c-tris");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  AppState *as = (AppState *)SDL_calloc(1, sizeof(*as));
  if (!as) {
    SDL_Log("Couldn't allocate space for AppState");
    return SDL_APP_FAILURE;
  }

  *appstate = as;

  if (!SDL_CreateWindowAndRenderer(
        "c-tris", CANVAS_WIDTH, CANVAS_HEIGHT, 0, &App_window, &App_renderer
      )) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!TTF_Init()) {
    SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  smallFont = TTF_OpenFont("jetbrainsmono.ttf", 14);
  largeFont = TTF_OpenFont("jetbrainsmono.ttf", 34);
  if (!smallFont || !largeFont) {
    SDL_Log("Couldn't open font: %s\n", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SDL_SetRenderDrawBlendMode(App_renderer, SDL_BLENDMODE_BLEND);

  if (!MenuScreen_create(&as->screen)) {
    SDL_Log("Couldn't create Initial Screen");
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState *as = (AppState *)appstate;
  ScreenEvent screenEvent = Screen_update(as->screen);
  switch (screenEvent) {
    case SCREEN_EVENT_CLOSE:
      return SDL_APP_SUCCESS;
    case SCREEN_EVENT_GO_TO_MENU:
      if (!switchScreen(as, MenuScreen_create)) {
        return SDL_APP_FAILURE;
      }
      break;
    case SCREEN_EVENT_GO_TO_GAME:
      if (!switchScreen(as, GameScreen_create)) {
        return SDL_APP_FAILURE;
      }
      break;
    case SCREEN_EVENT_GO_TO_OVER:
      // implement game over screen
      printf("let us pretend this is the game over screen");
      if (!switchScreen(as, GameScreen_create)) {
        return SDL_APP_FAILURE;
      }
      break;
    default:
      break;
  }
  Screen_draw(as->screen);
  SDL_RenderPresent(App_renderer);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  AppState *as = (AppState *)appstate;
  if (event->type == SDL_EVENT_KEY_DOWN) {
    Screen_keyDown(as->screen, event->key.scancode);
  }

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  (void)result;
  AppState *as = (AppState *)appstate;

  Screen_destroy(&as->screen);

  if (smallFont) {
    TTF_CloseFont(smallFont);
  }
  if (largeFont) {
    TTF_CloseFont(largeFont);
  }

  TTF_Quit();

  SDL_free(as);
  SDL_DestroyRenderer(App_renderer);
  SDL_DestroyWindow(App_window);
}
