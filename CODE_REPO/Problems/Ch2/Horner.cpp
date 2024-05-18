#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N; // N >= 0
    cout << "Degree of Polynomial:";
    cin >> N;
    vector<float> A;
    A.resize(N + 1);
    cout << "Enter the coefficient of the polynomial (in order highest to lowest):\n";
    for (int i = 0; i <= N; i++)
        cin >> A[i];
    float X;
    cout << "Enter the value at which Polynomial has to be calculated:\n";
    cin >> X;
    long double V = A[0];
    for (int i = 1; i <= N; i++)
        V = V * (long double)X + A[i];
    cout << "Value: " << V << "\n";
    return 0;
}