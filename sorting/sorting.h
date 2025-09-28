#ifndef SORTING_H
#define SORTING_H

#include "../visual/visual.h"  // Include for visualization functions
#include "../stats/stats.h"    // Include for SortStats

// Global variables
extern int sorting_in_progress;  // Flag to indicate if sorting is running
extern int should_stop_sorting;  // Flag to stop sorting on key press

// Function prototypes for sorting algorithms
void bubble_sort(int arr[], int n, SortStats* stats);
void selection_sort(int arr[], int n, SortStats* stats);
void insertion_sort(int arr[], int n, SortStats* stats);
void quick_sort(int arr[], int n, SortStats* stats);
void merge_sort(int arr[], int n, SortStats* stats);

// Helper prototypes (with n and stats passed for visualization and stats)
int partition(int arr[], int low, int high, int n, SortStats* stats);
void quicksort(int arr[], int low, int high, int n, SortStats* stats);
void merge(int arr[], int low, int mid, int high, int n, SortStats* stats);
void mergesort(int arr[], int low, int high, int n, SortStats* stats);
void process_events_during_sorting(void);  // Declare event processing function

#endif // SORTING_H