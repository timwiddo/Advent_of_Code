#include <stdio.h>
#include <stdbool.h>

#define MAX_ROWS 1000
#define MAX_COLS 100

bool isReportSafe(int levels[], int count) {
    if (count < 2) return false;

    bool increasing = levels[1] > levels[0];
    bool consistent = true;

    for (int i = 1; i < count; i++) {
        int diff = levels[i] - levels[i - 1];

        if (diff == 0 || diff < -3 || diff > 3) {
            consistent = false;
            break;
        }

        if ((increasing && diff < 0) || (!increasing && diff > 0)) {
            consistent = false;
            break;
        }
    }

    return consistent;
}


bool isReportSafeWithDampener(int levels[], int count) {

    if (isReportSafe(levels, count)) {
        return true;
    }


    for (int i = 0; i < count; i++) {
        int temp[MAX_COLS];
        int tempIndex = 0;


        for (int j = 0; j < count; j++) {
            if (j != i) {
                temp[tempIndex++] = levels[j];
            }
        }

        if (isReportSafe(temp, tempIndex)) {
            return true;
        }
    }

    return false;
}

int readInputFile(const char *filename, int numbers[MAX_ROWS][MAX_COLS], int *rowCounts) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int row = 0;
    while (!feof(file) && row < MAX_ROWS) {
        int col = 0;
        while (fscanf(file, "%d", &numbers[row][col]) == 1) {
            col++;
            if (getc(file) == '\n' || col >= MAX_COLS) {
                break;
            }
        }
        rowCounts[row] = col;
        row++;
    }

    fclose(file);
    return row;
}

int main() {
    int numbers[MAX_ROWS][MAX_COLS];
    int rowCounts[MAX_ROWS];
    int rows;

    rows = readInputFile("C:/Coding/AdventOfCode_Day2/Day2_Data", numbers, rowCounts);
    if (rows == -1) {
        return 1; // Error reading the file
    }

    // Count the number of safe reports
    int safeCount = 0;
    for (int i = 0; i < rows; i++) {
        if (isReportSafeWithDampener(numbers[i], rowCounts[i])) {
            safeCount++;
        }
    }
    
    printf("Number of safe reports with Problem Dampener: %d\n", safeCount);

    return 0;
}

