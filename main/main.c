#include "../visual/visual.h"
#include "../sorting/sorting.h"
#include "../stats/stats.h"
#include "../utils/utils.h"  // Ajouté pour distributions
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>  // Corrigé de printf.h à stdio.h

#define N 100

int sorting_in_progress = 0;
int should_stop_sorting = 0;
DistributionType current_distribution = DIST_RANDOM;  // Par défaut : random

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
    SortStats stats;
    generate_array(tableau, N, current_distribution);  // Utilise la distribution par défaut
    afficher_tableau(tableau, N, -1, -1);
    afficher_stats(&stats, "Idle", 0, current_distribution);  // Ajouté dist
    SDL_RenderPresent(renderer);

    SDL_Event e;
    int quit = 0;
    printf("Controls: b=Bubble, s=Selection, i=Insertion, q=Quick, m=Merge, "
           "r=Random, t=Sorted, v=Reverse, n=Nearly Sorted, d=Duplicates, p=Pyramid, ESC=Stop\n");

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN && !sorting_in_progress) {
                init_stats(&stats);
                const char* sort_name = "";
                switch (e.key.keysym.sym) {
                    // Nouveaux cas pour distributions
                    case SDLK_r:
                        current_distribution = DIST_RANDOM;
                        printf("Selected: Random\n");
                        generate_array(tableau, N, current_distribution);
                        afficher_tableau(tableau, N, -1, -1);
                        afficher_stats(&stats, "Idle", 0, current_distribution);
                        SDL_RenderPresent(renderer);
                        break;
                    case SDLK_t:
                        current_distribution = DIST_SORTED;
                        printf("Selected: Sorted\n");
                        generate_array(tableau, N, current_distribution);
                        afficher_tableau(tableau, N, -1, -1);
                        afficher_stats(&stats, "Idle", 0, current_distribution);
                        SDL_RenderPresent(renderer);
                        break;
                    case SDLK_v:
                        current_distribution = DIST_REVERSE;
                        printf("Selected: Reverse\n");
                        generate_array(tableau, N, current_distribution);
                        afficher_tableau(tableau, N, -1, -1);
                        afficher_stats(&stats, "Idle", 0, current_distribution);
                        SDL_RenderPresent(renderer);
                        break;
                    case SDLK_n:
                        current_distribution = DIST_NEARLY_SORTED;
                        printf("Selected: Nearly Sorted\n");
                        generate_array(tableau, N, current_distribution);
                        afficher_tableau(tableau, N, -1, -1);
                        afficher_stats(&stats, "Idle", 0, current_distribution);
                        SDL_RenderPresent(renderer);
                        break;
                    case SDLK_d:
                        current_distribution = DIST_DUPLICATES;
                        printf("Selected: Duplicates\n");
                        generate_array(tableau, N, current_distribution);
                        afficher_tableau(tableau, N, -1, -1);
                        afficher_stats(&stats, "Idle", 0, current_distribution);
                        SDL_RenderPresent(renderer);
                        break;
                    case SDLK_p:
                        current_distribution = DIST_PYRAMID;
                        printf("Selected: Pyramid\n");
                        generate_array(tableau, N, current_distribution);
                        afficher_tableau(tableau, N, -1, -1);
                        afficher_stats(&stats, "Idle", 0, current_distribution);
                        SDL_RenderPresent(renderer);
                        break;
                    // Cas pour tris (modifiés pour utiliser la distribution choisie)
                    case SDLK_b:
                        sort_name = "Bubble Sort";
                        printf("Starting Bubble Sort...\n");
                        generate_array(tableau, N, current_distribution);  // Changé
                        sorting_in_progress = 1;
                        should_stop_sorting = 0;
                        bubble_sort(tableau, N, &stats, current_distribution);
                        sorting_in_progress = 0;
                        break;
                    case SDLK_s:
                        sort_name = "Selection Sort";
                        printf("Starting Selection Sort...\n");
                        generate_array(tableau, N, current_distribution);  // Changé
                        sorting_in_progress = 1;
                        should_stop_sorting = 0;
                        selection_sort(tableau, N, &stats, current_distribution);
                        sorting_in_progress = 0;
                        break;
                    case SDLK_i:
                        sort_name = "Insertion Sort";
                        printf("Starting Insertion Sort...\n");
                        generate_array(tableau, N, current_distribution);  // Changé
                        sorting_in_progress = 1;
                        should_stop_sorting = 0;
                        insertion_sort(tableau, N, &stats, current_distribution);
                        sorting_in_progress = 0;
                        break;
                    case SDLK_q:
                        sort_name = "Quick Sort";
                        printf("Starting Quick Sort...\n");
                        generate_array(tableau, N, current_distribution);  // Changé
                        sorting_in_progress = 1;
                        should_stop_sorting = 0;
                        quick_sort(tableau, N, &stats, current_distribution);
                        sorting_in_progress = 0;
                        break;
                    case SDLK_m:
                        sort_name = "Merge Sort";
                        printf("Starting Merge Sort...\n");
                        generate_array(tableau, N, current_distribution);  // Changé
                        sorting_in_progress = 1;
                        should_stop_sorting = 0;
                        merge_sort(tableau, N, &stats, current_distribution);
                        sorting_in_progress = 0;
                        break;
                }
                // Display final array and stats
                if (!should_stop_sorting && sort_name[0] != '\0') {
                    afficher_tableau(tableau, N, -1, -1);
                    afficher_stats(&stats, sort_name, 0, current_distribution);  // Ajouté dist
                    SDL_RenderPresent(renderer);
                    if (!should_stop_sorting) {
                        printf("%s completed: %d comparisons, %d memory accesses, %.3f seconds\n",
                               sort_name, stats.comparisons, stats.memory_accesses,
                               get_execution_time(&stats));
                    }
                }
            }
        }
        // Update stats display during sorting or idle
        if (sorting_in_progress) {
            stats.end_time = SDL_GetTicks();  // Mise à jour en temps réel
            afficher_stats(&stats, "Sorting...", 1, current_distribution);  // Ajouté dist
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        } else {
            afficher_tableau(tableau, N, -1, -1); // Redraw array
            afficher_stats(&stats, "Idle", 0, current_distribution);  // Ajouté dist
            SDL_RenderPresent(renderer);
            SDL_Delay(16);
        }
    }

    fermer_SDL();
    printf("Program terminated\n");
    return 0;
}