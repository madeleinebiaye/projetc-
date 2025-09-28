#include "sorting.h"
#include <SDL2/SDL.h>

extern int should_stop_sorting;  // Declare global variable from main.c

// Implements Bubble Sort with step-by-step visualization
// Principle: Repeatedly swaps adjacent elements if they are in wrong order.
// Passes through the array until no more swaps are needed.
void bubble_sort(int arr[], int n) {
    int i, j, temp;
    int swapped;
    
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        
        for (j = 0; j < n - i - 1; j++) {
            process_events_during_sorting();  // Check events
            if (should_stop_sorting) return;  // Stop if requested
            afficher_tableau(arr, n, j, j + 1);
            SDL_Delay(100);  // Delay to make the animation visible
            
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
                
                // Visualize after swap
                afficher_tableau(arr, n, j, j + 1);
                SDL_Delay(100);
                process_events_during_sorting();  // Check after swap
                if (should_stop_sorting) return;
            }
        }
        
        // If no swaps in this pass, array is sorted
        if (swapped == 0) break;
    }
    
    // Final display of the sorted array
    afficher_tableau(arr, n, -1, -1);
}

// Implements Selection Sort with step-by-step visualization
// Principle: Finds the minimum element in the unsorted part and swaps it with the first unsorted element.
void selection_sort(int arr[], int n) {
    int i, j, min_index, temp;
    
    for (i = 0; i < n - 1; i++) {
        min_index = i;  // Assume the minimum is at position i
        
        for (j = i + 1; j < n; j++) {
            process_events_during_sorting();
            if (should_stop_sorting) return;
            afficher_tableau(arr, n, min_index, j);
            SDL_Delay(100);  // Delay to make the animation visible
            
            if (arr[j] < arr[min_index]) {
                min_index = j;  // Update min_index if a smaller element is found
            }
        }
        
        // If min_index changed, swap arr[i] and arr[min_index]
        if (min_index != i) {
            temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
            
            // Visualize the swap
            afficher_tableau(arr, n, i, min_index);
            SDL_Delay(100);  // Delay after swap
            process_events_during_sorting();
            if (should_stop_sorting) return;
        }
    }
    
    // Final display of the sorted array
    afficher_tableau(arr, n, -1, -1);
}

// Implements Insertion Sort with step-by-step visualization
// Principle: Builds a sorted subarray by inserting each new element into its correct position.
void insertion_sort(int arr[], int n) {
    int i, j, key;
    
    for (i = 1; i < n; i++) {
        key = arr[i];  // Element to insert
        j = i - 1;
        
        // Move elements of arr[0..i-1] that are greater than key
        while (j >= 0 && arr[j] > key) {
            process_events_during_sorting();
            if (should_stop_sorting) return;
            afficher_tableau(arr, n, j, i);
            SDL_Delay(100);  // Delay for animation
            
            arr[j + 1] = arr[j];  // Shift element
            j--;
        }
        
        arr[j + 1] = key;  // Insert key
        
        // Visualize after insertion
        afficher_tableau(arr, n, j + 1, -1);
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) return;
    }
    
    // Final display
    afficher_tableau(arr, n, -1, -1);
}

// Helper function for QuickSort partition with visualization
// Principle: Chooses a pivot and partitions the array around it.
int partition(int arr[], int low, int high, int n) {
    int pivot = arr[high];  // Choose last element as pivot
    int i = low - 1;  // Index of smaller element
    int j, temp;
    
    for (j = low; j < high; j++) {
        process_events_during_sorting();
        if (should_stop_sorting) return -1;  // Return invalid index to signal stop
        afficher_tableau(arr, n, j, high);
        SDL_Delay(100);
        
        if (arr[j] < pivot) {
            i++;
            // Swap arr[i] and arr[j]
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            
            // Visualize swap
            afficher_tableau(arr, n, i, j);
            SDL_Delay(100);
            process_events_during_sorting();
            if (should_stop_sorting) return -1;
        }
    }
    
    // Swap arr[i+1] and arr[high] (pivot)
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    // Visualize final pivot swap
    afficher_tableau(arr, n, i + 1, high);
    SDL_Delay(100);
    process_events_during_sorting();
    if (should_stop_sorting) return -1;
    
    return i + 1;  // Return partition index
}

// Recursive QuickSort function
// Principle: Divide-and-conquer: partition and recurse on subarrays.
void quicksort(int arr[], int low, int high, int n) {
    if (low < high) {
        int pi = partition(arr, low, high, n);
        if (pi == -1) return;  // Stop if interrupted
        quicksort(arr, low, pi - 1, n);  // Left subarray
        quicksort(arr, pi + 1, high, n);  // Right subarray
    }
}

// Main QuickSort function
void quick_sort(int arr[], int n) {
    quicksort(arr, 0, n - 1, n);
    
    // Final display
    afficher_tableau(arr, n, -1, -1);
}

// Helper function to merge two halves with visualization
// Principle: Merges two sorted subarrays into one.
void merge(int arr[], int low, int mid, int high, int n) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int L[n1], R[n2];  // Temporary arrays
    int i, j, k;
    
    // Copy data to temporary arrays
    for (i = 0; i < n1; i++) L[i] = arr[low + i];
    for (j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    i = 0; j = 0; k = low;
    
    while (i < n1 && j < n2) {
        process_events_during_sorting();
        if (should_stop_sorting) return;
        afficher_tableau(arr, n, low + i, mid + 1 + j);
        SDL_Delay(100);
        
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
        
        // Visualize after copy
        afficher_tableau(arr, n, k - 1, -1);
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) return;
    }
    
    // Copy remaining elements from L
    while (i < n1) {
        arr[k] = L[i];
        i++; k++;
        afficher_tableau(arr, n, k - 1, -1);
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) return;
    }
    
    // Copy remaining elements from R
    while (j < n2) {
        arr[k] = R[j];
        j++; k++;
        afficher_tableau(arr, n, k - 1, -1);
        SDL_Delay(100);
        process_events_during_sorting();
        if (should_stop_sorting) return;
    }
}

// Recursive MergeSort function
// Principle: Divide-and-conquer: split, sort recursively, then merge.
void mergesort(int arr[], int low, int high, int n) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        
        mergesort(arr, low, mid, n);
        if (should_stop_sorting) return;  // Check after recursive call
        mergesort(arr, mid + 1, high, n);
        if (should_stop_sorting) return;  // Check after recursive call
        merge(arr, low, mid, high, n);
    }
}

// Main MergeSort function
void merge_sort(int arr[], int n) {
    mergesort(arr, 0, n - 1, n);
    
    // Final display
    afficher_tableau(arr, n, -1, -1);
}