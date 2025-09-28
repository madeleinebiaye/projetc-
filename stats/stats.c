#include "stats.h"

void init_stats(SortStats* stats) {
    stats->comparisons = 0;
    stats->memory_accesses = 0;
    stats->start_time = 0;
    stats->end_time = 0;
}

void increment_comparisons(SortStats* stats) {
    stats->comparisons++;
}

void increment_memory_accesses(SortStats* stats, int count) {
    stats->memory_accesses += count;
}

void start_timer(SortStats* stats) {
    stats->start_time = SDL_GetTicks();
}

void stop_timer(SortStats* stats) {
    stats->end_time = SDL_GetTicks();
}

float get_execution_time(SortStats* stats) {
    return (stats->end_time - stats->start_time) / 1000.0f;  // Convert ms to seconds
}