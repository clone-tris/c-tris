#include "engine/screen.h"

void Screen_draw(Screen *screen) {
  if (screen->vtable->draw) {
    screen->vtable->draw(screen);
  }
}

void Screen_update(Screen *screen) {
  if (screen->vtable->update) {
    screen->vtable->update(screen);
  }
}

void Screen_keyDown(Screen *screen, SDL_Scancode scancode) {
  if (screen->vtable->keyDown) {
    screen->vtable->keyDown(screen, scancode);
  }
}

void Screen_mouseButtonUp(Screen *screen) {
  if (screen->vtable->mouseButtonUp) {
    screen->vtable->mouseButtonUp(screen);
  }
}

void Screen_destroy(Screen *screen) {
  if (screen->vtable->destroy) {
    screen->vtable->destroy(screen);
  }
}
