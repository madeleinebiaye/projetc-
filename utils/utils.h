#ifndef UTILS_H
#define UTILS_H

typedef enum {
    DIST_RANDOM,         // Uniform random
    DIST_SORTED,         // Already sorted
    DIST_REVERSE,        // Reverse sorted
    DIST_NEARLY_SORTED,  // Nearly sorted (small disorder)
    DIST_DUPLICATES,     // Many duplicates
    DIST_PYRAMID         // Pyramid shape
} DistributionType;

typedef struct {
    char name[20];
    int age;
    float grade;
} Student;

typedef int (*compare_func)(const void*, const void*);
int compare_int(const void* a, const void* b);
int compare_float(const void* a, const void* b);
int compare_student_age(const void* a, const void* b);
int compare_student_grade(const void* a, const void* b);
int compare_student_name(const void* a, const void* b);

void generate_array(int arr[], int size, DistributionType dist);
void generate_array_float(float arr[], int size, DistributionType dist); // Pour float
void generate_array_student(Student arr[], int size, DistributionType dist); // Pour Student

#endif // UTILS_H