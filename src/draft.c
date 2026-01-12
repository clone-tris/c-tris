#pragma once

#include <SDL3/SDL.h>

typedef struct Screen Screen;

// Vtable: function pointers for polymorphic behavior
typedef struct ScreenVTable {
  void (*update)(Screen *self, float dt);
  void (*draw)(Screen *self, SDL_Renderer *renderer);
  void (*cleanup)(Screen *self);
} ScreenVTable;

// Base screen structure
struct Screen {
  const ScreenVTable *vtable; // Pointer to vtable (the "type")
  void *data; // Screen-specific data
};

// menu_screen.h
typedef struct MenuData {
  int selected_option;
} MenuData;

Screen *menu_screen_create(void);

// menu_screen.c
#include <stdlib.h>

static void menu_update(Screen *self, float dt) {
  (void)dt;
  MenuData *data = (MenuData *)self->data;
  // Menu update logic...
  (void)data;
}

static void menu_draw(Screen *self, SDL_Renderer *renderer) {
  (void)renderer;
  MenuData *data = (MenuData *)self->data;
  // Menu draw logic...
  (void)data;
}

static void menu_cleanup(Screen *self) {
  free(self->data);
  free(self);
}

// The vtable for menu - defines its "type"
static const ScreenVTable menu_vtable = {
  .update = menu_update, .draw = menu_draw, .cleanup = menu_cleanup
};

Screen *menu_screen_create(void) {
  Screen *screen = malloc(sizeof(Screen));
  screen->vtable = &menu_vtable; // Connect to vtable

  MenuData *data = malloc(sizeof(MenuData));
  data->selected_option = 0;
  screen->data = data;

  return screen;
}

typedef struct GameData {
  int score;
} GameData;

static void game_update(Screen *self, float dt) {
  (void)dt;
  GameData *data = (GameData *)self->data;
  // Game update logic...
  (void)data;
}

static void game_draw(Screen *self, SDL_Renderer *renderer) {
  (void)renderer;
  GameData *data = (GameData *)self->data;
  // Game draw logic...
  (void)data;
}

static void game_cleanup(Screen *self) {
  free(self->data);
  free(self);
}

// The vtable for game
static const ScreenVTable game_vtable = {
  .update = game_update, .draw = game_draw, .cleanup = game_cleanup
};

Screen *game_screen_create(void) {
  Screen *screen = malloc(sizeof(Screen));
  screen->vtable = &game_vtable; // Different vtable!

  GameData *data = malloc(sizeof(GameData));
  data->score = 0;
  screen->data = data;

  return screen;
}

typedef struct OverData {
  int final_score;
} OverData;

static void over_update(Screen *self, float dt) {
  (void)dt;
  OverData *data = (OverData *)self->data;
  (void)data;
  // Over update logic...
}

static void over_draw(Screen *self, SDL_Renderer *renderer) {
  (void)renderer;
  OverData *data = (OverData *)self->data;
  (void)data;
  // Over draw logic...
}

static void over_cleanup(Screen *self) {
  free(self->data);
  free(self);
}

// The vtable for over
static const ScreenVTable over_vtable = {
  .update = over_update, .draw = over_draw, .cleanup = over_cleanup
};

Screen *over_screen_create(int score) {
  Screen *screen = malloc(sizeof(Screen));
  screen->vtable = &over_vtable;

  OverData *data = malloc(sizeof(OverData));
  data->final_score = score;
  screen->data = data;

  return screen;
}

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("Clonetris", 640, 480, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

  // Single pointer to current screen - could be any type!
  Screen *current_screen = menu_screen_create();

  bool running = true;
  Uint64 last_time = SDL_GetTicks();

  while (running) {
    Uint64 current_time = SDL_GetTicks();
    float dt = (float)(current_time - last_time) / 1000.0F;
    last_time = current_time;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }

    // Polymorphic calls - same code works for ANY screen!
    current_screen->vtable->update(current_screen, dt);
    current_screen->vtable->draw(current_screen, renderer);

    SDL_RenderPresent(renderer);

    // Switch screens (example)
    // screen_cleanup(current_screen);
    // current_screen = game_screen_create();
  }

  current_screen->vtable->cleanup(current_screen);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
