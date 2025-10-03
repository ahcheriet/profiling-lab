#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEXT_SIZE 500000
#define PATTERN_SIZE 20
#define SEARCH_COUNT 1000

// Generate random text
void generate_text(char* text, int size) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz ";
    for (int i = 0; i < size - 1; i++) {
        text[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    text[size - 1] = '\0';
}

// Naive string matching - O(n*m)
int naive_string_search(const char* text, const char* pattern) {
    int text_len = strlen(text);
    int pattern_len = strlen(pattern);
    int count = 0;
    
    for (int i = 0; i <= text_len - pattern_len; i++) {
        int j;
        for (j = 0; j < pattern_len; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == pattern_len) {
            count++;
        }
    }
    return count;
}

// Character frequency analysis
void count_character_frequency(const char* text, int* freq) {
    // Initialize frequency array
    for (int i = 0; i < 256; i++) {
        freq[i] = 0;
    }
    
    // Count each character
    for (int i = 0; text[i] != '\0'; i++) {
        freq[(unsigned char)text[i]]++;
    }
}

// Find most common character
char find_most_common(const int* freq) {
    int max_count = 0;
    char most_common = '\0';
    
    for (int i = 0; i < 256; i++) {
        if (freq[i] > max_count) {
            max_count = freq[i];
            most_common = (char)i;
        }
    }
    return most_common;
}

// Process text - wrapper function
void process_text(const char* text) {
    int freq[256];
    count_character_frequency(text, freq);
    
    char most_common = find_most_common(freq);
    printf("Most common character: '%c' with %d occurrences\n", 
           most_common, freq[(unsigned char)most_common]);
}

int main() {
    printf("String Processing Performance Test\n");
    printf("Text size: %d characters\n", TEXT_SIZE);
    printf("Pattern searches: %d\n\n", SEARCH_COUNT);
    
    // Allocate text buffer
    char* text = (char*)malloc(TEXT_SIZE * sizeof(char));
    
    // Generate random text
    printf("Generating random text...\n");
    generate_text(text, TEXT_SIZE);
    
    // Create search pattern
    char pattern[PATTERN_SIZE + 1];
    strncpy(pattern, text + 1000, PATTERN_SIZE);
    pattern[PATTERN_SIZE] = '\0';
    
    // Perform string searches
    printf("Performing pattern searches...\n");
    int total_matches = 0;
    for (int i = 0; i < SEARCH_COUNT; i++) {
        int matches = naive_string_search(text, pattern);
        total_matches += matches;
    }
    printf("Average matches per search: %.2f\n", 
           (double)total_matches / SEARCH_COUNT);
    
    // Analyze character frequency
    printf("\nAnalyzing character frequency...\n");
    process_text(text);
    
    // Clean up
    free(text);
    
    printf("\nDone! Check the profile to see function call distribution.\n");
    return 0;
}
