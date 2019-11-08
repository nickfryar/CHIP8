#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "chip8.h"

const int WIDTH = 500;
const int HEIGHT = 500;

int main(int argc, char* argv[]) {

    chip8 c8;

    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;

    if (argc < 2) {
        fprintf(stdout, "No rom specified.\n");
        exit(EXIT_SUCCESS);
    }

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

    // Load rom
    FILE* file = fopen(argv[1], "rb");
    if (file == NULL) {
        fprintf(stderr, "Unable to open rom: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if ((size-0x200) > c8.getSize()) {
        fprintf(stderr, "Rom is too large: %ld bytes\n", size);
        exit(EXIT_FAILURE);
    }

    char* buffer = (char*) malloc(sizeof(char) * size);
    size_t result = fread(buffer, sizeof(char), (size_t) size, file);
    if (result != (unsigned long) size) {
        fprintf(stderr, "An error ocurred while reading the rom.\n");
        exit(EXIT_FAILURE);
    }
    
    // Read rom into memory
    c8.load(buffer, size);
    fclose(file);
    free(buffer);

    // Start
    c8.run();

    // Quit
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}