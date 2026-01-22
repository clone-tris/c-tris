#include "game_screen.h"
#include "config.h"
#include "helpers.h"
#include "engine/screen.h"
#include "screens/game/components/score.h"
#include "screens/game/components/shape.h"
#include "screens/game/components/square.h"
#include "screens/game/components/tetromino.h"
#include "screens/game/painter.h"
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <assert.h>
#include <stb_ds.h>
#include <stdint.h>
#include <stdio.h>

typedef struct GameScreen GameScreen;
void applyGravity(GameScreen *selfj);
void makePlayerFall(GameScreen *self);
void makePlayerFallnow(GameScreen *self);
void mopTheFloor(GameScreen *self);
void spawnPlayer(GameScreen *self);
void updateScore(GameScreen *self, int32_t linesRemoved);
void togglePaused(GameScreen *self);
void pause(GameScreen *self);
void play(GameScreen *self);
void rotatePlayer(GameScreen *self);
void movePlayerLeft(GameScreen *self);
void movePlayerRight(GameScreen *self);
bool movePlayerDown(GameScreen *self);
bool movePlayer(GameScreen *self, Cell direction);
void eatPlayer(GameScreen *self);
void removeOpponentFullRows(GameScreen *self, const int32_t *fullRows);
int32_t *findFullRows(const Square *opponent);
bool isLegalPlayerPosition(const Shape *player, const Square *opponent);
void clearQueue(GameScreen *self);

typedef enum Command {
  COMMAND_MOVE_LEFT,
  COMMAND_MOVE_RIGHT,
  COMMAND_MOVE_DOWN,
  COMMAND_ROTATE,
  COMMAND_PAUSE,
  COMMAND_RESTART,
  COMMAND_CLOSE,
} Command;

typedef enum State {
  STATE_PAUSED,
  STATE_PLAYING,
  STATE_ON_FLOOR,
  STATE_GAME_OVER,
} State;

static const ScreenVTable GameScreen_vtable;

typedef struct GameScreen {
  Screen screen;
  Shape player;
  Shape nextPlayer;
  Square *opponent;
  Score score;
  uint32_t fallRate;
  uint32_t nextFall;
  uint32_t endOfLock;
  bool isPlayerFalling;
  bool isMoppingFloor;
  uint32_t timeRemainingAfterPaused;
  Command *commandQueue;
  State state;
  State previousState;
} GameScreen;

bool GameScreen_create(Screen **screen) {
  GameScreen *self = SDL_calloc(1, sizeof(*self));
  if (!self) {
    return false;
  }

  self->score = Score_create();
  self->nextPlayer = Tetromino_random();
  self->opponent = nullptr;
  self->isPlayerFalling = false;
  self->nextFall = SDL_GetTicks() + INITIAL_FALL_RATE;
  self->fallRate = INITIAL_FALL_RATE;
  self->endOfLock = 0;
  self->isMoppingFloor = false;
  self->timeRemainingAfterPaused = 0;
  self->commandQueue = nullptr;
  self->state = STATE_PLAYING;
  self->previousState = STATE_PLAYING;

  //
  spawnPlayer(self);
  //

  self->screen.vtable = &GameScreen_vtable;
  *screen = (Screen *)self;
  return true;
}

static ScreenEvent update(Screen *screen) {
  GameScreen *self = (GameScreen *)screen;
  if (self->state == STATE_GAME_OVER) {
    clearQueue(self);
    return SCREEN_EVENT_GO_TO_OVER;
  }

  int32_t qLen = arrlen(self->commandQueue);
  for (int i = 0; i < qLen; i++) {
    switch (self->commandQueue[i]) {
      case COMMAND_CLOSE:
        clearQueue(self);
        return SCREEN_EVENT_CLOSE;
      case COMMAND_RESTART:
        clearQueue(self);
        return SCREEN_EVENT_GO_TO_GAME;
      case COMMAND_PAUSE:
        clearQueue(self);
        togglePaused(self);
        return SCREEN_EVENT_NONE;
      case COMMAND_ROTATE:
        rotatePlayer(self);
        break;
      case COMMAND_MOVE_LEFT:
        movePlayerLeft(self);
        break;
      case COMMAND_MOVE_RIGHT:
        movePlayerRight(self);
        break;
      case COMMAND_MOVE_DOWN:
        makePlayerFallnow(self);
        break;
      default:
        break;
    }
  }

  clearQueue(self);
  applyGravity(self);

  return SCREEN_EVENT_NONE;
}

static void draw(Screen *screen) {
  GameScreen *self = (GameScreen *)screen;
  drawPlayfield(&self->player, self->opponent);
  drawSidebar(&self->nextPlayer, &self->score);
}

void debugFullRows(GameScreen *self) {
  int32_t *fullRows = findFullRows(self->opponent);
  for (int i = 0; i < arrlen(fullRows); i++) {
    printf("%d ", fullRows[i]);
  }
  printf("\n");
  arrfree(fullRows);
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
static void keydown(Screen *screen, SDL_Scancode scancode) {
  GameScreen *self = (GameScreen *)screen;
  switch (scancode) {
    case SDL_SCANCODE_Q:
      arrput(self->commandQueue, COMMAND_CLOSE);
      break;
    case SDL_SCANCODE_R:
      arrput(self->commandQueue, COMMAND_RESTART);
      break;
    case SDL_SCANCODE_P:
      if (self->state == STATE_PAUSED || self->state == STATE_PLAYING ||
          self->state == STATE_ON_FLOOR) {
        arrput(self->commandQueue, COMMAND_PAUSE);
      }
      break;
    case SDL_SCANCODE_UP:
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_SPACE:
      if (self->state == STATE_PLAYING || self->state == STATE_ON_FLOOR) {
        arrput(self->commandQueue, COMMAND_ROTATE);
      }
      break;
    case SDL_SCANCODE_LEFT:
    case SDL_SCANCODE_A:
      if (self->state == STATE_PLAYING || self->state == STATE_ON_FLOOR) {
        arrput(self->commandQueue, COMMAND_MOVE_LEFT);
      }
      break;
    case SDL_SCANCODE_RIGHT:
    case SDL_SCANCODE_D:
      if (self->state == STATE_PLAYING || self->state == STATE_ON_FLOOR) {
        arrput(self->commandQueue, COMMAND_MOVE_RIGHT);
      }
      break;
    case SDL_SCANCODE_DOWN:
    case SDL_SCANCODE_S:
      if (self->state == STATE_PLAYING || self->state == STATE_ON_FLOOR) {
        arrput(self->commandQueue, COMMAND_MOVE_DOWN);
      }
      break;
    case SDL_SCANCODE_L:
      debugFullRows(self);
      break;

    default:
      break;
  }
}
// NOLINTEND(readability-function-cognitive-complexity)

void applyGravity(GameScreen *self) {
  switch (self->state) {
    case STATE_ON_FLOOR:
      mopTheFloor(self);
      break;
    case STATE_PLAYING:
      makePlayerFall(self);
      break;
    default:
      break;
  }
}

void makePlayerFall(GameScreen *self) {
  uint32_t now = SDL_GetTicks();
  if (now < self->nextFall || self->isPlayerFalling) {
    return;
  }

  self->isPlayerFalling = true;

  bool ableToMove = movePlayerDown(self);

  if (ableToMove) {
    self->state = STATE_PLAYING;
    self->nextFall = now + self->fallRate;
  } else {
    self->state = STATE_ON_FLOOR;
    self->endOfLock = now + FLOOR_LOCK_RATE;
    self->nextFall = self->endOfLock;
  }

  self->isPlayerFalling = false;
}

void makePlayerFallnow(GameScreen *self) {
  if (self->state != STATE_PLAYING) {
    return;
  }
  self->nextFall = 0;
  self->score.total += 1;
  makePlayerFall(self);
}

void mopTheFloor(GameScreen *self) {
  uint32_t now = SDL_GetTicks();
  if (now < self->endOfLock || self->isMoppingFloor) {
    return;
  }

  self->isMoppingFloor = true;

  bool ableToMove = movePlayerDown(self);

  if (ableToMove) {
    self->state = STATE_PLAYING;
  } else {
    eatPlayer(self);
    const int32_t *fullRows = findFullRows(self->opponent);
    const int32_t fullRowsCount = arrlen(fullRows);
    if (fullRowsCount > 0) {
      removeOpponentFullRows(self, fullRows);
      updateScore(self, fullRowsCount);
    }
    arrfree(fullRows);
    spawnPlayer(self);
    self->state = STATE_PLAYING;
    self->nextFall = now + self->fallRate;

    if (Shape_overlapsSquares(&self->player, self->opponent)) {
      self->state = STATE_GAME_OVER;
    }
  }
  self->isMoppingFloor = false;
}

void spawnPlayer(GameScreen *self) {
  arrfree(self->player.squares);
  self->player = Shape_copy(&self->nextPlayer);
  self->player.column = (PUZZLE_WIDTH - self->player.width) / 2;
  arrfree(self->nextPlayer.squares);
  self->nextPlayer = Tetromino_random();
}

void updateScore(GameScreen *self, int32_t linesRemoved) {
  int32_t currentLevel = self->score.level;
  int32_t basePoints = POINTS[linesRemoved];
  assert(linesRemoved >= 0 && linesRemoved <= 4);
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

void togglePaused(GameScreen *self) {
  if (self->state == STATE_PAUSED) {
    play(self);
  } else if (self->state == STATE_PLAYING || self->state == STATE_ON_FLOOR) {
    pause(self);
  }
}

void pause(GameScreen *self) {
  const uint32_t now = SDL_GetTicks();
  if (self->state == STATE_PLAYING) {
    self->timeRemainingAfterPaused = max((int32_t)(self->nextFall - now), 0);
  } else if (self->state == STATE_ON_FLOOR) {
    self->timeRemainingAfterPaused = max((int32_t)(self->endOfLock - now), 0);
  }

  self->previousState = self->state;
  self->state = STATE_PAUSED;
}

void play(GameScreen *self) {
  const uint32_t now = SDL_GetTicks();
  if (self->previousState == STATE_PLAYING) {
    self->nextFall = now + self->timeRemainingAfterPaused;
  } else if (self->previousState == STATE_ON_FLOOR) {
    self->endOfLock = now + self->timeRemainingAfterPaused;
  }
  self->state = self->previousState;
}

void rotatePlayer(GameScreen *self) {
  Shape foreshadow = Shape_copy(&self->player);
  Shape_rotate(&foreshadow);

  bool ableToMove = isLegalPlayerPosition(&foreshadow, self->opponent);

  if (ableToMove) {
    arrfree(self->player.squares);
    self->player = foreshadow;
  } else {
    arrfree(foreshadow.squares);
  }
}

void movePlayerLeft(GameScreen *self) {
  movePlayer(self, (Cell){.row = 0, .column = -1});
}

void movePlayerRight(GameScreen *self) {
  movePlayer(self, (Cell){.row = 0, .column = 1});
}

bool movePlayerDown(GameScreen *self) {
  bool albeToMove = movePlayer(self, (Cell){.row = 1, .column = 0});
  return albeToMove;
}

bool movePlayer(GameScreen *self, Cell direction) {
  Shape foreshadow = Shape_copy(&self->player);
  Shape_translate(&foreshadow, direction);

  bool ableToMove = isLegalPlayerPosition(&foreshadow, self->opponent);

  if (ableToMove) {
    arrfree(self->player.squares);
    self->player = foreshadow;
  } else {
    arrfree(foreshadow.squares);
  }

  return ableToMove;
}

void eatPlayer(GameScreen *self) {
  const Square *absolutes = Shape_absoluteSquares(&self->player);
  const int32_t len = arrlen(absolutes);
  for (int i = 0; i < len; i++) {
    arrput(self->opponent, absolutes[i]);
  }
  arrfree(absolutes);
}

void removeOpponentFullRows(GameScreen *self, const int32_t *fullRows) {
  Square *squares = nullptr;
  for (int i = 0; i < arrlen(self->opponent); i++) {
    bool rowToRemove = false;
    Square square = self->opponent[i];
    for (int f = 0; f < arrlen(fullRows); f++) {
      if (fullRows[f] == square.row) {
        rowToRemove = true;
        break;
      }
    }
    if (rowToRemove) {
      continue;
    }

    int32_t rowBeforeShifting = square.row;
    for (int f = 0; f < arrlen(fullRows); f++) {
      int32_t fullRow = fullRows[f];
      if (fullRow > rowBeforeShifting) {
        square.row += 1;
      }
    }

    arrput(squares, square);
  }
  arrfree(self->opponent);
  self->opponent = squares;
}

int32_t *findFullRows(const Square *opponent) {
  int32_t *fullRows = nullptr;
  struct {
    int32_t key;
    int32_t value;
  } *population = nullptr;
  hmdefault(population, 0);

  for (int i = 0; i < arrlen(opponent); i++) {
    const int32_t squareRow = opponent[i].row;
    const int32_t value = hmget(population, squareRow) + 1;
    hmput(population, squareRow, value);
  }

  for (int i = 0; i < hmlen(population); i++) {
    if (population[i].value >= PUZZLE_WIDTH) {
      arrput(fullRows, population[i].key);
    }
  }

  hmfree(population);

  return fullRows;
}

bool isLegalPlayerPosition(const Shape *player, const Square *opponent) {
  return !Shape_overlapsSquares(player, opponent) && Shape_withinBounds(player);
}

void clearQueue(GameScreen *self) {
  arrsetlen(self->commandQueue, 0);
}

static void cleanup(Screen *screen) {
  printf("Cleaning up GameScreen\n");
  GameScreen *self = (GameScreen *)screen;
  arrfree(self->opponent);
  arrfree(self->player.squares);
  arrfree(self->nextPlayer.squares);
  arrfree(self->commandQueue);
  cleanGameBrushes();
}

static const ScreenVTable GameScreen_vtable = {
  .draw = draw,
  .update = update,
  .keyDown = keydown,
  .mouseButtonUp = nullptr,
  .cleanup = cleanup,
};
