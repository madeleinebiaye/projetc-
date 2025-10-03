#include "utils.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>  // AJOUTÉ POUR snprintf ET RÉSOUDRE LES ERREURS

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

int compare_int(const void* a, const void* b) {
    int val_a = *(const int*)a;
    int val_b = *(const int*)b;
    return (val_a > val_b) - (val_a < val_b); // -1, 0, ou 1
}

int compare_float(const void* a, const void* b) {
    float val_a = *(const float*)a;
    float val_b = *(const float*)b;
    return (val_a > val_b) - (val_a < val_b);
}

int compare_student_age(const void* a, const void* b) {
    Student* s1 = (Student*)a;
    Student* s2 = (Student*)b;
    return (s1->age > s2->age) - (s1->age < s2->age);
}

int compare_student_grade(const void* a, const void* b) {
    Student* s1 = (Student*)a;
    Student* s2 = (Student*)b;
    return (s1->grade > s2->grade) - (s1->grade < s2->grade);
}

int compare_student_name(const void* a, const void* b) {
    Student* s1 = (Student*)a;
    Student* s2 = (Student*)b;
    return strcmp(s1->name, s2->name);
}

// Fonctions de génération pour float
void generate_float_sorted(float arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = (float)(i + 1);
    }
}

void generate_float_reverse_sorted(float arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = (float)(size - i);
    }
}

void generate_float_nearly_sorted(float arr[], int size) {
    generate_float_sorted(arr, size);
    for (int i = 0; i < size / 10; i++) {
        int idx1 = rand() % size;
        int idx2 = rand() % size;
        float temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }
}

void generate_float_duplicates(float arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = (float)(rand() % (size / 10)) / 2.0f; // Valeurs limitées pour doublons
    }
}

void generate_float_pyramid(float arr[], int size) {
    int mid = size / 2;
    for (int i = 0; i < size; i++) {
        if (i <= mid) {
            arr[i] = (float)(i + 1);
        } else {
            arr[i] = (float)(size - i);
        }
    }
}

void generate_array_float(float arr[], int size, DistributionType dist) {
    switch (dist) {
        case DIST_RANDOM:
            for (int i = 0; i < size; i++) {
                arr[i] = (float)(rand() % 10000) / 100.0f; // Valeurs entre 0 et 100
            }
            break;
        case DIST_SORTED:
            generate_float_sorted(arr, size);
            break;
        case DIST_REVERSE:
            generate_float_reverse_sorted(arr, size);
            break;
        case DIST_NEARLY_SORTED:
            generate_float_nearly_sorted(arr, size);
            break;
        case DIST_DUPLICATES:
            generate_float_duplicates(arr, size);
            break;
        case DIST_PYRAMID:
            generate_float_pyramid(arr, size);
            break;
    }
}

// Fonctions de génération pour Student (tri par grade par défaut)
void generate_student_sorted(Student arr[], int size) {
    for (int i = 0; i < size; i++) {
        snprintf(arr[i].name, 20, "Student%d", i + 1);
        arr[i].age = 15 + i % 50; // Âge entre 15 et 64
        arr[i].grade = (float)(i + 1) / 5.0f; // Notes croissantes
    }
}

void generate_student_reverse_sorted(Student arr[], int size) {
    for (int i = 0; i < size; i++) {
        snprintf(arr[i].name, 20, "Student%d", size - i);
        arr[i].age = 15 + (size - i - 1) % 50;
        arr[i].grade = (float)(size - i) / 5.0f;
    }
}

void generate_student_nearly_sorted(Student arr[], int size) {
    generate_student_sorted(arr, size);
    for (int i = 0; i < size / 10; i++) {
        int idx1 = rand() % size;
        int idx2 = rand() % size;
        Student temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }
}

void generate_student_duplicates(Student arr[], int size) {
    for (int i = 0; i < size; i++) {
        snprintf(arr[i].name, 20, "Student%d", i + 1);
        arr[i].age = rand() % 10 + 15; // Âge limité pour doublons
        arr[i].grade = (float)(rand() % (size / 10)) / 2.0f;
    }
}

void generate_student_pyramid(Student arr[], int size) {
    int mid = size / 2;
    for (int i = 0; i < size; i++) {
        snprintf(arr[i].name, 20, "Student%d", i + 1);
        arr[i].age = 15 + i % 50;
        if (i <= mid) {
            arr[i].grade = (float)(i + 1) / 5.0f;
        } else {
            arr[i].grade = (float)(size - i) / 5.0f;
        }
    }
}

void generate_student_random(Student arr[], int size) {
    for (int i = 0; i < size; i++) {
        snprintf(arr[i].name, 20, "Student%d", i + 1);
        arr[i].age = rand() % 50 + 15; // Âge entre 15 et 64
        arr[i].grade = (float)(rand() % 2000) / 100.0f; // Note entre 0 et 20
    }
}

void generate_array_student(Student arr[], int size, DistributionType dist) {
    switch (dist) {
        case DIST_RANDOM:
            generate_student_random(arr, size);
            break;
        case DIST_SORTED:
            generate_student_sorted(arr, size);
            break;
        case DIST_REVERSE:
            generate_student_reverse_sorted(arr, size);
            break;
        case DIST_NEARLY_SORTED:
            generate_student_nearly_sorted(arr, size);
            break;
        case DIST_DUPLICATES:
            generate_student_duplicates(arr, size);
            break;
        case DIST_PYRAMID:
            generate_student_pyramid(arr, size);
            break;
    }
}