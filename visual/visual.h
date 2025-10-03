#ifndef VISUAL_H
#define VISUAL_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../stats/stats.h"
#include "../utils/utils.h"  // Added for DistributionType

extern SDL_Renderer* renderer; // Add this
int init_SDL();                    // Initializes SDL and creates window + renderer
void display_array(int* tab, int taille, int highlight1, int highlight2); // Displays array as bars
void display_array_generic(void* tab, int taille, size_t size, int highlight1, int highlight2, DistributionType dist, float (*extract_value)(const void*));
float extract_int(const void* ptr);
float extract_float(const void* ptr);
float extract_student_grade(const void* ptr);
float extract_student_age(const void* ptr);
void display_stats(SortStats* stats, const char* sort_name , int live_update , DistributionType dist); // Display stats
void close_SDL();                  // Cleans up SDL

#endif