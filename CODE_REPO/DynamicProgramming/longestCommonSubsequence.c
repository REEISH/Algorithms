#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
typedef long long int LONG;

void printLCS(int M, int N, LONG B[M][N], char *X, int i, int j)
{
    if (i == 0 || j == 0)
    {
        return;
    }
    if (B[i - 1][j - 1] == 2)
    {
        printLCS(M, N, B, X, i - 1, j - 1);
        printf("%c", X[i - 1]);
    }
    else if (B[i - 1][j - 1] == 1)
    {
        printLCS(M, N, B, X, i - 1, j);
    }
    else
    {
        printLCS(M, N, B, X, i, j - 1);
    }
}

void LCSlength(char *X, char *Y, int M, int N)
{
    // M=X.length and N=Y.length
    LONG B[M][N];
    LONG C[M + 1][N + 1];
    for (int i = 0; i <= M; i++)
    {
        C[i][0] = 0;
    }
    for (int j = 0; j <= N; j++)
    {
        C[0][j] = 0;
    }
    for (int i = 1; i <= M; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                C[i][j] = C[i - 1][j - 1] + 1;
                B[i - 1][j - 1] = 2;
            }
            else if (C[i - 1][j] >= C[i][j - 1])
            {
                C[i][j] = C[i - 1][j];
                B[i - 1][j - 1] = 1;
            }
            else
            {
                C[i][j] = C[i][j - 1];
                B[i - 1][j - 1] = 0;
            }
        }
    }
    printf("LENGTH:%lld\n", C[M][N]);
    printLCS(M, N, B, X, M, N);
    printf("\n");
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    int M, N; // Max num of elements
    printf("Enter a integer M:");
    scanf("%d", &M);
    char X[M];
    printf("Enter an array of M charhecters:\n");
    scanf("%s", X);
    printf("Enter a integer N:");
    scanf("%d", &N);
    char Y[N];
    printf("Enter an array of N charhecters:\n");
    scanf("%s", Y);
    LCSlength(X, Y, M, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}
// Note for a given sequence ,there may be more than one LCS, yes this is possible()
// Eg - X = baababab, Y = ababbabba 
// has LCS(1) = bababa and LCS(2) = baabba,both of length 6.
// It just prints one of the LCS,that depends on which argument is passed first.
