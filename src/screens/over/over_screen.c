#include "app.h"
#include "engine/screen.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <stdio.h>
static void draw(Screen *screen);
static void cleanup(Screen *screen);
static const ScreenVTable OverScreen_vtable;

typedef struct OverScreen {
  Screen screen;
  ScreenEvent nextStep;
  SDL_Texture *background;
} OverScreen;

bool OverScreen_create(Screen **screen) {
  OverScreen *self = SDL_calloc(1, sizeof(*self));
  if (!self) {
    self = nullptr;
    return false;
  }
  //

  SDL_Surface *surface = SDL_RenderReadPixels(App_renderer, nullptr);
  self->background = SDL_CreateTextureFromSurface(App_renderer, surface);
  SDL_DestroySurface(surface);

  self->nextStep = SCREEN_EVENT_NONE;
  //
  self->screen.vtable = &OverScreen_vtable;
  *screen = (Screen *)self;
  return true;
}

static void draw(Screen *screen) {
  OverScreen *self = (OverScreen *)screen;
  SDL_RenderTexture(App_renderer, self->background, nullptr, nullptr);
}

static ScreenEvent update(Screen *screen) {
  OverScreen *self = (OverScreen *)screen;
  return self->nextStep;
}

static void keyDown(Screen *screen, SDL_Scancode scancode) {
  OverScreen *self = (OverScreen *)screen;
  switch (scancode) {
    case SDL_SCANCODE_Q:
      self->nextStep = SCREEN_EVENT_CLOSE;
      break;
    case SDL_SCANCODE_R:
      self->nextStep = SCREEN_EVENT_GO_TO_GAME;
      break;
    case SDL_SCANCODE_M:
      self->nextStep = SCREEN_EVENT_GO_TO_MENU;
      break;
    default:
      break;
  }
}

static void cleanup(Screen *screen) {
  printf("Cleaning up GameScreen\n");
  OverScreen *self = (OverScreen *)screen;
  SDL_DestroyTexture(self->background);
}

static const ScreenVTable OverScreen_vtable = {
  .draw = draw,
  .update = update,
  .keyDown = keyDown,
  .mouseButtonUp = nullptr,
  .cleanup = cleanup,
};
