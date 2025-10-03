#include "../visual/visual.h"
#include "../sorting/sorting.h"
#include "../stats/stats.h"
#include "../utils/utils.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define N 100

int sorting_in_progress = 0;
int should_stop_sorting = 0;
DistributionType current_distribution = DIST_RANDOM;
typedef enum { TYPE_INT, TYPE_FLOAT, TYPE_STUDENT } DataType;

// Print the array in console (generic for all types)
void print_array(void* tableau, int n, size_t element_size, DataType type, extract_value_func extract_value) {
    printf("Tableau (%d éléments) : ", n);
    for (int i = 0; i < n; i++) {
        float value = extract_value((char*)tableau + i * element_size);
        if (type == TYPE_INT) {
            printf("%d", (int)value);
        } else if (type == TYPE_FLOAT) {
            printf("%.2f", value);
        } else {
            printf("%.2f", value);
        }
        if (i < n - 1) printf(", ");
    }
    printf("\n");
}

// Handle SDL events during sorting
void process_events_during_sorting() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            should_stop_sorting = 1;
            printf("SDL_QUIT event received\n");
        } else if (e.type == SDL_KEYDOWN) {
            printf("Key pressed: %s\n", SDL_GetKeyName(e.key.keysym.sym));
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

    DataType current_type = TYPE_INT;
    size_t element_size = sizeof(int);
    void* tableau = malloc(N * sizeof(int));
    compare_func cmp = compare_int;
    extract_value_func extract_value = extract_int;
    generate_array((int*)tableau, N, current_distribution);
    print_array(tableau, N, element_size, current_type, extract_value);
    SortStats stats;
    init_stats(&stats);

    display_array((int*)tableau, N, -1, -1);
    display_stats(&stats, "Idle", 0, current_distribution);
    SDL_RenderPresent(renderer);

    SDL_Event e;
    int quit = 0;
    printf("Controls: b=Bubble, s=Selection, i=Insertion, q=Quick, m=Merge, "
           "r=Random, t=Sorted, v=Reverse, n=Nearly Sorted, d=Duplicates, p=Pyramid, "
           "f=Float, g=Student(grade), a=Student(age), ESC=Stop\n");

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN && !sorting_in_progress) {
                init_stats(&stats);
                const char* sort_name = "";
                switch (e.key.keysym.sym) {
                    case SDLK_r:
                        current_distribution = DIST_RANDOM;
                        printf("Selected: Random\n");
                        if (current_type == TYPE_INT) {
                            generate_array((int*)tableau, N, current_distribution);
                        } else if (current_type == TYPE_FLOAT) {
                            generate_array_float((float*)tableau, N, current_distribution);
                        } else {
                            generate_array_student((Student*)tableau, N, current_distribution);
                        }
                        print_array(tableau, N, element_size, current_type, extract_value);
                        break;
                    case SDLK_t:
                        current_distribution = DIST_SORTED;
                        printf("Selected: Sorted\n");
                        if (current_type == TYPE_INT) {
                            generate_array((int*)tableau, N, current_distribution);
                        } else if (current_type == TYPE_FLOAT) {
                            generate_array_float((float*)tableau, N, current_distribution);
                        } else {
                            generate_array_student((Student*)tableau, N, current_distribution);
                        }
                        print_array(tableau, N, element_size, current_type, extract_value);
                        break;
                    case SDLK_v:
                        current_distribution = DIST_REVERSE;
                        printf("Selected: Reverse\n");
                        if (current_type == TYPE_INT) {
                            generate_array((int*)tableau, N, current_distribution);
                        } else if (current_type == TYPE_FLOAT) {
                            generate_array_float((float*)tableau, N, current_distribution);
                        } else {
                            generate_array_student((Student*)tableau, N, current_distribution);
                        }
                        print_array(tableau, N, element_size, current_type, extract_value);
                        break;
                    case SDLK_n:
                        current_distribution = DIST_NEARLY_SORTED;
                        printf("Selected: Nearly Sorted\n");
                        if (current_type == TYPE_INT) {
                            generate_array((int*)tableau, N, current_distribution);
                        } else if (current_type == TYPE_FLOAT) {
                            generate_array_float((float*)tableau, N, current_distribution);
                        } else {
                            generate_array_student((Student*)tableau, N, current_distribution);
                        }
                        print_array(tableau, N, element_size, current_type, extract_value);
                        break;
                    case SDLK_d:
                        current_distribution = DIST_DUPLICATES;
                        printf("Selected: Duplicates\n");
                        if (current_type == TYPE_INT) {
                            generate_array((int*)tableau, N, current_distribution);
                        } else if (current_type == TYPE_FLOAT) {
                            generate_array_float((float*)tableau, N, current_distribution);
                        } else {
                            generate_array_student((Student*)tableau, N, current_distribution);
                        }
                        print_array(tableau, N, element_size, current_type, extract_value);
                        break;
                    case SDLK_p:
                        current_distribution = DIST_PYRAMID;
                        printf("Selected: Pyramid\n");
                        if (current_type == TYPE_INT) {
                            generate_array((int*)tableau, N, current_distribution);
                        } else if (current_type == TYPE_FLOAT) {
                            generate_array_float((float*)tableau, N, current_distribution);
                        } else {
                            generate_array_student((Student*)tableau, N, current_distribution);
                        }
                        print_array(tableau, N, element_size, current_type, extract_value);
                        break;
                    case SDLK_f:
                        current_type = TYPE_FLOAT;
                        element_size = sizeof(float);
                        free(tableau);
                        tableau = malloc(N * sizeof(float));
                        cmp = compare_float;
                        extract_value = extract_float;
                        generate_array_float((float*)tableau, N, current_distribution);
                        printf("Selected: Float\n");
                        print_array(tableau, N, element_size, current_type, extract_value);
                        break;
                    case SDLK_g:
                        current_type = TYPE_STUDENT;
                        element_size = sizeof(Student);
                        free(tableau);
                        tableau = malloc(N * sizeof(Student));
                        cmp = compare_student_grade;
                        extract_value = extract_student_grade;
                        generate_array_student((Student*)tableau, N, current_distribution);
                        printf("Selected: Student (by grade)\n");
                        print_array(tableau, N, element_size, current_type, extract_value);
                        break;
                    case SDLK_a:
                        current_type = TYPE_STUDENT;
                        element_size = sizeof(Student);
                        free(tableau);
                        tableau = malloc(N * sizeof(Student));
                        cmp = compare_student_age;
                        extract_value = extract_student_age;
                        generate_array_student((Student*)tableau, N, current_distribution);
                        printf("Selected: Student (by age)\n");
                        print_array(tableau, N, element_size, current_type, extract_value);
                        break;
                    case SDLK_b:
                        sort_name = "Bubble Sort";
                        printf("Starting Bubble Sort...\n");
                        if (current_type == TYPE_INT) {
                            generate_array((int*)tableau, N, current_distribution);
                            print_array(tableau, N, element_size, current_type, extract_value);
                            sorting_in_progress = 1;
                            should_stop_sorting = 0;
                            bubble_sort_int((int*)tableau, N, &stats, current_distribution);
                        } else {
                            if (current_type == TYPE_FLOAT)
                                generate_array_float((float*)tableau, N, current_distribution);
                            else
                                generate_array_student((Student*)tableau, N, current_distribution);
                            print_array(tableau, N, element_size, current_type, extract_value);
                            sorting_in_progress = 1;
                            should_stop_sorting = 0;
                            bubble_sort(tableau, N, element_size, &stats, current_distribution, cmp, extract_value);
                        }
                        sorting_in_progress = 0;
                        print_array(tableau, N, element_size, current_type, extract_value);
                        break;
                    case SDLK_s:
                        sort_name = "Selection Sort";
                        printf("Starting Selection Sort...\n");
                        if (current_type == TYPE_INT) {
                            generate_array((int*)tableau, N, current_distribution);
                            print_array(tableau, N, element_size, current_type, extract_value);
                            sorting_in_progress = 1;
                            should_stop_sorting = 0;
                            selection_sort_int((int*)tableau, N, &stats, current_distribution);
                        } else {
                            if (current_type == TYPE_FLOAT)
                                generate_array_float((float*)tableau, N, current_distribution);
                            else
                                generate_array_student((Student*)tableau, N, current_distribution);
                            print_array(tableau, N, element_size, current_type, extract_value);
                            sorting_in_progress = 1;
                            should_stop_sorting = 0;
                            selection_sort(tableau, N, element_size, &stats, current_distribution, cmp, extract_value);
                        }
                        sorting_in_progress = 0;
                        print_array(tableau, N, element_size, current_type, extract_value);
                        break;
                    case SDLK_i:
                        sort_name = "Insertion Sort";
                        printf("Starting Insertion Sort...\n");
                        if (current_type == TYPE_INT) {
                            generate_array((int*)tableau, N, current_distribution);
                            print_array(tableau, N, element_size, current_type, extract_value);
                            sorting_in_progress = 1;
                            should_stop_sorting = 0;
                            insertion_sort_int((int*)tableau, N, &stats, current_distribution);
                        } else {
                            if (current_type == TYPE_FLOAT)
                                generate_array_float((float*)tableau, N, current_distribution);
                            else
                                generate_array_student((Student*)tableau, N, current_distribution);
                            print_array(tableau, N, element_size, current_type, extract_value);
                            sorting_in_progress = 1;
                            should_stop_sorting = 0;
                            insertion_sort(tableau, N, element_size, &stats, current_distribution, cmp, extract_value);
                        }
                        sorting_in_progress = 0;
                        print_array(tableau, N, element_size, current_type, extract_value);
                        break;
                    case SDLK_q:
                        sort_name = "Quick Sort";
                        printf("Starting Quick Sort...\n");
                        if (current_type == TYPE_INT) {
                            generate_array((int*)tableau, N, current_distribution);
                            print_array(tableau, N, element_size, current_type, extract_value);
                            sorting_in_progress = 1;
                            should_stop_sorting = 0;
                            quick_sort_int((int*)tableau, N, &stats, current_distribution);
                        } else {
                            if (current_type == TYPE_FLOAT)
                                generate_array_float((float*)tableau, N, current_distribution);
                            else
                                generate_array_student((Student*)tableau, N, current_distribution);
                            print_array(tableau, N, element_size, current_type, extract_value);
                            sorting_in_progress = 1;
                            should_stop_sorting = 0;
                            quick_sort(tableau, N, element_size, &stats, current_distribution, cmp, extract_value);
                        }
                        sorting_in_progress = 0;
                        print_array(tableau, N, element_size, current_type, extract_value);
                        break;
                    case SDLK_m:
                        sort_name = "Merge Sort";
                        printf("Starting Merge Sort...\n");
                        if (current_type == TYPE_INT) {
                            generate_array((int*)tableau, N, current_distribution);
                            print_array(tableau, N, element_size, current_type, extract_value);
                            sorting_in_progress = 1;
                            should_stop_sorting = 0;
                            merge_sort_int((int*)tableau, N, &stats, current_distribution);
                        } else {
                            if (current_type == TYPE_FLOAT)
                                generate_array_float((float*)tableau, N, current_distribution);
                            else
                                generate_array_student((Student*)tableau, N, current_distribution);
                            print_array(tableau, N, element_size, current_type, extract_value);
                            sorting_in_progress = 1;
                            should_stop_sorting = 0;
                            merge_sort(tableau, N, element_size, &stats, current_distribution, cmp, extract_value);
                        }
                        sorting_in_progress = 0;
                        print_array(tableau, N, element_size, current_type, extract_value);
                        break;
                }
                if (current_type == TYPE_INT) {
                    display_array((int*)tableau, N, -1, -1);
                } else {
                    display_array_generic(tableau, N, element_size, -1, -1, current_distribution, extract_value);
                }
                display_stats(&stats, sort_name[0] ? sort_name : "Idle", 0, current_distribution);
                SDL_RenderPresent(renderer);
                if (!should_stop_sorting && sort_name[0] != '\0') {
                    printf("%s completed: %d comparisons, %d memory accesses, %.3f seconds\n",
                           sort_name, stats.comparisons, stats.memory_accesses,
                           get_execution_time(&stats));
                }
            }
        }
        if (sorting_in_progress) {
            stats.end_time = SDL_GetTicks();
            display_stats(&stats, "Sorting...", 1, current_distribution);
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        } else {
            if (current_type == TYPE_INT) {
                display_array((int*)tableau, N, -1, -1);
            } else {
                display_array_generic(tableau, N, element_size, -1, -1, current_distribution, extract_value);
            }
            display_stats(&stats, "Idle", 0, current_distribution);
            SDL_RenderPresent(renderer);
            SDL_Delay(16);
        }
    }

    free(tableau);
    close_SDL();
    printf("Program terminated\n");
    return 0;
}
