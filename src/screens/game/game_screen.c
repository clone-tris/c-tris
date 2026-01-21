#include "game_screen.h"
#include "colors.h"
#include "config.h"
#include "engine/screen.h"
#include "screens/game/components/score.h"
#include "screens/game/components/shape.h"
#include "screens/game/components/square.h"
#include "screens/game/components/tetromino.h"
#include "screens/game/painter.h"
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <stb_ds.h>
#include <stdint.h>
#include <stdio.h>

void updateScore(Screen *screen, int32_t linesRemoved);
bool movePlayer(Screen *screen, Cell direction);

static const ScreenVTable GameScreen_vtable;

typedef struct GameScreen {
  Screen screen;
  Shape player;
  Shape nextPlayer;
  Square *opponent;
  Score score;
  bool isPlayerFalling;
  uint32_t nextFall;
  uint32_t fallRate;
  uint32_t endOfLock;
  bool isMoppingFloor;
  uint32_t timeRemainingAfterPaused;
} GameScreen;

bool GameScreen_create(Screen **screen) {
  GameScreen *self = SDL_calloc(1, sizeof(*self));
  if (!self) {
    return false;
  }

  self->score = Score_create();
  self->player = Tetromino_random();
  self->nextPlayer = Tetromino_random();
  self->opponent = nullptr;
  Square s = (Square){.row = 6, .column = 6, .color = TETROMINO_CYAN};
  arrput(self->opponent, s);
  // TODO: remove the above
  self->isPlayerFalling = false;
  self->nextFall = SDL_GetTicks();
  self->fallRate = INITIAL_FALL_RATE;
  self->endOfLock = 0;
  self->isMoppingFloor = false;
  self->timeRemainingAfterPaused = 0;
  //
  self->screen.vtable = &GameScreen_vtable;
  *screen = (Screen *)self;
  return true;
}

static void draw(Screen *screen) {
  GameScreen *self = (GameScreen *)screen;
  drawPlayfield(&self->player, self->opponent);
  drawSidebar(&self->nextPlayer, &self->score);
}

static void keydown(Screen *screen, SDL_Scancode scancode) {
  GameScreen *self = (GameScreen *)screen;
  switch (scancode) {
    case SDL_SCANCODE_K:
      updateScore(screen, 3);
      break;
    case SDL_SCANCODE_J:
      updateScore(screen, 1);
      break;
    case SDL_SCANCODE_W:
      Shape_rotate(&self->player);
      break;
    case SDL_SCANCODE_A:
      movePlayer(screen, (Cell){.row = 0, .column = -1});
      break;
    case SDL_SCANCODE_S:
      movePlayer(screen, (Cell){.row = 1, .column = 0});
      break;
    case SDL_SCANCODE_D:
      movePlayer(screen, (Cell){.row = 0, .column = 1});
      break;
    default:
      break;
  }
}

void updateScore(Screen *screen, int32_t linesRemoved) {
  GameScreen *self = (GameScreen *)screen;

  int32_t currentLevel = self->score.level;
  int32_t basePoints = POINTS[linesRemoved];
  int32_t linesCleared = self->score.linesCleared + linesRemoved;
  int32_t level = (linesCleared / LINES_PER_LEVEL) + 1;
  int32_t points = basePoints * currentLevel;
  int32_t total = self->score.total + points;

  if (level != currentLevel) {
    self->fallRate -= self->fallRate / FALL_RATE_REDUCTION_FACTOR;
  }

  self->score.level = level;
  self->score.linesCleared = linesCleared;
  self->score.total = total;
}

bool movePlayer(Screen *screen, const Cell direction) {
  GameScreen *self = (GameScreen *)screen;
  Shape foreshadow = Shape_copy(&self->player);
  Shape_translate(&foreshadow, direction);
  Square *absolutes = nullptr;
  arraddnptr(absolutes, 4);
  Shape_absoluteSquares(&foreshadow, absolutes);

  // TODO: add within bounds
  bool ableToMove = (bool)(!squaresCollide((SquaresPair){.a = absolutes,
                                                         .b = self->opponent}));

  if (ableToMove) {
    arrfree(self->player.squares);
    self->player = foreshadow;
  } else {
    arrfree(foreshadow.squares);
  }

  return ableToMove;
}

static void cleanup(Screen *screen) {
  printf("Cleaning up GameScreen\n");
  GameScreen *self = (GameScreen *)screen;
  arrfree(self->opponent);
  arrfree(self->player.squares);
  arrfree(self->nextPlayer.squares);
  cleanGameBrushes();
}

static const ScreenVTable GameScreen_vtable = {
  .draw = draw,
  .update = nullptr,
  .keyDown = keydown,
  .mouseButtonUp = nullptr,
  .cleanup = cleanup,
};
