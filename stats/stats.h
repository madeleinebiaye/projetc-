#ifndef STATS_H
#define STATS_H

#include <SDL2/SDL.h>  // For Uint32 (SDL_GetTicks)

// Structure to hold sorting statistics
typedef struct {
    int comparisons;      // Number of comparisons
    int memory_accesses;  // Number of array reads/writes
    Uint32 start_time;    // Start time in milliseconds (SDL_GetTicks)
    Uint32 end_time;      // End time in milliseconds
} SortStats;

// Function prototypes
void init_stats(SortStats* stats);  // Initialize stats
void increment_comparisons(SortStats* stats);  // Increment comparison counter
void increment_memory_accesses(SortStats* stats, int count);  // Increment memory accesses
void start_timer(SortStats* stats);  // Start the timer
void stop_timer(SortStats* stats);  // Stop the timer
float get_execution_time(SortStats* stats);  // Get execution time in seconds

#endif // STATS_H