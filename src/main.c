#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    // I don't like the next two lines :-(
    (void)argc; 
    (void)argv;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("Sliding Square", SDL_WINDOWPOS_CENTERED, 
                                       SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    
    srand((unsigned int)time(NULL));
    float x = 320, y = 240;
    float dx = (float)(rand() % 3 + 1) * (rand() % 2 ? 1 : -1);
    float dy = (float)(rand() % 3 + 1) * (rand() % 2 ? 1 : -1);
    
    SDL_Event e;
    int running = 1;
    
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) running = 0;
        }
        
        x += dx;
        y += dy;
        
        if (x > 640) x = -70;
        if (x < -70) x = 640;
        if (y > 480) y = -70;
        if (y < -70) y = 480;
        
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        
        SDL_SetRenderDrawColor(ren, 0, 255, 255, 255);
        SDL_Rect rect = {(int)x, (int)y, 70, 70};
        SDL_RenderFillRect(ren, &rect);
        
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }
    
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
