#include <stdio.h>
#include <stdlib.h>

void scanArray(int *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }
}

int binarySearch(int *A, int v, int start, int end)
{
    int mid = (start + end) / 2;
    int ret = -1;
    if (A[mid - 1] == v)
    {
        ret = mid - 1;
        return ret;
    }
    if (v <= A[mid - 1])
    {
        ret = binarySearch(A, v, start, mid);
    }
    else
    {
        ret = binarySearch(A, v, mid + 1, end);
    }

    
    return ret;
}

void main()
{
    int n;

    printf("Enter a integer n:");
    scanf("%d", &n);
    int array[n];
    printf("Enter a sorted array n:");
    scanArray(array, n);
    int v;
    printf("Enter a number you want to search :");
    scanf("%d", &v);
    int result;
    result = binarySearch(array,v,1,n);
    printf("%d\n",result+1);
}