#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum_numbers(const char *numbers) {
  
    int sum = 0;
    char *numbers_copy = strdup(numbers);
    char *token = strtok(numbers_copy, ",");

    while (token != NULL) {
        sum += atoi(token);
        token = strtok(NULL, ",");
    }

    free(numbers_copy); 
    return sum;
}

int add(const char* input)
{
  if(*input == '\0')
  {
    return 0;
  }
  else
  {
    sum_numbers(input);
  }
  
}

