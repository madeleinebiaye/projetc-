#ifndef SORTING_H
#define SORTING_H

#include "../visual/visual.h"  // Include for visualization functions
#include "../stats/stats.h" 
#include "../utils/utils.h"   // Include for SortStats

// Global variables
extern int sorting_in_progress;  // Flag to indicate if sorting is running
extern int should_stop_sorting;  // Flag to stop sorting on key press

// Type definition for the extraction function (AJOUTÉ POUR RÉSOUDRE L'ERREUR)
typedef float (*extract_value_func)(const void*);

// Function prototypes for sorting algorithms (versions pour int)
void bubble_sort_int(int arr[], int n, SortStats* stats, DistributionType dist);
void selection_sort_int(int arr[], int n, SortStats* stats, DistributionType dist);
void insertion_sort_int(int arr[], int n, SortStats* stats, DistributionType dist);
void quick_sort_int(int arr[], int n, SortStats* stats, DistributionType dist);
void merge_sort_int(int arr[], int n, SortStats* stats, DistributionType dist);

// Helper prototypes for int
int partition_int(int arr[], int low, int high, int n, SortStats* stats, DistributionType dist);
void quicksort_int(int arr[], int low, int high, int n, SortStats* stats, DistributionType dist);
void merge_int(int arr[], int low, int mid, int high, int n, SortStats* stats, DistributionType dist);
void mergesort_int(int arr[], int low, int high, int n, SortStats* stats, DistributionType dist);

// Function prototypes for generic sorting algorithms (avec compare_func et extract_value_func)
void bubble_sort(void* arr, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract);
void selection_sort(void* arr, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract);
void insertion_sort(void* arr, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract);
void quick_sort(void* arr, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract);
void merge_sort(void* arr, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract);

// Helper prototypes for generic (avec n, size, stats, cmp et extract)
int partition(void* arr, int low, int high, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract);
void quicksort(void* arr, int low, int high, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract);
void merge(void* arr, int low, int mid, int high, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract);
void mergesort(void* arr, int low, int high, int n, size_t size, SortStats* stats, DistributionType dist, compare_func cmp, extract_value_func extract);

void process_events_during_sorting(void);  // Declare event processing function

#endif // SORTING_H