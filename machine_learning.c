#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000

int main(void)
{
    FILE *fptr;
    char line[MAX_LINE_LENGTH];

    if ((fptr = fopen("tic-tac-toe.data", "r")) == NULL)
    {
        printf("Error opening file!");
        exit(1);
    }

    while(fgets(line, MAX_LINE_LENGTH, fptr))
    {
        printf("%s", line);
    }

    fclose(fptr);
    return 0;
}