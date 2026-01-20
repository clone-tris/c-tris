#include "game_screen.h"
#include "config.h"
#include "engine/painter.h"
#include "engine/screen.h"
#include "screens/game/components/score.h"
#include "screens/game/components/shape.h"
#include "screens/game/components/tetromino.h"
#include "screens/game/painter.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
#include <stb_ds.h>
#include <stdio.h>

static const ScreenVTable GameScreen_vtable;
SDL_Texture *levelTexture = nullptr;
SDL_Texture *totalTexture = nullptr;
SDL_Texture *linesClearedTexture = nullptr;

static char levelText[20];
static char levelFormat[] = "Level\n%d";

typedef struct GameScreen {
  Screen screen;
  Shape player;
  Shape nextPlayer;
  Score score;
} GameScreen;

bool GameScreen_create(Screen **screen) {
  GameScreen *self = SDL_calloc(1, sizeof(*self));
  if (!self) {
    return false;
  }

  self->score = Score_create();
  self->player = Tetromino_random();
  self->nextPlayer = Tetromino_random();
  self->screen.vtable = &GameScreen_vtable;

  sprintf(levelText, levelFormat, self->score.level);
  makeFontTexture(levelText, &levelTexture);

  *screen = (Screen *)self;
  return true;
}

static void GameScreen_draw(Screen *screen) {
  GameScreen *self = (GameScreen *)screen;
  drawPlayfield(&self->player);
  drawSidebar(&self->nextPlayer, &self->score);
  // clang-format off
  SDL_RenderTexture(
    App_renderer,
    levelTexture,
    nullptr,
    &(SDL_FRect){
      .w = (float)levelTexture->w,
      .h = (float)levelTexture->w,
      .x = (float)(SQUARE_WIDTH / 3.0),
      .y = (float)(SQUARE_WIDTH * 4)
    }
  );
  // clang-format on
}

static void GameScreen_keydown(Screen *screen, SDL_Scancode scancode) {
  GameScreen *self = (GameScreen *)screen;
  if (scancode == SDL_SCANCODE_K) {
    self->score.level += 1;
    sprintf(levelText, levelFormat, self->score.level);
    makeFontTexture(levelText, &levelTexture);
  }
  if (scancode == SDL_SCANCODE_J) {
    self->score.level -= 1;
    sprintf(levelText, levelFormat, self->score.level);
    makeFontTexture(levelText, &levelTexture);
  }
}

static void GameScreen_cleanup(Screen *screen) {
  printf("Cleaning up GameScreen\n");
  GameScreen *self = (GameScreen *)screen;
  arrfree(self->player.squares);
  arrfree(self->nextPlayer.squares);
  SDL_DestroyTexture(levelTexture);
  SDL_DestroyTexture(totalTexture);
  SDL_DestroyTexture(linesClearedTexture);
}

static const ScreenVTable GameScreen_vtable = {
  .draw = GameScreen_draw,
  .update = nullptr,
  .keyDown = GameScreen_keydown,
  .mouseButtonUp = nullptr,
  .cleanup = GameScreen_cleanup,
};
