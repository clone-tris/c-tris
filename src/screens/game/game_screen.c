#include "game_screen.h"
#include "colors.h"
#include "config.h"
#include "SDL3/SDL_stdinc.h"
#include "engine/painter.h"
#include "engine/screen.h"
#include "screens/game/components/square.h"
#include <stdio.h>

static const SDL_FRect PLAYFIELD_RECT = {
  (float)SIDEBAR_WIDTH, (float)0, (float)WAR_ZONE_WIDTH, (float)CANVAS_HEIGHT
};

typedef struct GameScreen {
  Screen screen;
  Square s;
} GameScreen;

static void GameScreen_draw(Screen *screen) {
  GameScreen *self = (GameScreen *)screen;

  drawGuide(&PLAYFIELD_RECT);
}

static void GameScreen_cleanup(Screen *self) {
  GameScreen *game = (GameScreen *)self;
  printf("Cleaning up GameScreen\n");
  SDL_free(game);
}

static const ScreenVTable GameScreen_vtable = {
  .draw = GameScreen_draw,
  .update = nullptr,
  .keyDown = nullptr,
  .mouse_button_up = nullptr,
  .cleanup = GameScreen_cleanup,
};

Screen *GameScreen_create(void) {
  GameScreen *game = SDL_calloc(1, sizeof(GameScreen));

  game->s = (Square){.row = 2, .column = 2, .color = TETROMINO_ORANGE};

  game->screen.vtable = &GameScreen_vtable;
  return (Screen *)game;
}
