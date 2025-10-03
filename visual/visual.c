#include <SDL2/SDL.h>
#include <stdio.h>
#include "visual.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL; // Remove static
TTF_Font* font = NULL;

int init_SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        return 0;
    }
    if (TTF_Init() < 0) {
        printf("TTF_Init failed: %s\n", TTF_GetError());
        return 0;
    }
    window = SDL_CreateWindow("Sorting Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (!window) {
        printf("Window creation error: %s\n", SDL_GetError());
        return 0;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return 0;
    }
    font = TTF_OpenFont("fonts/DejaVuSans.ttf", 20);
    if (!font) {
        printf("Font loading failed: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return 0;
    }
    return 1;
}

float extract_int(const void* ptr) {
    return (float)(*(int*)ptr);
}

float extract_float(const void* ptr) {
    return *(float*)ptr;
}

float extract_student_grade(const void* ptr) {
    return ((Student*)ptr)->grade;
}

float extract_student_age(const void* ptr) {
    return (float)((Student*)ptr)->age;
}

void afficher_tableau_generic(void* tab, int taille, size_t size, int highlight1, int highlight2, DistributionType dist, float (*extract_value)(const void*)) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    float max_val = 1.0f;
    for (int i = 0; i < taille; i++) {
        float val = extract_value((char*)tab + i * size);
        if (val > max_val) max_val = val;
    }
    
    int bar_width = (800 - 20) / taille;
    if (bar_width < 1) bar_width = 1;
    int spacing = 1;
    for (int i = 0; i < taille; i++) {
        SDL_SetRenderDrawColor(renderer, i == highlight1 || i == highlight2 ? 0 : 255,
        i == highlight1 || i == highlight2 ? 255 : 0, 0, 255);
        float val = extract_value((char*)tab + i * size);
        int bar_height = (val * 550) / max_val;
        SDL_Rect rect = {10 + i * (bar_width + spacing), 600 - bar_height - 10, bar_width, bar_height};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void afficher_tableau(int* tab, int taille, int highlight1, int highlight2) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    int max_val = 1;
    for (int i = 0; i < taille; i++) {
        if (tab[i] > max_val) max_val = tab[i];
    }
    int bar_width = (800 - 20) / taille;
    if (bar_width < 1) bar_width = 1;
    int spacing = 1;
    for (int i = 0; i < taille; i++) {
        SDL_SetRenderDrawColor(renderer, i == highlight1 || i == highlight2 ? 0 : 255,
                               i == highlight1 || i == highlight2 ? 255 : 0, 0, 255);
        int bar_height = (tab[i] * 550) / max_val;
        SDL_Rect rect = {10 + i * (bar_width + spacing), 600 - bar_height - 10, bar_width, bar_height};
        SDL_RenderFillRect(renderer, &rect);
    }
    // Note: SDL_RenderPresent called by caller
}

void afficher_stats(SortStats* stats, const char* sort_name, int live_update, DistributionType dist) {
    SDL_Color white = {255, 255, 255, 255};
    char text[256];
    float time;
    const char* dist_name = "";
    switch (dist) {
        case DIST_RANDOM: dist_name = "Random"; break;
        case DIST_SORTED: dist_name = "Sorted"; break;
        case DIST_REVERSE: dist_name = "Reverse"; break;
        case DIST_NEARLY_SORTED: dist_name = "Nearly Sorted"; break;
        case DIST_DUPLICATES: dist_name = "Duplicates"; break;
        case DIST_PYRAMID: dist_name = "Pyramid"; break;
    }
    if (live_update) {
        stats->end_time = SDL_GetTicks();  // Mise à jour en temps réel
        time = (stats->end_time - stats->start_time) / 1000.0f;
    } else {
        time = get_execution_time(stats);  // Temps final
    }
    snprintf(text, sizeof(text),
             "%s: %d comparisons, %d accesses, %.3f s - Dist: %s",
             sort_name, stats->comparisons, stats->memory_accesses, time, dist_name);
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, white);
    if (!surface) {
        printf("Text rendering failed: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Texture creation failed: %s\n", TTF_GetError());
        SDL_FreeSurface(surface);
        return;
    }
    SDL_Rect dest = {10, 10, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}



void fermer_SDL() {
    if (font) TTF_CloseFont(font);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}