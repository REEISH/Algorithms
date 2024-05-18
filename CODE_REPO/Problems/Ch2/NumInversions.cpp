#include <bits/stdc++.h>

using namespace std;

long Combine(vector<int> A, int sIndex, int mIndex, int eIndex)
{
    long INV = 0;
    static int count = 0;
    vector<int> B;
    B.resize(mIndex - sIndex + 1);
    vector<int> C;
    C.resize(eIndex - mIndex);
    int L = 1;
    int R = 1;
    for (int i = 0; i < mIndex - sIndex + 1; i++)
        B[i] = A[sIndex + i - 1];
    for (int i = 0; i < eIndex - mIndex; i++)
        C[i] = A[mIndex + i];
    for (int i = sIndex; i <= eIndex; i++)
    {
        if (L <= mIndex - sIndex + 1 && R <= eIndex - mIndex)
        {
            if (B[L - 1] < C[R - 1])
            {
                A[i - 1] = B[L - 1];
                L++;
                INV = INV + R - 1;
            }
            else
            {
                A[i - 1] = C[R - 1];
                R++;
            }
        }
        else if (L <= mIndex - sIndex + 1)
        {
            A[i - 1] = B[L - 1];
            L++;
            INV = INV + R - 1;
        }
        else if (R <= eIndex - mIndex)
        {
            A[i - 1] = C[R - 1];
            R++;
        }
    }
    count++;
    // cout << count << "|" << sIndex << "|" << mIndex << "|" << eIndex << "|" << INV << "\n ";
    return INV;
}

long N_Inversions(vector<int> A, int sInsex, int eIndex)
{
    if (sInsex == eIndex)
        return 0;
    int mIndex = (sInsex + eIndex) / 2;
    return N_Inversions(A, sInsex, mIndex) + N_Inversions(A, mIndex + 1, eIndex) + Combine(A, sInsex, mIndex, eIndex);
}

int main()
{
    int N;
    cout << "Enter N:";
    cin >> N;
    vector<int> A;
    A.resize(N);
    cout << "Enter the element of the Array:\n";
    for (int i = 0; i < N; i++)
        cin >> A[i];
    cout << "Number of Inversions: " << N_Inversions(A, 1, N) << '\n';
    return 0;
}