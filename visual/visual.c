#include <SDL2/SDL.h>
#include <stdio.h>
#include "visual.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int init_SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        return 0;
    }
    // Window size as per project example: 800x600
    window = SDL_CreateWindow("Sorting Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (!window) {
        printf("Window creation error: %s\n", SDL_GetError());
        return 0;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation error: %s\n", SDL_GetError());
        return 0;
    }
    return 1;
}

void afficher_tableau(int* tab, int taille, int highlight1, int highlight2) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Find max value to scale heights
    int max_val = 1; // Avoid division by zero
    for (int i = 0; i < taille; i++) {
        if (tab[i] > max_val) max_val = tab[i];
    }

    // Dynamic bar width and spacing
    int bar_width = (800 - 20) / taille; // Total width 800, margin 10 each side
    if (bar_width < 1) bar_width = 1; // Minimum width
    int spacing = 1; // Small spacing

    for (int i = 0; i < taille; i++) {
        // Default color: red
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        
        // Highlight color: green if index matches highlight1 or highlight2
        if (i == highlight1 || i == highlight2) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for highlights
        }
        
        // Bar rect: x = margin + i*(width+space), y = bottom - height, width, height scaled to 550 max (margin top/bottom)
        int bar_height = (tab[i] * 550) / max_val;
        SDL_Rect rect = { 10 + i * (bar_width + spacing), 600 - bar_height - 10, bar_width, bar_height };
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}

void fermer_SDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}