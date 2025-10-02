#include "sorting.h"
#include <SDL2/SDL.h>

extern SDL_Renderer* renderer; // Access renderer from visual.c

// Implements Bubble Sort with step-by-step visualization
void bubble_sort(int arr[], int n, SortStats* stats) {
    int i, j, temp;
    int swapped;
    
    start_timer(stats);  // Start timing
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            process_events_during_sorting();
            if (should_stop_sorting) {
                stop_timer(stats);
                return;
            }
            afficher_tableau(arr, n, j, j + 1);
            stats->end_time = SDL_GetTicks();  // Mise à jour en temps réel
            afficher_stats(stats, "Bubble Sort", 1); // Add stats display with live update
            SDL_RenderPresent(renderer); // Update display
            SDL_Delay(100);
            
            increment_comparisons(stats);  // Count comparison
            increment_memory_accesses(stats, 2);  // Read arr[j], arr[j+1]
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
                increment_memory_accesses(stats, 3);  // Read temp, write arr[j], arr[j+1]
                
                afficher_tableau(arr, n, j, j + 1);
                stats->end_time = SDL_GetTicks();  // Mise à jour en temps réel
                afficher_stats(stats, "Bubble Sort", 1); // Add stats display with live update
                SDL_RenderPresent(renderer); // Update display
                SDL_Delay(100);
                process_events_during_sorting();
                if (should_stop_sorting) {
                    stop_timer(stats);
                    return;
                }
            }
        }
        if (swapped == 0) break;
    }
    stop_timer(stats);  // Stop timing
    afficher_tableau(arr, n, -1, -1);
    afficher_stats(stats, "Bubble Sort", 0); // Final stats display
    SDL_RenderPresent(renderer); // Update display
}

void selection_sort(int arr[], int n, SortStats* stats) {
    int i, j, min_index, temp;
    
    start_timer(stats);
    for (i = 0; i < n - 1; i++) {
        min_index = i;
        for (j = i + 1; j < n; j++) {
            process_events_during_sorting();
            if (should_stop_sorting) {
                stop_timer(stats);
                return;
            }
            afficher_tableau(arr, n, min_index, j);
            stats->end_time = SDL_GetTicks();  // Mise à jour en temps réel
            afficher_stats(stats, "Selection Sort", 1); // Add stats display with live update
            SDL_RenderPresent(renderer); // Update display
            SDL_Delay(100);
            
            increment_comparisons(stats);
            increment_memory_accesses(stats, 2);  // Read arr[j], arr[min_index]
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
            increment_memory_accesses(stats, 3);  // Read temp, write arr[i], arr[min_index]
            
            afficher_tableau(arr, n, i, min_index);
            stats->end_time = SDL_GetTicks();  // Mise à jour en temps réel
            afficher_stats(stats, "Selection Sort", 1); // Add stats display with live update
            SDL_RenderPresent(renderer); // Update display
            SDL_Delay(100);
            process_events_during_sorting();
            if (should_stop_sorting) {
                stop_timer(stats);
                return;
            }
        }
    }
    stop_timer(stats);
    afficher_tableau(arr, n, -1, -1);
    afficher_stats(stats, "Selection Sort", 0); // Final stats display
    SDL_RenderPresent(renderer); // Update display
}

void insertion_sort(int arr[], int n, SortStats* stats) {
    int i, j, key;
    
    start_timer(stats);
    for (i = 1; i < n; i++) {
        key = arr[i];
        increment_memory_accesses(stats, 1);  // Read arr[i]
        j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            process_events_during_sorting();
            if (should_stop_sorting) {
                stop_timer(stats);
                return;
            }
            increment_comparisons(stats);
            increment_memory_accesses(stats, 1);  // Read arr[j]
            afficher_tableau(arr, n, j, i);
            stats->end_time = SDL_GetTicks();  // Mise à jour en temps réel
            afficher_stats(stats, "Insertion Sort", 1); // Add stats display with live update
            SDL_RenderPresent(renderer); // Update display
            SDL_Delay(100);
            
            arr[j + 1] = arr[j];
            increment_memory_accesses(stats, 2);  // Read arr[j], write arr[j+1]
            j--;
        }
        
        arr[j + 1] = key;
        increment_memory_accesses(stats, 1);  // Write arr[j+1]
        afficher_tableau(arr, n, j + 1, -1);
        stats->end_time = SDL_GetTicks();  // Mise à jour en temps réel
        afficher_stats(stats, "Insertion Sort", 1); // Add stats display with live update
        SDL_RenderPresent(renderer); // Update display
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) {
            stop_timer(stats);
            return;
        }
    }
    stop_timer(stats);
    afficher_tableau(arr, n, -1, -1);
    afficher_stats(stats, "Insertion Sort", 0); // Final stats display
    SDL_RenderPresent(renderer); // Update display
}

int partition(int arr[], int low, int high, int n, SortStats* stats) {
    int pivot = arr[high];
    increment_memory_accesses(stats, 1);  // Read arr[high]
    int i = low - 1;
    int j, temp;
    
    for (j = low; j < high; j++) {
        process_events_during_sorting();
        if (should_stop_sorting) {
            stop_timer(stats);
            return -1;
        }
        afficher_tableau(arr, n, j, high);
        stats->end_time = SDL_GetTicks();  // Mise à jour en temps réel
        afficher_stats(stats, "Quick Sort", 1); // Add stats display with live update
        SDL_RenderPresent(renderer); // Update display
        SDL_Delay(100);
        
        increment_comparisons(stats);
        increment_memory_accesses(stats, 1);  // Read arr[j]
        if (arr[j] < pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            increment_memory_accesses(stats, 3);  // Read temp, write arr[i], arr[j]
            
            afficher_tableau(arr, n, i, j);
            stats->end_time = SDL_GetTicks();  // Mise à jour en temps réel
            afficher_stats(stats, "Quick Sort", 1); // Add stats display with live update
            SDL_RenderPresent(renderer); // Update display
            SDL_Delay(100);
            process_events_during_sorting();
            if (should_stop_sorting) {
                stop_timer(stats);
                return -1;
            }
        }
    }
    
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    increment_memory_accesses(stats, 3);  // Read temp, write arr[i+1], arr[high]
    
    afficher_tableau(arr, n, i + 1, high);
    stats->end_time = SDL_GetTicks();  // Mise à jour en temps réel
    afficher_stats(stats, "Quick Sort", 1); // Add stats display with live update
    SDL_RenderPresent(renderer); // Update display
    SDL_Delay(100);
    process_events_during_sorting();
    if (should_stop_sorting) {
        stop_timer(stats);
        return -1;
    }
    
    return i + 1;
}

void quicksort(int arr[], int low, int high, int n, SortStats* stats) {
    if (low < high) {
        int pi = partition(arr, low, high, n, stats);
        if (pi == -1) return;
        quicksort(arr, low, pi - 1, n, stats);
        quicksort(arr, pi + 1, high, n, stats);
    }
}

void quick_sort(int arr[], int n, SortStats* stats) {
    start_timer(stats);
    quicksort(arr, 0, n - 1, n, stats);
    stop_timer(stats);
    afficher_tableau(arr, n, -1, -1);
    afficher_stats(stats, "Quick Sort", 0); // Final stats display
    SDL_RenderPresent(renderer); // Update display
}

void merge(int arr[], int low, int mid, int high, int n, SortStats* stats) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int L[n1], R[n2];
    int i, j, k;
    
    for (i = 0; i < n1; i++) {
        L[i] = arr[low + i];
        increment_memory_accesses(stats, 2);  // Read arr[low+i], write L[i]
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        increment_memory_accesses(stats, 2);  // Read arr[mid+1+j], write R[j]
    }
    
    i = 0; j = 0; k = low;
    
    while (i < n1 && j < n2) {
        process_events_during_sorting();
        if (should_stop_sorting) {
            stop_timer(stats);
            return;
        }
        afficher_tableau(arr, n, low + i, mid + 1 + j);
        stats->end_time = SDL_GetTicks();  // Mise à jour en temps réel
        afficher_stats(stats, "Merge Sort", 1); // Add stats display with live update
        SDL_RenderPresent(renderer); // Update display
        SDL_Delay(100);
        
        increment_comparisons(stats);
        increment_memory_accesses(stats, 2);  // Read L[i], R[j]
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            increment_memory_accesses(stats, 2);  // Read L[i], write arr[k]
            i++;
        } else {
            arr[k] = R[j];
            increment_memory_accesses(stats, 2);  // Read R[j], write arr[k]
            j++;
        }
        k++;
        
        afficher_tableau(arr, n, k - 1, -1);
        stats->end_time = SDL_GetTicks();  // Mise à jour en temps réel
        afficher_stats(stats, "Merge Sort", 1); // Add stats display with live update
        SDL_RenderPresent(renderer); // Update display
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) {
            stop_timer(stats);
            return;
        }
    }
    
    while (i < n1) {
        arr[k] = L[i];
        increment_memory_accesses(stats, 2);  // Read L[i], write arr[k]
        i++; k++;
        afficher_tableau(arr, n, k - 1, -1);
        stats->end_time = SDL_GetTicks();  // Mise à jour en temps réel
        afficher_stats(stats, "Merge Sort", 1); // Add stats display with live update
        SDL_RenderPresent(renderer); // Update display
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) {
            stop_timer(stats);
            return;
        }
    }
    
    while (j < n2) {
        arr[k] = R[j];
        increment_memory_accesses(stats, 2);  // Read R[j], write arr[k]
        j++; k++;
        afficher_tableau(arr, n, k - 1, -1);
        stats->end_time = SDL_GetTicks();  // Mise à jour en temps réel
        afficher_stats(stats, "Merge Sort", 1); // Add stats display with live update
        SDL_RenderPresent(renderer); // Update display
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) {
            stop_timer(stats);
            return;
        }
    }
}

void mergesort(int arr[], int low, int high, int n, SortStats* stats) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        
        mergesort(arr, low, mid, n, stats);
        if (should_stop_sorting) return;
        mergesort(arr, mid + 1, high, n, stats);
        if (should_stop_sorting) return;
        merge(arr, low, mid, high, n, stats);
        stats->end_time = SDL_GetTicks();  // Mise à jour en temps réel
        afficher_tableau(arr, n, low, mid + 1);  // Ajuste les highlights si besoin
        afficher_stats(stats, "Merge Sort", 1);  // Affichage en temps réel
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) return;
    }
}

void merge_sort(int arr[], int n, SortStats* stats) {
    start_timer(stats);
    mergesort(arr, 0, n - 1, n, stats);
    stop_timer(stats);
    afficher_tableau(arr, n, -1, -1);
    afficher_stats(stats, "Merge Sort", 0); // Final stats display
    SDL_RenderPresent(renderer); // Update display
}