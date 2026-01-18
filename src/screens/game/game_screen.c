#include "game_screen.h"
#include "config.h"
#include "stb_ds.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_stdinc.h"
#include "engine/painter.h"
#include "engine/screen.h"
#include "screens/game/components/shape.h"
#include "screens/game/components/tetromino.h"
#include <stdio.h>

static const ScreenVTable GameScreen_vtable;

static const SDL_FRect PLAYFIELD_RECT = {
  (float)SIDEBAR_WIDTH, (float)0, (float)WAR_ZONE_WIDTH, (float)CANVAS_HEIGHT
};

static const SDL_Point PLAYFIELD_REF = {.x = SIDEBAR_WIDTH, .y = 0};

typedef struct GameScreen {
  Screen screen;
  Shape player;
} GameScreen;

Screen *GameScreen_create(void) {
  GameScreen *self = SDL_calloc(1, sizeof(*self));
  self->player = Tetromino_random();
  self->screen.vtable = &GameScreen_vtable;
  return (Screen *)self;
}

static void GameScreen_draw(Screen *screen) {
  GameScreen *self = (GameScreen *)screen;
  drawGuide(&PLAYFIELD_RECT);
  drawShape(&self->player, &PLAYFIELD_REF);
}

static void GameScreen_destroy(Screen *screen) {
  GameScreen *game = (GameScreen *)screen;
  printf("Cleaning up GameScreen\n");
  arrfree(game->player.squares);
  SDL_free(game);
}

static const ScreenVTable GameScreen_vtable = {
  .draw = GameScreen_draw,
  .update = nullptr,
  .keyDown = nullptr,
  .mouseButtonUp = nullptr,
  .destroy = GameScreen_destroy,
};
