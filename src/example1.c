#include <stdio.h>
#include <stdbool.h>

// Inefficient function to check if a number is prime
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    // Inefficient: checking all odd numbers up to n-1
    for (int i = 3; i < n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to count primes up to a limit
int count_primes(int limit) {
    int count = 0;
    for (int i = 2; i <= limit; i++) {
        if (is_prime(i)) {
            count++;
        }
    }
    return count;
}

int main() {
    int limit = 10000;
    
    printf("Counting prime numbers up to %d...\n", limit);
    int prime_count = count_primes(limit);
    printf("Found %d prime numbers.\n", prime_count);
    
    return 0;
}
