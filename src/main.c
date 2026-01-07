#include <SDL3/SDL.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *win = SDL_CreateWindow("Sliding Square", 640, 480, 0);
  SDL_Renderer *ren = SDL_CreateRenderer(win, NULL);

  srand(time(NULL));
  float x = 320;
  float y = 240;
  float dx = (float)((rand() % 3) + 1) * (rand() % 2 ? 1 : -1);
  float dy = (float)((rand() % 3) + 1) * (rand() % 2 ? 1 : -1);
  int BaseColor = 69;

  SDL_Event e;
  int running = 1;

  while (running) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_KEY_DOWN) {
        running = 0;
      }
    }

    x += dx;
    y += dy;

    if (x > 640) {
      x = -70;
    }
    if (x < -70) {
      x = 640;
    }
    if (y > 480) {
      y = -70;
    }
    if (y < -70) {
      y = 480;
    }

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    SDL_SetRenderDrawColor(ren, BaseColor, BaseColor * 2, BaseColor * 3, 255);
    SDL_FRect rect = {x, y, 70, 70};
    SDL_RenderFillRect(ren, &rect);

    SDL_RenderPresent(ren);
    SDL_Delay(16);
  }

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
