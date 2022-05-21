#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define RUN 10 //Number of Test Cases change as per need
#define MAXNUM 100000
#define MAX 100000000
// This is a boilerplate to run your code on large test cases and store the results, it does not evaluate those
// results, but tells the execution time of the code.

// use fscanf, fprintf to scan through the given input file/ to print to the output file

int main()
{
    FILE *INPUT;
    FILE *OUTPUT;
    INPUT = fopen("testCaseOfArray.in", "r"); // Change the name of input file as per requirement
    OUTPUT = fopen("SolvedProblem.out", "w"); // Change the name of output file as per requirement

    for (int i = 1; i <= RUN; i++)
    {

        clock_t clockTime;
        clockTime = clock();
        // your code goes here

        clockTime = clock() - clockTime;
        fprintf(OUTPUT, "Time taken in execution :%f\n", ((double)clockTime) / CLOCKS_PER_SEC);
    }

    fclose(INPUT);
    fclose(OUTPUT);

    return 0;
}