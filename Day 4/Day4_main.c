#include <stdio.h>
#include <string.h>
#define SIZE 140

char input[SIZE][SIZE+1];

int Horizontal(int i, int j, const char tosearch[]) {
    if (j <= SIZE - 4) {
        return strncmp(&input[i][j], tosearch, 4) == 0;
    }
    return 0;
}

int Vertical(int i, int j, const char tosearch[]) {
    if (i <= SIZE - 4) {
        int match = 1;
        for (int k = 0; k < 4; k++) {
            if (input[i+k][j] != tosearch[k]) {
                match = 0;
            }
        }
        return match;
    }
    return 0;
}

int DiagLeft(int i, int j, const char tosearch[]) {
    if (i <= SIZE - 4 && j <= SIZE-4) {
        int match = 1;
        for (int k = 0; k < 4; k++) {
            if (input[i+k][j+k] != tosearch[k]) {
                match = 0;
            }
        }
        return match;
    }
    return 0;
}

int DiagRight(int i, int j, const char tosearch[]) {
    if (i <= SIZE - 4 && j >= 4-1) {
        int match = 1;
        for (int k = 0; k < 4; k++) {
            if (input[i+k][j-k] != tosearch[k]) {
                match = 0;
            }
        }
        return match;
    }
    return 0;
}

int CountDiamondPattern() {
    int count = 0;

    for (int i = 0; i <= SIZE-3; i++) {
        for (int j = 0; j <= SIZE-3; j++) {
            int valid = 0;
            if (input[i+1][j+1] == 'A') {
                valid = 1;
                if (!((input[i][j] == 'M' && input[i+2][j+2] == 'S') ||
                      (input[i][j] == 'S' && input[i+2][j+2] == 'M'))) {
                    valid = 0;
                }
                if (!((input[i+2][j] == 'M' && input[i][j+2] == 'S') ||
                      (input[i+2][j] == 'S' && input[i][j+2] == 'M'))) {
                    valid = 0;
                }
            }
            count += valid;
        }
    }

    return count;
}

int main() {
    FILE* f = fopen("C:/Coding/AdventOfCode_Day4/Day4_Input", "r");

    for (int i = 0; i < SIZE; i++) {
        fscanf(f, "%s ", &input[i]);
    }

    int count_patterns = 0;
    int count_diamond = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            count_patterns += Horizontal(i, j, "XMAS");
            count_patterns += Horizontal(i, j, "SAMX");

            count_patterns += Vertical(i, j, "XMAS");
            count_patterns += Vertical(i, j, "SAMX");

            count_patterns += DiagLeft(i, j, "XMAS");
            count_patterns += DiagLeft(i, j, "SAMX");

            count_patterns += DiagRight(i, j, "XMAS");
            count_patterns += DiagRight(i, j, "SAMX");
        }
    }

    count_diamond = CountDiamondPattern();

    printf("Pattern count (XMAS/SAMX): %d\n", count_patterns);
    printf("Diamond count: %d\n", count_diamond);

    fclose(f);
    return 0;
}

