#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Bubble Sort - O(n^2)
void bubble_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Partition function for Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort - O(n log n) average case
void quick_sort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// Wrapper for Quick Sort
void quick_sort_wrapper(vector<int>& arr) {
    quick_sort(arr, 0, arr.size() - 1);
}

// Generate random array
vector<int> generate_random_array(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;
    }
    return arr;
}

int main() {
    srand(time(NULL));
    int size = 5000;
    
    cout << "Generating array of " << size << " random integers...\n" << endl;
    
    // Test Bubble Sort
    vector<int> arr1 = generate_random_array(size);
    cout << "Testing Bubble Sort..." << endl;
    clock_t start = clock();
    bubble_sort(arr1);
    clock_t end = clock();
    double time_bubble = double(end - start) / CLOCKS_PER_SEC;
    cout << "Bubble Sort completed in " << time_bubble << " seconds.\n" << endl;
    
    // Test Quick Sort
    vector<int> arr2 = generate_random_array(size);
    cout << "Testing Quick Sort..." << endl;
    start = clock();
    quick_sort_wrapper(arr2);
    end = clock();
    double time_quick = double(end - start) / CLOCKS_PER_SEC;
    cout << "Quick Sort completed in " << time_quick << " seconds.\n" << endl;
    
    cout << "Quick Sort is " << (time_bubble / time_quick) << "x faster!" << endl;
    
    return 0;
}
