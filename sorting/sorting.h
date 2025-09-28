#ifndef SORTING_H
#define SORTING_H

#include "../visual/visual.h"  // Include for visualization functions

// Function prototypes for sorting algorithms
void bubble_sort(int arr[], int n);
void selection_sort(int arr[], int n);
void insertion_sort(int arr[], int n);
void quick_sort(int arr[], int n);
void merge_sort(int arr[], int n);

// Helper prototypes (with n passed for visualization)
int partition(int arr[], int low, int high, int n);
void quicksort(int arr[], int low, int high, int n);
void merge(int arr[], int low, int mid, int high, int n);
void mergesort(int arr[], int low, int high, int n);
void process_events_during_sorting(void);  // Declare event processing function

#endif // SORTING_H