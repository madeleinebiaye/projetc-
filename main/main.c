#include "../visual/visual.h"
#include "../sorting/sorting.h"
#include "../stats/stats.h"  // Include stats
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define N 100

int sorting_in_progress = 0;
int should_stop_sorting = 0;

void generate_random_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100 + 1;
    }
}

void process_events_during_sorting() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            should_stop_sorting = 1;
        } else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_SPACE) {
                should_stop_sorting = 1;
                printf("Sorting interrupted by user\n");
            }
        }
    }
}

int main() {
    srand(time(NULL));

    printf("Starting sorting visualization...\n");
    if (!init_SDL()) {
        printf("Failed to initialize SDL\n");
        return 1;
    }
    printf("SDL initialized successfully\n");

    int tableau[N];
    SortStats stats;  // Stats structure
    generate_random_array(tableau, N);
    afficher_tableau(tableau, N, -1, -1);

    SDL_Event e;
    int quit = 0;
    printf("Controls: b=Bubble, s=Selection, i=Insertion, q=Quick, m=Merge, ESC=Stop during sort\n");
    
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN && !sorting_in_progress) {
                init_stats(&stats);  // Reset stats before each sort
                switch (e.key.keysym.sym) {
                    case SDLK_b:
                        printf("Starting Bubble Sort...\n");
                        generate_random_array(tableau, N);
                        sorting_in_progress = 1;
                        should_stop_sorting = 0;
                        bubble_sort(tableau, N, &stats);
                        sorting_in_progress = 0;
                        if (!should_stop_sorting) {
                            printf("Bubble Sort completed: %d comparisons, %d memory accesses, %.3f seconds\n",
                                   stats.comparisons, stats.memory_accesses, get_execution_time(&stats));
                        }
                        break;
                    case SDLK_s:
                        printf("Starting Selection Sort...\n");
                        generate_random_array(tableau, N);
                        sorting_in_progress = 1;
                        should_stop_sorting = 0;
                        selection_sort(tableau, N, &stats);
                        sorting_in_progress = 0;
                        if (!should_stop_sorting) {
                            printf("Selection Sort completed: %d comparisons, %d memory accesses, %.3f seconds\n",
                                   stats.comparisons, stats.memory_accesses, get_execution_time(&stats));
                        }
                        break;
                    case SDLK_i:
                        printf("Starting Insertion Sort...\n");
                        generate_random_array(tableau, N);
                        sorting_in_progress = 1;
                        should_stop_sorting = 0;
                        insertion_sort(tableau, N, &stats);
                        sorting_in_progress = 0;
                        if (!should_stop_sorting) {
                            printf("Insertion Sort completed: %d comparisons, %d memory accesses, %.3f seconds\n",
                                   stats.comparisons, stats.memory_accesses, get_execution_time(&stats));
                        }
                        break;
                    case SDLK_q:
                        printf("Starting Quick Sort...\n");
                        generate_random_array(tableau, N);
                        sorting_in_progress = 1;
                        should_stop_sorting = 0;
                        quick_sort(tableau, N, &stats);
                        sorting_in_progress = 0;
                        if (!should_stop_sorting) {
                            printf("Quick Sort completed: %d comparisons, %d memory accesses, %.3f seconds\n",
                                   stats.comparisons, stats.memory_accesses, get_execution_time(&stats));
                        }
                        break;
                    case SDLK_m:
                        printf("Starting Merge Sort...\n");
                        generate_random_array(tableau, N);
                        sorting_in_progress = 1;
                        should_stop_sorting = 0;
                        merge_sort(tableau, N, &stats);
                        sorting_in_progress = 0;
                        if (!should_stop_sorting) {
                            printf("Merge Sort completed: %d comparisons, %d memory accesses, %.3f seconds\n",
                                   stats.comparisons, stats.memory_accesses, get_execution_time(&stats));
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        
        if (sorting_in_progress) {
            SDL_Delay(10);
        } else {
            SDL_Delay(16);
        }
    }

    fermer_SDL();
    printf("Program terminated\n");
    return 0;
}