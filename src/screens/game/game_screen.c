#include "game_screen.h"
#include "colors.h"
#include "config.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "engine/app.h"
#include "engine/screen.h"
#include <stdio.h>

static const SDL_FRect PLAYFIELD_RECT = {
  (float)SIDEBAR_WIDTH, (float)0, (float)WAR_ZONE_WIDTH, (float)CANVAS_HEIGHT
};

struct GameScreen {
  struct Screen screen;
};

void drawGuide(const SDL_FRect *rect) {
  App_SetRenderDrawColor(App_renderer, UI_BACKGROUND);
  SDL_RenderFillRect(App_renderer, rect);
}

static void GameScreen_draw(struct Screen *self) {
  (void)self;

  drawGuide(&PLAYFIELD_RECT);
}

static void GameScreen_cleanup(struct Screen *self) {
  struct GameScreen *game = (struct GameScreen *)self;
  printf("Cleaning up GameScreen\n");
  SDL_free(game);
}

static const struct ScreenVTable GameScreen_vtable = {
  .draw = GameScreen_draw,
  .update = nullptr,
  .keyDown = nullptr,
  .mouse_button_up = nullptr,
  .cleanup = GameScreen_cleanup,
};

struct Screen *GameScreen_create(void) {
  struct GameScreen *game = SDL_calloc(1, sizeof(struct GameScreen));
  game->screen.vtable = &GameScreen_vtable;
  return (struct Screen *)game;
}
