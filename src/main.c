#include "config.h"
#include "screens/game_screen/components/square.h"
#include <SDL3/SDL.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *win = SDL_CreateWindow(
    "Sliding Square", CANVAS_WIDTH, CANVAS_HEIGHT, 0
  );
  SDL_Renderer *ren = SDL_CreateRenderer(win, NULL);

  srand(time(NULL));
  Square square = {.row = 1, .column = 1};
  int BaseColor = 69;

  SDL_Event e;
  int running = 1;

  while (running) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_KEY_DOWN) {
        running = 0;
      }
    }

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    SDL_SetRenderDrawColor(ren, BaseColor, BaseColor * 2, BaseColor * 3, 255);
    SDL_FRect rect = {
      (float)square.column * (float)SQUARE_WIDTH,
      (float)square.row * (float)SQUARE_WIDTH,
      (float)SQUARE_WIDTH,
      (float)SQUARE_WIDTH
    };
    SDL_RenderFillRect(ren, &rect);

    SDL_RenderPresent(ren);
    SDL_Delay(16);
  }

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
