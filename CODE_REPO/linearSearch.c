# include <stdio.h>
// Implementation of linear search
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
    printf("Enter a integer n :");
    scanf("%d",&n);
    int A[n];
    printf("Enter a array of n integers :");
    scanArray(A,n);
    int v;
    printf("Enter a integer v you want to search :");
    scanf("%d",&v);
    int j=0;
    for(int i=0;i<n;i++)
    {
        
        if(A[i]== v)
        {
            printf("%d",i+1);
            j +=1;
        }
        if(i==n-1 && j==0)
        {
            printf("NIL");
        }
    }
printf("\n");

}