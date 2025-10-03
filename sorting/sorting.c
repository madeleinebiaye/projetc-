#include "sorting.h"
#include <SDL2/SDL.h>
#include <string.h>

extern SDL_Renderer* renderer; // Access renderer from visual.c

// Fonctions pour int (versions originales renommées avec _int)

// Bubble Sort pour int
void bubble_sort_int(int arr[], int n, SortStats* stats, DistributionType dist) {
    int i, j, temp;
    int swapped;
    
    start_timer(stats);
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            process_events_during_sorting();
            if (should_stop_sorting) {
                stop_timer(stats);
                return;
            }
            afficher_tableau(arr, n, j, j + 1);
            stats->end_time = SDL_GetTicks();
            afficher_stats(stats, "Bubble Sort", 1, dist);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
            
            increment_comparisons(stats);
            increment_memory_accesses(stats, 2);
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
                increment_memory_accesses(stats, 3);
                
                afficher_tableau(arr, n, j, j + 1);
                stats->end_time = SDL_GetTicks();
                afficher_stats(stats, "Bubble Sort", 1, dist);
                SDL_RenderPresent(renderer);
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
    stop_timer(stats);
    afficher_tableau(arr, n, -1, -1);
    afficher_stats(stats, "Bubble Sort", 0, dist);
    SDL_RenderPresent(renderer);
}

// Selection Sort pour int
void selection_sort_int(int arr[], int n, SortStats* stats, DistributionType dist) {
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
            stats->end_time = SDL_GetTicks();
            afficher_stats(stats, "Selection Sort", 1, dist);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
            
            increment_comparisons(stats);
            increment_memory_accesses(stats, 2);
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
            increment_memory_accesses(stats, 3);
            
            afficher_tableau(arr, n, i, min_index);
            stats->end_time = SDL_GetTicks();
            afficher_stats(stats, "Selection Sort", 1, dist);
            SDL_RenderPresent(renderer);
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
    afficher_stats(stats, "Selection Sort", 0, dist);
    SDL_RenderPresent(renderer);
}

// Insertion Sort pour int
void insertion_sort_int(int arr[], int n, SortStats* stats, DistributionType dist) {
    int i, j, key;
    
    start_timer(stats);
    for (i = 1; i < n; i++) {
        key = arr[i];
        increment_memory_accesses(stats, 1);
        j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            process_events_during_sorting();
            if (should_stop_sorting) {
                stop_timer(stats);
                return;
            }
            increment_comparisons(stats);
            increment_memory_accesses(stats, 1);
            afficher_tableau(arr, n, j, i);
            stats->end_time = SDL_GetTicks();
            afficher_stats(stats, "Insertion Sort", 1, dist);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
            
            arr[j + 1] = arr[j];
            increment_memory_accesses(stats, 2);
            j--;
        }
        
        arr[j + 1] = key;
        increment_memory_accesses(stats, 1);
        afficher_tableau(arr, n, j + 1, -1);
        stats->end_time = SDL_GetTicks();
        afficher_stats(stats, "Insertion Sort", 1, dist);
        SDL_RenderPresent(renderer);
    }
    stop_timer(stats);
    afficher_tableau(arr, n, -1, -1);
    afficher_stats(stats, "Insertion Sort", 0, dist);
    SDL_RenderPresent(renderer);
}

// Partition pour int
int partition_int(int arr[], int low, int high, int n, SortStats* stats, DistributionType dist) {
    int pivot = arr[high];
    int i = low - 1;
    int j, temp;
    
    increment_memory_accesses(stats, 1);
    
    for (j = low; j < high; j++) {
        process_events_during_sorting();
        if (should_stop_sorting) {
            stop_timer(stats);
            return -1;
        }
        afficher_tableau(arr, n, i + 1, j);
        stats->end_time = SDL_GetTicks();
        afficher_stats(stats, "Quick Sort", 1, dist);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        
        increment_comparisons(stats);
        increment_memory_accesses(stats, 1);
        if (arr[j] < pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            increment_memory_accesses(stats, 3);
            
            afficher_tableau(arr, n, i, j);
            stats->end_time = SDL_GetTicks();
            afficher_stats(stats, "Quick Sort", 1, dist);
            SDL_RenderPresent(renderer);
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
    increment_memory_accesses(stats, 3);
    
    afficher_tableau(arr, n, i + 1, high);
    stats->end_time = SDL_GetTicks();
    afficher_stats(stats, "Quick Sort", 1, dist);
    SDL_RenderPresent(renderer);
    SDL_Delay(100);
    process_events_during_sorting();
    if (should_stop_sorting) {
        stop_timer(stats);
        return -1;
    }
    
    return i + 1;
}

// Quicksort pour int
void quicksort_int(int arr[], int low, int high, int n, SortStats* stats, DistributionType dist) {
    if (low < high) {
        int pi = partition_int(arr, low, high, n, stats, dist);
        if (pi == -1) return;
        quicksort_int(arr, low, pi - 1, n, stats, dist);
        quicksort_int(arr, pi + 1, high, n, stats, dist);
    }
}

// Quick Sort pour int
void quick_sort_int(int arr[], int n, SortStats* stats, DistributionType dist) {
    start_timer(stats);
    quicksort_int(arr, 0, n - 1, n, stats, dist);
    stop_timer(stats);
    afficher_tableau(arr, n, -1, -1);
    afficher_stats(stats, "Quick Sort", 0, dist);
    SDL_RenderPresent(renderer);
}

// Merge pour int
void merge_int(int arr[], int low, int mid, int high, int n, SortStats* stats, DistributionType dist) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int L[n1], R[n2];
    int i, j, k;
    
    for (i = 0; i < n1; i++) {
        L[i] = arr[low + i];
        increment_memory_accesses(stats, 2);
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        increment_memory_accesses(stats, 2);
    }
    
    i = 0; j = 0; k = low;
    
    while (i < n1 && j < n2) {
        process_events_during_sorting();
        if (should_stop_sorting) {
            stop_timer(stats);
            return;
        }
        afficher_tableau(arr, n, low + i, mid + 1 + j);
        stats->end_time = SDL_GetTicks();
        afficher_stats(stats, "Merge Sort", 1, dist);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        
        increment_comparisons(stats);
        increment_memory_accesses(stats, 2);
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            increment_memory_accesses(stats, 2);
            i++;
        } else {
            arr[k] = R[j];
            increment_memory_accesses(stats, 2);
            j++;
        }
        k++;
        
        afficher_tableau(arr, n, k - 1, -1);
        stats->end_time = SDL_GetTicks();
        afficher_stats(stats, "Merge Sort", 1, dist);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) {
            stop_timer(stats);
            return;
        }
    }
    
    while (i < n1) {
        arr[k] = L[i];
        increment_memory_accesses(stats, 2);
        i++; k++;
        afficher_tableau(arr, n, k - 1, -1);
        stats->end_time = SDL_GetTicks();
        afficher_stats(stats, "Merge Sort", 1, dist);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) {
            stop_timer(stats);
            return;
        }
    }
    
    while (j < n2) {
        arr[k] = R[j];
        increment_memory_accesses(stats, 2);
        j++; k++;
        afficher_tableau(arr, n, k - 1, -1);
        stats->end_time = SDL_GetTicks();
        afficher_stats(stats, "Merge Sort", 1, dist);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) {
            stop_timer(stats);
            return;
        }
    }
}

// Mergesort pour int
void mergesort_int(int arr[], int low, int high, int n, SortStats* stats, DistributionType dist) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        
        mergesort_int(arr, low, mid, n, stats, dist);
        if (should_stop_sorting) return;
        mergesort_int(arr, mid + 1, high, n, stats, dist);
        if (should_stop_sorting) return;
        merge_int(arr, low, mid, high, n, stats, dist);
        stats->end_time = SDL_GetTicks();
        afficher_tableau(arr, n, low, mid + 1);
        afficher_stats(stats, "Merge Sort", 1, dist);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) return;
    }
}

// Merge Sort pour int
void merge_sort_int(int arr[], int n, SortStats* stats, DistributionType dist) {
    start_timer(stats);
    mergesort_int(arr, 0, n - 1, n, stats, dist);
    stop_timer(stats);
    afficher_tableau(arr, n, -1, -1);
    afficher_stats(stats, "Merge Sort", 0, dist);
    SDL_RenderPresent(renderer);
}

// Versions génériques pour tout type

// Bubble Sort générique
void bubble_sort(void* arr, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract) {
    char* array = (char*)arr;
    char* temp = malloc(size);
    int swapped;
    
    start_timer(stats);
    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            process_events_during_sorting();
            if (should_stop_sorting) {
                stop_timer(stats);
                free(temp);
                return;
            }
            afficher_tableau_generic(arr, n, size, j, j + 1, dist, extract);
            stats->end_time = SDL_GetTicks();
            afficher_stats(stats, "Bubble Sort", 1, dist);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
            
            increment_comparisons(stats);
            increment_memory_accesses(stats, 2);
            if (cmp(array + j * size, array + (j + 1) * size) > 0) {
                memcpy(temp, array + j * size, size);
                memcpy(array + j * size, array + (j + 1) * size, size);
                memcpy(array + (j + 1) * size, temp, size);
                swapped = 1;
                increment_memory_accesses(stats, 3);
                
                afficher_tableau_generic(arr, n, size, j, j + 1, dist, extract);
                stats->end_time = SDL_GetTicks();
                afficher_stats(stats, "Bubble Sort", 1, dist);
                SDL_RenderPresent(renderer);
                SDL_Delay(100);
                process_events_during_sorting();
                if (should_stop_sorting) {
                    stop_timer(stats);
                    free(temp);
                    return;
                }
            }
        }
        if (swapped == 0) break;
    }
    stop_timer(stats);
    afficher_tableau_generic(arr, n, size, -1, -1, dist, extract);
    afficher_stats(stats, "Bubble Sort", 0, dist);
    SDL_RenderPresent(renderer);
    free(temp);
}

// Selection Sort générique
void selection_sort(void* arr, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract) {
    char* array = (char*)arr;
    char* temp = malloc(size);
    
    start_timer(stats);
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            process_events_during_sorting();
            if (should_stop_sorting) {
                stop_timer(stats);
                free(temp);
                return;
            }
            afficher_tableau_generic(arr, n, size, min_index, j, dist, extract);
            stats->end_time = SDL_GetTicks();
            afficher_stats(stats, "Selection Sort", 1, dist);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
            
            increment_comparisons(stats);
            increment_memory_accesses(stats, 2);
            if (cmp(array + j * size, array + min_index * size) < 0) {
                min_index = j;
            }
        }
        if (min_index != i) {
            memcpy(temp, array + i * size, size);
            memcpy(array + i * size, array + min_index * size, size);
            memcpy(array + min_index * size, temp, size);
            increment_memory_accesses(stats, 3);
            
            afficher_tableau_generic(arr, n, size, i, min_index, dist, extract);
            stats->end_time = SDL_GetTicks();
            afficher_stats(stats, "Selection Sort", 1, dist);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
            process_events_during_sorting();
            if (should_stop_sorting) {
                stop_timer(stats);
                free(temp);
                return;
            }
        }
    }
    stop_timer(stats);
    afficher_tableau_generic(arr, n, size, -1, -1, dist, extract);
    afficher_stats(stats, "Selection Sort", 0, dist);
    SDL_RenderPresent(renderer);
    free(temp);
}

// Insertion Sort générique
void insertion_sort(void* arr, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract) {
    char* array = (char*)arr;
    char* key = malloc(size);
    
    start_timer(stats);
    for (int i = 1; i < n; i++) {
        memcpy(key, array + i * size, size);
        increment_memory_accesses(stats, 1);
        int j = i - 1;
        
        while (j >= 0 && cmp(array + j * size, key) > 0) {
            process_events_during_sorting();
            if (should_stop_sorting) {
                stop_timer(stats);
                free(key);
                return;
            }
            increment_comparisons(stats);
            increment_memory_accesses(stats, 1);
            afficher_tableau_generic(arr, n, size, j, i, dist, extract);
            stats->end_time = SDL_GetTicks();
            afficher_stats(stats, "Insertion Sort", 1, dist);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
            
            memcpy(array + (j + 1) * size, array + j * size, size);
            increment_memory_accesses(stats, 2);
            j--;
        }
        
        memcpy(array + (j + 1) * size, key, size);
        increment_memory_accesses(stats, 1);
        afficher_tableau_generic(arr, n, size, j + 1, -1, dist, extract);
        stats->end_time = SDL_GetTicks();
        afficher_stats(stats, "Insertion Sort", 1, dist);
        SDL_RenderPresent(renderer);
    }
    stop_timer(stats);
    afficher_tableau_generic(arr, n, size, -1, -1, dist, extract);
    afficher_stats(stats, "Insertion Sort", 0, dist);
    SDL_RenderPresent(renderer);
    free(key);
}

// Partition générique
int partition(void* arr, int low, int high, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract) {
    char* array = (char*)arr;
    char* pivot = malloc(size);
    char* temp = malloc(size);
    memcpy(pivot, array + high * size, size);
    int i = low - 1;
    
    increment_memory_accesses(stats, 1);
    
    for (int j = low; j < high; j++) {
        process_events_during_sorting();
        if (should_stop_sorting) {
            stop_timer(stats);
            free(pivot);
            free(temp);
            return -1;
        }
        afficher_tableau_generic(arr, n, size, i + 1, j, dist, extract);
        stats->end_time = SDL_GetTicks();
        afficher_stats(stats, "Quick Sort", 1, dist);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        
        increment_comparisons(stats);
        increment_memory_accesses(stats, 1);
        if (cmp(array + j * size, pivot) < 0) {
            i++;
            memcpy(temp, array + i * size, size);
            memcpy(array + i * size, array + j * size, size);
            memcpy(array + j * size, temp, size);
            increment_memory_accesses(stats, 3);
            
            afficher_tableau_generic(arr, n, size, i, j, dist, extract);
            stats->end_time = SDL_GetTicks();
            afficher_stats(stats, "Quick Sort", 1, dist);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
            process_events_during_sorting();
            if (should_stop_sorting) {
                stop_timer(stats);
                free(pivot);
                free(temp);
                return -1;
            }
        }
    }
    
    memcpy(temp, array + (i + 1) * size, size);
    memcpy(array + (i + 1) * size, array + high * size, size);
    memcpy(array + high * size, temp, size);
    increment_memory_accesses(stats, 3);
    
    afficher_tableau_generic(arr, n, size, i + 1, high, dist, extract);
    stats->end_time = SDL_GetTicks();
    afficher_stats(stats, "Quick Sort", 1, dist);
    SDL_RenderPresent(renderer);
    SDL_Delay(100);
    process_events_during_sorting();
    if (should_stop_sorting) {
        stop_timer(stats);
        free(pivot);
        free(temp);
        return -1;
    }
    
    free(pivot);
    free(temp);
    return i + 1;
}

// Quicksort générique
void quicksort(void* arr, int low, int high, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract) {
    if (low < high) {
        int pi = partition(arr, low, high, n, size, stats, dist, cmp, extract);
        if (pi == -1) return;
        quicksort(arr, low, pi - 1, n, size, stats, dist, cmp, extract);
        quicksort(arr, pi + 1, high, n, size, stats, dist, cmp, extract);
    }
}

// Quick Sort générique
void quick_sort(void* arr, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract) {
    start_timer(stats);
    quicksort(arr, 0, n - 1, n, size, stats, dist, cmp, extract);
    stop_timer(stats);
    afficher_tableau_generic(arr, n, size, -1, -1, dist, extract);
    afficher_stats(stats, "Quick Sort", 0, dist);
    SDL_RenderPresent(renderer);
}

// Merge générique
void merge(void* arr, int low, int mid, int high, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    char* L = malloc(n1 * size);
    char* R = malloc(n2 * size);
    int i, j, k;
    
    for (i = 0; i < n1; i++) {
        memcpy(L + i * size, (char*)arr + (low + i) * size, size);
        increment_memory_accesses(stats, 2);
    }
    for (j = 0; j < n2; j++) {
        memcpy(R + j * size, (char*)arr + (mid + 1 + j) * size, size);
        increment_memory_accesses(stats, 2);
    }
    
    i = 0; j = 0; k = low;
    
    while (i < n1 && j < n2) {
        process_events_during_sorting();
        if (should_stop_sorting) {
            stop_timer(stats);
            free(L);
            free(R);
            return;
        }
        afficher_tableau_generic(arr, n, size, low + i, mid + 1 + j, dist, extract);
        stats->end_time = SDL_GetTicks();
        afficher_stats(stats, "Merge Sort", 1, dist);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        
        increment_comparisons(stats);
        increment_memory_accesses(stats, 2);
        if (cmp(L + i * size, R + j * size) <= 0) {
            memcpy((char*)arr + k * size, L + i * size, size);
            increment_memory_accesses(stats, 2);
            i++;
        } else {
            memcpy((char*)arr + k * size, R + j * size, size);
            increment_memory_accesses(stats, 2);
            j++;
        }
        k++;
        
        afficher_tableau_generic(arr, n, size, k - 1, -1, dist, extract);
        stats->end_time = SDL_GetTicks();
        afficher_stats(stats, "Merge Sort", 1, dist);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) {
            stop_timer(stats);
            free(L);
            free(R);
            return;
        }
    }
    
    while (i < n1) {
        memcpy((char*)arr + k * size, L + i * size, size);
        increment_memory_accesses(stats, 2);
        i++; k++;
        afficher_tableau_generic(arr, n, size, k - 1, -1, dist, extract);
        stats->end_time = SDL_GetTicks();
        afficher_stats(stats, "Merge Sort", 1, dist);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) {
            stop_timer(stats);
            free(L);
            free(R);
            return;
        }
    }
    
    while (j < n2) {
        memcpy((char*)arr + k * size, R + j * size, size);
        increment_memory_accesses(stats, 2);
        j++; k++;
        afficher_tableau_generic(arr, n, size, k - 1, -1, dist, extract);
        stats->end_time = SDL_GetTicks();
        afficher_stats(stats, "Merge Sort", 1, dist);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) {
            stop_timer(stats);
            free(L);
            free(R);
            return;
        }
    }
    
    free(L);
    free(R);
}

// Mergesort générique
void mergesort(void* arr, int low, int high, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        
        mergesort(arr, low, mid, n, size, stats, dist, cmp, extract);
        if (should_stop_sorting) return;
        mergesort(arr, mid + 1, high, n, size, stats, dist, cmp, extract);
        if (should_stop_sorting) return;
        merge(arr, low, mid, high, n, size, stats, dist, cmp, extract);
        stats->end_time = SDL_GetTicks();
        afficher_tableau_generic(arr, n, size, low, mid + 1, dist, extract);
        afficher_stats(stats, "Merge Sort", 1, dist);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) return;
    }
}

// Merge Sort générique
void merge_sort(void* arr, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract) {
    start_timer(stats);
    mergesort(arr, 0, n - 1, n, size, stats, dist, cmp, extract);
    stop_timer(stats);
    afficher_tableau_generic(arr, n, size, -1, -1, dist, extract);
    afficher_stats(stats, "Merge Sort", 0, dist);
    SDL_RenderPresent(renderer);
}