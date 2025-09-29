#ifndef VISUAL_H
#define VISUAL_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../stats/stats.h"

extern SDL_Renderer* renderer; // Add this
int init_SDL();                    // Initializes SDL and creates window + renderer
void afficher_tableau(int* tab, int taille, int highlight1, int highlight2); // Displays array as bars
void afficher_stats(SortStats* stats, const char* sort_name); // Display stats
void fermer_SDL();                  // Cleans up SDL

#endif