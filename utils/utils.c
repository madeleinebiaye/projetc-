#include "utils.h"
#include <stdlib.h>
#include <time.h>

void generate_sorted(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1; // 1, 2, 3, ..., size
    }
}

void generate_reverse_sorted(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = size - i; // size, size-1, ..., 1
    }
}

void generate_nearly_sorted(int arr[], int size) {
    generate_sorted(arr, size);
    for (int i = 0; i < size / 10; i++) { // Quelques swaps aléatoires (10%)
        int idx1 = rand() % size;
        int idx2 = rand() % size;
        int temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }
}

void generate_duplicates(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (size / 10); // Valeurs entre 0 et size/10 pour doublons
    }
}

void generate_pyramid(int arr[], int size) {
    int mid = size / 2;
    for (int i = 0; i < size; i++) {
        if (i <= mid) {
            arr[i] = i + 1; // Croît jusqu'au milieu
        } else {
            arr[i] = size - i; // Décroît après
        }
    }
}

void generate_array(int arr[], int size, DistributionType dist) {
    switch (dist) {
        case DIST_RANDOM:
            for (int i = 0; i < size; i++) {
                arr[i] = rand() % 100 + 1;
            }
            break;
        case DIST_SORTED:
            generate_sorted(arr, size);
            break;
        case DIST_REVERSE:
            generate_reverse_sorted(arr, size);
            break;
        case DIST_NEARLY_SORTED:
            generate_nearly_sorted(arr, size);
            break;
        case DIST_DUPLICATES:
            generate_duplicates(arr, size);
            break;
        case DIST_PYRAMID:
            generate_pyramid(arr, size);
            break;
    }
}