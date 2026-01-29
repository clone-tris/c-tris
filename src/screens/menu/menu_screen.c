#include "menu_screen.h"
#include "app.h"
#include "config.h"
#include "engine/button.h"
#include "engine/painter.h"
#include "engine/screen.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <stdio.h>

static void draw(Screen *screen);
static void cleanup(Screen *screen);
static const ScreenVTable MenuScreen_vtable;

typedef struct MenuScreen {
  Screen screen;
  ScreenEvent nextStep;
  Button startButton;
  Button quitButton;
} MenuScreen;

bool MenuScreen_create(Screen **screen) {
  MenuScreen *self = SDL_calloc(1, sizeof(*self));
  if (!self) {
    self = nullptr;
    return false;
  }

  self->nextStep = SCREEN_EVENT_NONE;
  self->startButton = Button_create("[S]tart", (Cell){.row = 17, .column = 4});
  self->quitButton = Button_create("[Q]uit", (Cell){.row = 17, .column = 9});

  //
  self->screen.vtable = &MenuScreen_vtable;
  *screen = (Screen *)self;
  return true;
}

static void draw(Screen *screen) {
  MenuScreen *self = (MenuScreen *)screen;
  static const SDL_FRect rect = {
    .x = 0,
    .y = 0,
    .w = CANVAS_WIDTH,
    .h = CANVAS_HEIGHT,
  };
  drawGuide(&rect);
  drawNSquares(graphic, &(SDL_Point){.x = 0, .y = 0}, 43);
  drawButton(&self->startButton);
  drawButton(&self->quitButton);
}

static ScreenEvent update(Screen *screen) {
  MenuScreen *self = (MenuScreen *)screen;
  return self->nextStep;
}

static void keyDown(Screen *screen, SDL_Scancode scancode) {
  MenuScreen *self = (MenuScreen *)screen;
  switch (scancode) {
    case SDL_SCANCODE_S:
      self->nextStep = SCREEN_EVENT_GO_TO_GAME;
      break;
    case SDL_SCANCODE_Q:
      self->nextStep = SCREEN_EVENT_CLOSE;
      break;

    default:
      break;
  }
}

static void mouseButtonUp(Screen *screen, SDL_FPoint mouse) {
  MenuScreen *self = (MenuScreen *)screen;
  if (Button_clicked(&self->startButton, mouse)) {
    self->nextStep = SCREEN_EVENT_GO_TO_GAME;
  }
  if (Button_clicked(&self->quitButton, mouse)) {
    self->nextStep = SCREEN_EVENT_CLOSE;
  }
}

static void cleanup(Screen *screen) {
  MenuScreen *self = (MenuScreen *)screen;
  printf("Cleaning up MenuScreen\n");
  SDL_DestroyTexture(self->startButton.texture);
  SDL_DestroyTexture(self->quitButton.texture);
}

static const ScreenVTable MenuScreen_vtable = {
  .draw = draw,
  .update = update,
  .keyDown = keyDown,
  .mouseButtonUp = mouseButtonUp,
  .cleanup = cleanup,
};
