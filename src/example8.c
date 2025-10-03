#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_POINTS 5000000

// Structure to hold a point
typedef struct {
    double x;
    double y;
} Point;

// Calculate distance between two points
double calculate_distance(Point p1, Point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

// Find the closest pair using brute force - O(n^2)
double find_closest_pair_bruteforce(Point* points, int n, int* idx1, int* idx2) {
    double min_dist = 1e9;
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = calculate_distance(points[i], points[j]);
            if (dist < min_dist) {
                min_dist = dist;
                *idx1 = i;
                *idx2 = j;
            }
        }
    }
    return min_dist;
}

// Calculate centroid of points
Point calculate_centroid(Point* points, int n) {
    Point centroid = {0.0, 0.0};
    
    for (int i = 0; i < n; i++) {
        centroid.x += points[i].x;
        centroid.y += points[i].y;
    }
    
    centroid.x /= n;
    centroid.y /= n;
    
    return centroid;
}

// Calculate average distance from centroid
double average_distance_from_centroid(Point* points, int n) {
    Point centroid = calculate_centroid(points, n);
    double total_distance = 0.0;
    
    for (int i = 0; i < n; i++) {
        total_distance += calculate_distance(points[i], centroid);
    }
    
    return total_distance / n;
}

// Generate random points
void generate_random_points(Point* points, int n) {
    for (int i = 0; i < n; i++) {
        points[i].x = (double)rand() / RAND_MAX * 1000.0;
        points[i].y = (double)rand() / RAND_MAX * 1000.0;
    }
}

int main() {
    printf("Computational Geometry Performance Test\n");
    printf("Number of points: %d\n\n", NUM_POINTS);
    
    // Allocate points
    Point* points = (Point*)malloc(NUM_POINTS * sizeof(Point));
    
    // Generate random points
    printf("Generating random points...\n");
    generate_random_points(points, NUM_POINTS);
    
    // Calculate centroid and average distance
    printf("Calculating centroid and average distances...\n");
    double avg_dist = average_distance_from_centroid(points, NUM_POINTS);
    printf("Average distance from centroid: %.4f\n", avg_dist);
    
    // Note: We use a smaller subset for closest pair to keep runtime reasonable
    int subset_size = 2000;
    printf("\nFinding closest pair in subset of %d points...\n", subset_size);
    int idx1 = 0, idx2 = 0;
    double min_dist = find_closest_pair_bruteforce(points, subset_size, &idx1, &idx2);
    printf("Minimum distance: %.4f (between points %d and %d)\n", min_dist, idx1, idx2);
    
    // Clean up
    free(points);
    
    printf("\nDone! Profile will show:\n");
    printf("  - calculate_distance called many times\n");
    printf("  - Time distribution across geometric calculations\n");
    
    return 0;
}
