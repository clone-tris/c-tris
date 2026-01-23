#pragma once

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_scancode.h>

typedef enum ScreenEvent {
  SCREEN_EVENT_NONE,
  SCREEN_EVENT_CLOSE,
  SCREEN_EVENT_GO_TO_MENU,
  SCREEN_EVENT_GO_TO_GAME,
  SCREEN_EVENT_GO_TO_OVER,
} ScreenEvent;

typedef struct Screen Screen;

typedef struct ScreenVTable {
  void (*draw)(Screen *);
  ScreenEvent (*update)(Screen *);
  void (*keyDown)(Screen *, SDL_Scancode);
  void (*mouseButtonUp)(Screen *, SDL_FPoint);
  void (*cleanup)(Screen *);
} ScreenVTable;

typedef struct Screen {
  const ScreenVTable *vtable;
} Screen;

void Screen_draw(Screen *);
ScreenEvent Screen_update(Screen *);
void Screen_keyDown(Screen *, SDL_Scancode);
void Screen_mouseButtonUp(Screen *, SDL_FPoint);
void Screen_destroy(Screen **);
