#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NUMBERS 100000 //assumed it is less than that by scrolling through the data

// Function to read tuples from a file

   /*   Explained while loop
    *
    *        3   4
    *        2   5
    *   After the first iteration:
    *   left[0] is 3.
    *   right[0] is 4.
    *
    */


int readTuplesFromFile(const char *filename, int *left, int *right) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file '%s'\n", filename);
        return -1;
    }

    int count = 0;
    while (fscanf(file, "%d   %d", &left[count], &right[count]) == 2) {
        count++;
        if (count >= MAX_NUMBERS) {
            printf("Warning: Maximum number of tuples (%d) reached.\n", MAX_NUMBERS);
            break;
        }
    }

    fclose(file);
    return count;
}

// Function to compare two ints (for use in qsort)
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to calculate the total distance between pairs
int calculateTotalDistance(int *left, int *right, int count) {
    int totalDistance = 0;
    for (int i = 0; i < count; i++) {
        totalDistance += abs(left[i] - right[i]);
    }
    return totalDistance;
}

int countOccurrences(int *array, int size, int number) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] == number) {
            count++;
        }
    }
    return count;
}

int calculateSimilarityScore(int *left, int *right, int leftSize, int rightSize) {
    int similarityScore = 0;
    for (int i = 0; i < leftSize; i++) {
        int count = countOccurrences(right, rightSize, left[i]);
        similarityScore += left[i] * count;
    }
    return similarityScore;
}

int main() {
    const char *filename = "C:/Users/Tim/Desktop/AOC_Day1_Data.txt";

    int left[MAX_NUMBERS];
    int right[MAX_NUMBERS];

    // Read tuples from the file
    int count = readTuplesFromFile(filename, left, right);
    if (count <= 0) {
        printf("No valid data found.\n");
        return 1;
    }

    // Sort both arrays
    qsort(left, count, sizeof(int), compare);
    qsort(right, count, sizeof(int), compare);


    int totalDistance = calculateTotalDistance(left, right, count);
    int similarityScore = calculateSimilarityScore(left, right, count, count);

    // Print the result
    printf("Total Distance: %d\n", totalDistance);
    printf("Similarity Score: %d\n", similarityScore);

    return 0;
}



