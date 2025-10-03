#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

// Function that allocates memory in a loop - good for Valgrind testing
void allocate_and_process() {
    const int iterations = 1000;
    const int size = 1024;
    
    for (int i = 0; i < iterations; i++) {
        // Allocate memory using malloc
        char* buffer = (char*)malloc(size);
        
        // Use the memory
        memset(buffer, 'A', size);
        
        // Process the data
        int sum = 0;
        for (int j = 0; j < size; j++) {
            sum += buffer[j];
        }
        
        // Free the memory (comment this out to test memory leak detection)
        free(buffer);
    }
}

// Function that allocates memory using new
void allocate_with_new() {
    const int iterations = 500;
    const int size = 2048;
    
    for (int i = 0; i < iterations; i++) {
        // Allocate array using new
        int* data = new int[size];
        
        // Initialize and process
        for (int j = 0; j < size; j++) {
            data[j] = j * j;
        }
        
        // Calculate sum
        long long sum = 0;
        for (int j = 0; j < size; j++) {
            sum += data[j];
        }
        
        // Free the memory (comment this out to test memory leak detection)
        delete[] data;
    }
}

// Function with nested allocations
void nested_allocations() {
    const int outer = 100;
    const int inner = 50;
    
    for (int i = 0; i < outer; i++) {
        char* outer_buffer = (char*)malloc(256);
        
        for (int j = 0; j < inner; j++) {
            int* inner_data = new int[128];
            
            // Use the data
            for (int k = 0; k < 128; k++) {
                inner_data[k] = i + j + k;
            }
            
            delete[] inner_data;
        }
        
        free(outer_buffer);
    }
}

int main() {
    cout << "Starting memory allocation test..." << endl;
    cout << "This program is designed to demonstrate profiling and memory analysis.\n" << endl;
    
    cout << "Phase 1: Allocating with malloc..." << endl;
    allocate_and_process();
    cout << "Phase 1 complete.\n" << endl;
    
    cout << "Phase 2: Allocating with new..." << endl;
    allocate_with_new();
    cout << "Phase 2 complete.\n" << endl;
    
    cout << "Phase 3: Nested allocations..." << endl;
    nested_allocations();
    cout << "Phase 3 complete.\n" << endl;
    
    cout << "All memory allocation tests completed!" << endl;
    cout << "Run with Valgrind to check for memory leaks and profiling." << endl;
    
    return 0;
}
