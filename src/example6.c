#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 1000000
#define SEARCH_COUNT 10000

// Linear search - O(n)
int linear_search(int* array, int size, int target) {
    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            return i;
        }
    }
    return -1;
}

// Binary search - O(log n) - requires sorted array
int binary_search(int* array, int size, int target) {
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (array[mid] == target) {
            return mid;
        }
        if (array[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// Comparison function for qsort
int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Function to perform multiple searches
void perform_searches(int* array, int size, int count, int use_binary) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        int target = rand() % (size * 2);  // Some will be found, some won't
        int result;
        
        if (use_binary) {
            result = binary_search(array, size, target);
        } else {
            result = linear_search(array, size, target);
        }
        
        if (result != -1) {
            found++;
        }
    }
    printf("Found %d out of %d searches\n", found, count);
}

int main() {
    printf("Search Algorithm Performance Test\n");
    printf("Array size: %d elements\n", ARRAY_SIZE);
    printf("Number of searches: %d\n\n", SEARCH_COUNT);
    
    // Allocate and initialize array
    printf("Allocating and initializing array...\n");
    int* array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i * 2;  // Even numbers
    }
    
    // Perform linear searches
    printf("\nPerforming %d linear searches...\n", SEARCH_COUNT);
    perform_searches(array, ARRAY_SIZE, SEARCH_COUNT, 0);
    
    printf("\nLinear search complete!\n");
    printf("Profile will show linear_search taking most of the time.\n");
    
    // Clean up
    free(array);
    
    return 0;
}
