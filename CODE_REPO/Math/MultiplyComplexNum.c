#include <stdio.h>
#include <stdlib.h>

int main()
{
    float A, B, C, D;
    printf("Enter Complex Number 1: ");
    scanf("%f%f", &A, &B);
    printf("Enter Complex Number 2: ");
    scanf("%f%f", &C, &D);
    double M1 = ((double)A + (double)B) * ((double)C + (double)D);
    double M2 = ((double)A - (double)B) * ((double)C - (double)D);
    double M3 = (double)B * (double)D;
    double CA = ((double)M1 - (double)M2) / 2.0;
    double RA = ((double)M1 + (double)M2) / 2.0 - (double)2 * M3;
    printf("ANSWER : Real -- %lf | Complex -- %lf\n", RA, CA);
    return 0;
}