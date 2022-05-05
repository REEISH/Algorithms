#include <stdio.h>
 // This algorithm is only for computing the sum 
 // of 2 positive numbers written in binary format
 // Note that this is just ine way of doing this and other
 // apt solutions are also available

void scanArray(int *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&A[i]);
    }
}

void main()
{
    int n;
    printf("Enter a integer n: ");
    scanf("%d", &n);
    int A[n], B[n];
    printf("write down first int in binary: ");
    scanArray(A,n);
    printf("write down second int in binary : ");
    scanArray(B,n);
    int C[n+1];
    for (int i=0;i<n+1;i++)
    {
        C[i] = 0;
    }
    for(int i=n-1;i>=0;i--)
    {
        if(A[i]*B[i]==0)
        {
            C[i+1] += A[i]+B[i];
        }
        if(A[i]*B[i]==1)
        {
            C[i+1]  += 0;
            C[i] += 1;
        }
        if(C[i+1]==2)
        {
            C[i+1]=0;
            C[i]=1;
        }
    }
    for (int i=0;i<n+1;i++)
    {
        printf("%d",C[i]);
    }
printf("\n");
}