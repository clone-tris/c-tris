#include "game_screen.h"
#include "app.h"
#include "colors.h"
#include "config.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "engine/painter.h"
#include "engine/screen.h"
#include "screens/game/components/shape.h"
#include "screens/game/components/square.h"
#include <stdio.h>

static const SDL_FRect PLAYFIELD_RECT = {
  (float)SIDEBAR_WIDTH, (float)0, (float)WAR_ZONE_WIDTH, (float)CANVAS_HEIGHT
};

static const SDL_Point PLAYFIELD_REF = {.x = SIDEBAR_WIDTH, .y = 0};

typedef struct GameScreen {
  Screen screen;
  Shape player;
} GameScreen;

void drawShape(Shape *shape) {
  for (int i = 0; i < 4; i++) {
    Square s = shape->squares[i];
    App_SetRenderDrawColor(App_renderer, s.color);

    const int x = PLAYFIELD_REF.x + ((shape->column + s.column) * SQUARE_WIDTH);
    const int y = PLAYFIELD_REF.y + ((shape->row + s.row) * SQUARE_WIDTH);

    SDL_RenderFillRect(
      App_renderer,
      &(SDL_FRect){
        .w = (float)SQUARE_WIDTH,
        .h = (float)SQUARE_WIDTH,
        .x = (float)x,
        .y = (float)y,
      }
    );
  }
}

static void GameScreen_draw(Screen *screen) {
  GameScreen *self = (GameScreen *)screen;
  drawGuide(&PLAYFIELD_RECT);

  drawShape(&self->player);
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
  // clang-format off
  game->player = (Shape){
    .row = 2,
    .column = 2,
    .width = 0,
    .height = 0,
    .squares = {
      {.row = 0, .column = 0, .color = TETROMINO_CYAN},
      {.row = 0, .column = 1, .color = TETROMINO_ORANGE},
      {.row = 1, .column = 0, .color = TETROMINO_GREEN},
      {.row = 1, .column = 1, .color = TETROMINO_BLUE},
    }
  };
  // clang-format on

  game->screen.vtable = &GameScreen_vtable;
  return (Screen *)game;
}
