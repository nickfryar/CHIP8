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

    SDL_Event e;

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
    while (c8.running()) {
        
        // Handle input
        c8.clearKeys();
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                c8.quit();
            }
            else if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_1: c8.setKey(0x0); break;
                    case SDLK_2: c8.setKey(0x1); break;
                    case SDLK_3: c8.setKey(0x2); break;
                    case SDLK_4: c8.setKey(0x3); break;
                    case SDLK_q: c8.setKey(0x4); break;
                    case SDLK_w: c8.setKey(0x5); break;
                    case SDLK_e: c8.setKey(0x6); break;
                    case SDLK_r: c8.setKey(0x7); break;
                    case SDLK_a: c8.setKey(0x8); break;
                    case SDLK_s: c8.setKey(0x9); break;
                    case SDLK_d: c8.setKey(0xa); break;
                    case SDLK_f: c8.setKey(0xb); break;
                    case SDLK_z: c8.setKey(0xc); break;
                    case SDLK_x: c8.setKey(0xd); break;
                    case SDLK_c: c8.setKey(0xe); break;
                    case SDLK_v: c8.setKey(0xf); break;
                }
            }
        }

        c8.cycle();

        // Draw
        if (c8.draw()) {
            u32* pixels = (u32*)surface->pixels;

            for (int i = 0; i < WIDTH*HEIGHT; i++) {
                *pixels = (c8.pixel(i)) ? 0xffffffff : 0xff000000;
                pixels++;
                SDL_BlitScaled(surface_native, NULL, surface, NULL);
                SDL_UpdateWindowSurface(window);
            }
        }
    }

    // Quit
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}