#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBERS 1000
#define MAX_DELIMITER_LENGTH 10

void throw_exception(int negatives[], int count) {
    printf("Exception: Negatives not allowed: ");
    for (int i = 0; i < count; i++) {
        printf("%d", negatives[i]);
        if (i < count - 1) {
            printf(", ");
        }
    }
    printf("\n");
    exit(1);
}

void add_delimiters(const char *delimiter_start, const char *delimiter_end, char *delimiters) {
    while (delimiter_start < delimiter_end) {
        const char *end = strchr(delimiter_start, ']');
        if (end == NULL || end > delimiter_end) break;
        strncat(delimiters, delimiter_start, end - delimiter_start);
        delimiter_start = end + 1;
        if (*delimiter_start == '[') delimiter_start++;
    }
}

void parse_delimiters(const char *numbers, char *delimiters, const char **num_start) {
    if (strncmp(numbers, "//", 2) == 0) {
        const char *delimiter_end = strstr(numbers, "\n");
        if (delimiter_end != NULL) {
            *num_start = delimiter_end + 1;
            const char *delimiter_start = numbers + 2;
            if (*delimiter_start == '[') {
                delimiter_start++;
                add_delimiters(delimiter_start, delimiter_end, delimiters);
            } else {
                delimiters[0] = *delimiter_start;
                delimiters[1] = '\0';
            }
        }
    }
}

void add_numbers(int num, int *negatives, int* sum, int *negative_count)
{
    if (num < 0) {
        negatives[(*negative_count)++] = num;
    } else if (num <= 1000) {
        *sum += num;
    }
}
void tokenize_and_sum(const char *num_start, const char *delimiters, int *sum, int *negatives, int *negative_count) {
    char *numbers_copy = strdup(num_start);
    char *token = strtok(numbers_copy, delimiters);

    while (token != NULL) {
        int num = atoi(token);
        add_numbers(num, negatives, sum, negative_count);
        token = strtok(NULL, delimiters);
    }

    free(numbers_copy);
}

int add(const char *numbers) {
    if (numbers == NULL || *numbers == '\0') {
        return 0;
    }

    char delimiters[MAX_DELIMITER_LENGTH] = ",\n";
    const char *num_start = numbers;
    int sum = 0;
    int negatives[MAX_NUMBERS];
    int negative_count = 0;

    parse_delimiters(numbers, delimiters, &num_start);
    tokenize_and_sum(num_start, delimiters, &sum, negatives, &negative_count);

    if (negative_count > 0) {
        throw_exception(negatives, negative_count);
    }

    return sum;
}

