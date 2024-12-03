#include <stdio.h>
#include <string.h>

int part_one(FILE* f) {
    char content[20000]; //getting limit by ctrl + a on the file in CLion
    fread(content, 1, 20000, f);
    int len = strlen(content);

    int sum = 0;
    for (int i = 0; i < len - 4; i++) {
        if (strncmp(content + i, "mul(", 4) == 0) {
            i += 4;
            int a = 0;
            int b = 0;
            while (content[i] >= '0' && content[i] <= '9') {
                a *= 10; // enable 0*10+1 -> 1*10+2 -> 12*10+3 for the number 123
                a += content[i] - '0'; // -48 ASCII Shift to align char with int
                i++;
            }
            if (content[i] == ',') {
                i++;
                while (content[i] >= '0' && content[i] <= '9') {
                    b *= 10;
                    b += content[i] - '0';
                    i++;
                }
            }
            if (content[i] != ')') {
                a = 0;
            }
            sum += a * b;
        }
    }
    return sum;
}

int part_two(FILE* f) {
    char content[20000];
    fread(content, 1, 20000, f);
    int len = strlen(content);

    int sum = 0;
    int enabled = 1; // Initially mults are enabled
    for (int i = 0; i < len - 4; i++) {
        if (strncmp(content + i, "do()", 4) == 0) {
            enabled = 1; // Enable multiplication
        }
        if (i < len - 7 && strncmp(content + i, "don't()", 7) == 0) {
            enabled = 0; // Disable multiplication
        }
        if (strncmp(content + i, "mul(", 4) == 0) {
            i += 4;
            int a = 0;
            int b = 0;
            while (content[i] >= '0' && content[i] <= '9') {
                a *= 10;
                a += content[i] - '0';
                i++;
            }
            if (content[i] == ',') {
                i++;
                while (content[i] >= '0' && content[i] <= '9') {
                    b *= 10;
                    b += content[i] - '0';
                    i++;
                }
            }
            if (content[i] != ')') {
                a = 0;
            }
            sum += a * b * enabled; // Multiply by enabled flag (either 1 or 0)
        }
    }
    return sum;
}

int main() {

    FILE* f = fopen("C:/Coding/AdventOdCode_Day3/Day3_Input", "r");
    if (f == NULL) {
        perror("Error opening file");
        return 1;
    }
    int sum_part_one = part_one(f);

    // Rewind file pointer to the beginning for part 2
    rewind(f);

    int sum_part_two = part_two(f);

    fclose(f);

    printf("Sum for part one: %d\n", sum_part_one);
    printf("Sum for part two: %d\n", sum_part_two);

    return 0;
}



