#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define RUN 10
#define MAXNUM 100000
#define MAX 100000000

int main()
{
    freopen("testCaseOfArray.in", "w", stdout);
    srand(time(NULL));

    for (int i = 1; i <= RUN; i++)
    {

        int NUM = 1 + rand() % MAXNUM;

        printf("%d\n", NUM);

        for (int j = 1; j <= NUM; j++)
        {
            printf("%d ", rand() % MAX);
        }
        printf("\n");
    }
    fclose(stdout);
    return 0;
}