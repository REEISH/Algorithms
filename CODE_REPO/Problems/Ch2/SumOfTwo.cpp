#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cout << "Enter N:";
    cin >> N;
    vector<int> A;
    A.resize(N);
    cout << "Enter the Array Elements:\n";
    for (int i = 0; i < N; i++)
        cin >> A[i];
    int X;
    cout << "Enter an integer for Sum to be Equal:";
    cin >> X;
    sort(A.begin(), A.end());
    int L = 0;
    int R = N - 1;
    while (L < R && A[L] + A[R] != X)
    {
        if (A[L] + A[R] < X)
            L++;
        if (A[L] + A[R] > X)
            R--;
    }
    if (L >= R)
        cout << "No such Pair EXISTS";
    else
    {
        cout << L << ": " << A[L] << "," << R << ": " << A[R] << "\n";
    }
    return 0;
}