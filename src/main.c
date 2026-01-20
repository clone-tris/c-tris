#include "colors.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
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

  as->smallFont = TTF_OpenFont("jetbrainsmono.ttf", 14);
  as->largeFont = TTF_OpenFont("jetbrainsmono.ttf", 34);
  if (!as->smallFont || !as->largeFont) {
    SDL_Log("Couldn't open font: %s\n", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // TODO: extract this part to my font-drawing bit snippet
  SDL_Surface *text = TTF_RenderText_Blended_Wrapped(
    as->smallFont, "Level\n4", 0, App_Color(UI_WHITE_TEXT), 0
  );
  if (text) {
    as->texture = SDL_CreateTextureFromSurface(App_renderer, text);
    SDL_DestroySurface(text);
  }
  // end of snippet

  if (!as->texture) {
    SDL_Log("Couldn't create text: %s\n", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!GameScreen_create(&as->screen)) {
    SDL_Log("Couldn't create Initial Screen");
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState *as = (AppState *)appstate;
  Screen_draw(as->screen);

  // clang-format off
  SDL_RenderTexture(
    App_renderer,
    as->texture,
    nullptr,
    &(SDL_FRect){
      .w = (float)as->texture->w,
      .h = (float)as->texture->h,
      .x = (float)(SQUARE_WIDTH / 3.0),
      .y = (float)(SQUARE_WIDTH * 4)
    }
  );
  // clang-format on

  SDL_RenderPresent(App_renderer);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  AppState *as = (AppState *)appstate;
  if (event->type == SDL_EVENT_KEY_DOWN) {
    Screen_keyDown(as->screen, event->key.scancode);
    switch (event->key.scancode) {
      case SDL_SCANCODE_Q:
        return SDL_APP_SUCCESS;
      case SDL_SCANCODE_G:
        if (!switchScreen(as, GameScreen_create)) {
          return SDL_APP_FAILURE;
        }
        break;
      case SDL_SCANCODE_M:
        if (!switchScreen(as, MenuScreen_create)) {
          return SDL_APP_FAILURE;
        }
        break;
      default:
        return SDL_APP_CONTINUE;
    }
  }

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  (void)result;
  AppState *as = (AppState *)appstate;

  Screen_destroy(&as->screen);

  if (as->texture) {
    SDL_DestroyTexture(as->texture);
  }

  if (as->smallFont) {
    TTF_CloseFont(as->smallFont);
  }
  if (as->largeFont) {
    TTF_CloseFont(as->largeFont);
  }

  TTF_Quit();

  SDL_free(as);
  SDL_DestroyRenderer(App_renderer);
  SDL_DestroyWindow(App_window);
}
