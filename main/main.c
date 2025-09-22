#include "../visual/visual.h"
#include "../sorting/sorting.h"  // Include sorting functions
#include <SDL2/SDL.h>
#include <stdlib.h>  // For rand()
#include <time.h>    // For srand()

#define N 100  // Array size as per project example

// Function to generate random array (values 1 to 100 for visualization)
void generate_random_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100 + 1;  // Random between 1 and 100
    }
}

int main() {
    srand(time(NULL));  // Seed random

    if (!init_SDL()) return 1;

    int tableau[N];
    generate_random_array(tableau, N);  // Initial random array
    afficher_tableau(tableau, N, -1, -1);  // Initial display

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                // Select sorting algorithm based on key press
                switch (e.key.keysym.sym) {
                    case SDLK_b:  // 'b' for Bubble Sort
                        generate_random_array(tableau, N);  // Reset array
                        bubble_sort(tableau, N);
                        break;
                    case SDLK_s:  // 's' for Selection Sort
                        generate_random_array(tableau, N);
                        selection_sort(tableau, N);
                        break;
                    case SDLK_i:  // 'i' for Insertion Sort
                        generate_random_array(tableau, N);
                        insertion_sort(tableau, N);
                        break;
                    case SDLK_q:  // 'q' for Quick Sort
                        generate_random_array(tableau, N);
                        quick_sort(tableau, N);
                        break;
                    case SDLK_m:  // 'm' for Merge Sort
                        generate_random_array(tableau, N);
                        merge_sort(tableau, N);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    fermer_SDL();
    return 0;
}