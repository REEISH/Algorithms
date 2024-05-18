#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    float N;
    printf("Enter N: ");
    scanf("%f", &N);
    int ANS = 0;
    float X = N;
    float C;
    printf("Enter Constant Value to Break: ");
    scanf("%f", &C);
    while (X > 0)
    {
        X = log2f(X);
        ANS++;
    }
    printf("%d\n", ANS);
    return 0;
}