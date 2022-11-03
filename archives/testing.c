#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void chooseTile();

int main(void)
{
    srand(time(NULL));
    float a = (float) (rand() % (100 + 1 - 0) + 0) / 100;
    printf("Random value: %f\n", a);
    return 1;
}