#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "chip8.h"

const int WIDTH = 64;
const int HEIGHT = 32;
const int SCALE = 8;

int main(int argc, char* argv[]) {

    chip8 c8;

    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;
    SDL_Surface* surface_native = NULL;

    int scale = SCALE;

    if (argc < 2) {
        fprintf(stdout, "No rom specified.\n");
        exit(EXIT_SUCCESS);
    }

    if (argc > 2) {
        scale = atoi(argv[2]);
        if (scale < 1 || scale > 20) {
            fprintf(stderr, "Invalid scale selection: %d. Using default.\n", scale);
            scale = SCALE;
        }
    }

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create window
    window = SDL_CreateWindow("CHIP-8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH * scale, HEIGHT * scale, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        fprintf(stderr, "Unable to create window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x0, 0x0, 0x0));
    surface_native = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
    
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
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    while (c8.running()) {
        
        // Handle input
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                c8.quit();
            }
        }
        if (state[SDL_SCANCODE_0]) c8.setKey(0x0); else c8.clearKey(0x0);
        if (state[SDL_SCANCODE_1]) c8.setKey(0x1); else c8.clearKey(0x1);
        if (state[SDL_SCANCODE_2]) c8.setKey(0x2); else c8.clearKey(0x2);
        if (state[SDL_SCANCODE_3]) c8.setKey(0x3); else c8.clearKey(0x3);
        if (state[SDL_SCANCODE_Q]) c8.setKey(0x4); else c8.clearKey(0x4);
        if (state[SDL_SCANCODE_W]) c8.setKey(0x5); else c8.clearKey(0x5);
        if (state[SDL_SCANCODE_E]) c8.setKey(0x6); else c8.clearKey(0x6);
        if (state[SDL_SCANCODE_E]) c8.setKey(0x7); else c8.clearKey(0x7);
        if (state[SDL_SCANCODE_A]) c8.setKey(0x8); else c8.clearKey(0x8);
        if (state[SDL_SCANCODE_S]) c8.setKey(0x9); else c8.clearKey(0x9);
        if (state[SDL_SCANCODE_D]) c8.setKey(0xa); else c8.clearKey(0xa);
        if (state[SDL_SCANCODE_F]) c8.setKey(0xb); else c8.clearKey(0xb);
        if (state[SDL_SCANCODE_Z]) c8.setKey(0xc); else c8.clearKey(0xc);
        if (state[SDL_SCANCODE_X]) c8.setKey(0xd); else c8.clearKey(0xd);
        if (state[SDL_SCANCODE_C]) c8.setKey(0xe); else c8.clearKey(0xe);
        if (state[SDL_SCANCODE_V]) c8.setKey(0xf); else c8.clearKey(0xf);
        if (state[SDL_SCANCODE_0]) c8.quit();

        c8.cycle();

        // Draw
        if (c8.draw()) {
            u32* pixels = (u32*)surface_native->pixels;

            for (int i = 0; i < WIDTH*HEIGHT; i++) {
                *pixels = (c8.pixel(i)) ? 0xffffffff : 0xff000000;

                pixels++;
            }
            SDL_BlitScaled(surface_native, NULL, surface, NULL);
            SDL_UpdateWindowSurface(window);
        }
    }

    // Quit
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}