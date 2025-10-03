#include <stdio.h>
#include <time.h>

// Inefficient recursive Fibonacci
long long fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

// Efficient iterative Fibonacci
long long fibonacci_iterative(int n) {
    if (n <= 1) return n;
    
    long long prev = 0, curr = 1;
    for (int i = 2; i <= n; i++) {
        long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

int main() {
    int n = 40;
    long long result;
    clock_t start, end;
    double cpu_time_used;
    
    // Test recursive version
    printf("Computing Fibonacci(%d) recursively...\n", n);
    start = clock();
    result = fibonacci_recursive(n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Recursive result: %lld (Time: %.4f seconds)\n", result, cpu_time_used);
    
    // Test iterative version
    printf("\nComputing Fibonacci(%d) iteratively...\n", n);
    start = clock();
    result = fibonacci_iterative(n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Iterative result: %lld (Time: %.4f seconds)\n", result, cpu_time_used);
    
    return 0;
}
