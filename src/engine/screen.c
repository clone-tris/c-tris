#include "engine/screen.h"
#include <SDL3/SDL_rect.h>
#include <assert.h>

void Screen_draw(Screen *screen) {
  assert(screen);
  assert(screen->vtable);
  if (screen->vtable->draw) {
    screen->vtable->draw(screen);
  }
}

ScreenEvent Screen_update(Screen *screen) {
  assert(screen);
  assert(screen->vtable);
  if (screen->vtable->update) {
    return screen->vtable->update(screen);
  }
  return SCREEN_EVENT_NONE;
}

void Screen_keyDown(Screen *screen, SDL_Scancode scancode) {
  assert(screen);
  assert(screen->vtable);
  if (screen->vtable->keyDown) {
    screen->vtable->keyDown(screen, scancode);
  }
}

void Screen_mouseButtonUp(Screen *screen, SDL_FPoint point) {
  assert(screen);
  assert(screen->vtable);
  if (screen->vtable->mouseButtonUp) {
    screen->vtable->mouseButtonUp(screen, point);
  }
}

void Screen_destroy(Screen **screen) {
  if (!screen || !*screen) {
    return;
  }

  if ((*screen)->vtable && (*screen)->vtable->cleanup) {
    (*screen)->vtable->cleanup(*screen);
  }

  SDL_free(*screen);
  *screen = nullptr;
}
