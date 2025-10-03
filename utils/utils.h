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

void generate_array(int arr[], int size, DistributionType dist);

#endif // UTILS_H