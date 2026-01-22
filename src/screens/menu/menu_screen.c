#include "menu_screen.h"
#include "app.h"
#include "colors.h"
#include "config.h"
#include "engine/screen.h"
#include <SDL3/SDL_joystick.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <stdio.h>

static void MenuScreen_draw(Screen *screen);
static void MenuScreen_cleanup(Screen *screen);
static const ScreenVTable MenuScreen_vtable;

typedef struct MenuScreen {
  Screen screen;
  SDL_FRect rect;
  SDL_Vertex vert[3];
} MenuScreen;

bool MenuScreen_create(Screen **screen) {
  MenuScreen *self = SDL_calloc(1, sizeof(*self));

  if (!self) {
    self = nullptr;
    return false;
  }
  self->screen.vtable = &MenuScreen_vtable;
  self->rect = (SDL_FRect){
    .x = 0, .y = 0, (float)SQUARE_WIDTH * 4, (float)SQUARE_WIDTH * 3
  };

  self->vert[0].color = App_FColor(TETROMINO_CYAN);
  self->vert[0].position = (SDL_FPoint){.x = 25, .y = 0};
  self->vert[1].color = App_FColor(TETROMINO_CYAN);
  self->vert[1].position = (SDL_FPoint){.x = 0, .y = 50};
  self->vert[2].color = App_FColor(TETROMINO_CYAN);
  self->vert[2].position = (SDL_FPoint){.x = 50, .y = 50};

  *screen = (Screen *)self;
  return true;
}

static void MenuScreen_draw(Screen *screen) {
  MenuScreen *self = (MenuScreen *)screen;

  SDL_SetRenderDrawColor(App_renderer, 0, 0, 0, 255);
  SDL_RenderClear(App_renderer);

  SDL_RenderGeometry(App_renderer, nullptr, self->vert, 3, nullptr, 0);

  SDL_SetRenderDrawColor(App_renderer, 69 * 3, 69 * 2, 69 * 3, 255);
  SDL_RenderFillRect(App_renderer, &self->rect);
}

static void MenuScreen_keyDown(Screen *screen, SDL_Scancode scancode) {
  MenuScreen *self = (MenuScreen *)screen;
  switch (scancode) {
    case SDL_SCANCODE_D:
      self->rect.x += SQUARE_WIDTH;
      break;
    case SDL_SCANCODE_A:
      self->rect.x -= SQUARE_WIDTH;
      break;
    case SDL_SCANCODE_W:
      self->rect.y -= SQUARE_WIDTH;
      break;
    case SDL_SCANCODE_S:
      self->rect.y += SQUARE_WIDTH;
      break;
    default:
      break;
  }
}

static void MenuScreen_cleanup(Screen *screen) {
  printf("Cleaning up MenuScreen\n");
  (void)screen;
}

static const ScreenVTable MenuScreen_vtable = {
  .draw = MenuScreen_draw,
  .update = nullptr,
  .keyDown = MenuScreen_keyDown,
  .mouseButtonUp = nullptr,
  .cleanup = MenuScreen_cleanup,
};
