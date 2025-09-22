#include "../visual/visual.h"
#include "../sorting/sorting.h"  // Include sorting functions
#include <SDL2/SDL.h>
#include <stdlib.h>  // For rand()
#include <time.h>    // For srand()
#include <stdio.h>   // For printf

#define N 100  // Array size as per project example

// Global variables for sorting state
int sorting_in_progress = 0;  // Flag to indicate if sorting is running
int should_stop_sorting = 0;  // Flag to stop sorting on key press

// Function to generate random array (values 1 to 100 for visualization)
void generate_random_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100 + 1;  // Random between 1 and 100
    }
}

// Callback function for sorting algorithms to process SDL events
void process_events_during_sorting() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            should_stop_sorting = 1;
        } else if (e.type == SDL_KEYDOWN) {
            // Stop sorting if any key is pressed during animation
            if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_SPACE) {
                should_stop_sorting = 1;
                printf("Sorting interrupted by user\n");
            }
        }
    }
}

int main() {
    srand(time(NULL));  // Seed random

    printf("Starting sorting visualization...\n");
    if (!init_SDL()) {
        printf("Failed to initialize SDL\n");
        return 1;
    }
    printf("SDL initialized successfully\n");

    int tableau[N];
    generate_random_array(tableau, N);  // Initial random array
    afficher_tableau(tableau, N, -1, -1);  // Initial display

    SDL_Event e;
    int quit = 0;
    printf("Controls: b=Bubble, s=Selection, i=Insertion, q=Quick, m=Merge, ESC=Stop during sort\n");
    
    while (!quit) {
        // Main event loop - always responsive
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN && !sorting_in_progress) {
                // Only start sorting if not already sorting
                switch (e.key.keysym.sym) {
                    case SDLK_b:  // 'b' for Bubble Sort
                        printf("Starting Bubble Sort...\n");
                        generate_random_array(tableau, N);
                        sorting_in_progress = 1;
                        should_stop_sorting = 0;
                        bubble_sort(tableau, N);
                        sorting_in_progress = 0;
                        printf("Bubble Sort completed\n");
                        break;
                    case SDLK_s:  // 's' for Selection Sort
                        printf("Starting Selection Sort...\n");
                        generate_random_array(tableau, N);
                        sorting_in_progress = 1;
                        should_stop_sorting = 0;
                        selection_sort(tableau, N);
                        sorting_in_progress = 0;
                        printf("Selection Sort completed\n");
                        break;
                    case SDLK_i:  // 'i' for Insertion Sort
                        printf("Starting Insertion Sort...\n");
                        generate_random_array(tableau, N);
                        sorting_in_progress = 1;
                        should_stop_sorting = 0;
                        insertion_sort(tableau, N);
                        sorting_in_progress = 0;
                        printf("Insertion Sort completed\n");
                        break;
                    case SDLK_q:  // 'q' for Quick Sort
                        printf("Starting Quick Sort...\n");
                        generate_random_array(tableau, N);
                        sorting_in_progress = 1;
                        should_stop_sorting = 0;
                        quick_sort(tableau, N);
                        sorting_in_progress = 0;
                        printf("Quick Sort completed\n");
                        break;
                    case SDLK_m:  // 'm' for Merge Sort
                        printf("Starting Merge Sort...\n");
                        generate_random_array(tableau, N);
                        sorting_in_progress = 1;
                        should_stop_sorting = 0;
                        merge_sort(tableau, N);
                        sorting_in_progress = 0;
                        printf("Merge Sort completed\n");
                        break;
                    default:
                        break;
                }
            }
        }
        
        // If sorting is in progress, let it continue (events processed inside sorting functions)
        if (sorting_in_progress) {
            // Small delay to not hog CPU
            SDL_Delay(10);
        } else {
            // Normal idle state
            SDL_Delay(16);  // ~60 FPS
        }
    }

    fermer_SDL();
    printf("Program terminated\n");
    return 0;
}