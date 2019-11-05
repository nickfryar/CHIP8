#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

const int WIDTH = 500;
const int HEIGHT = 500;

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create window
    window = SDL_CreateWindow("CHIP-8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        fprintf(stderr, "Unable to create window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x0, 0x0, 0x0));
    SDL_UpdateWindowSurface(window);

    #ifdef DEBUG
    SDL_Delay(1000);
    #endif

    return 0;
}