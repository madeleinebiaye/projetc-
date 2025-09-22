#include <SDL2/SDL.h>
#include <stdio.h>
#include "visual.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int init_SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        return 0;
    }
    window = SDL_CreateWindow("Visualisation Tri", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    if (!window) {
        printf("Erreur creation window: %s\n", SDL_GetError());
        return 0;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur creation renderer: %s\n", SDL_GetError());
        return 0;
    }
    return 1;
}

void afficher_tableau(int* tab, int taille) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // fond noir
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // colonnes rouges

    int largeur_col = 50;
    int espace = 10;

    for (int i = 0; i < taille; i++) {
        SDL_Rect rect = { i * (largeur_col + espace) + 50, 480 - tab[i]*50, largeur_col, tab[i]*50 };
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}

void fermer_SDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
