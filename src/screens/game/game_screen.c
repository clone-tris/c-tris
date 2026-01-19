#include "game_screen.h"
#include "engine/screen.h"
#include "screens/game/components/shape.h"
#include "screens/game/components/tetromino.h"
#include "screens/game/painter.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <stb_ds.h>
#include <stdio.h>

static const ScreenVTable GameScreen_vtable;

typedef struct GameScreen {
  Screen screen;
  Shape player;
} GameScreen;

bool GameScreen_create(Screen **screen) {
  GameScreen *self = SDL_calloc(1, sizeof(*self));
  if (!self) {
    return false;
  }
  self->player = Tetromino_random();
  self->screen.vtable = &GameScreen_vtable;
  *screen = (Screen *)self;
  return true;
}

static void GameScreen_draw(Screen *screen) {
  GameScreen *self = (GameScreen *)screen;
  drawPlayfield(&self->player);
}

static void GameScreen_cleanup(Screen *screen) {
  printf("Cleaning up GameScreen\n");
  GameScreen *game = (GameScreen *)screen;
  arrfree(game->player.squares);
}

static const ScreenVTable GameScreen_vtable = {
  .draw = GameScreen_draw,
  .update = nullptr,
  .keyDown = nullptr,
  .mouseButtonUp = nullptr,
  .cleanup = GameScreen_cleanup,
};
