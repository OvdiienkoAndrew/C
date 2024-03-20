// min ... max
#include <iostream>
using namespace std;
const int N_MAX = 100000000;
int A[N_MAX];

void swap(int & a, int & b)
{
    int t = a; a=b; b=t;
}

int iMin(int A[], int l, int n)
{
    int imin = l;
    for(int i=l+1; i<n; ++i)
    {
        if(A[imin]>A[i])
        imin = i;
    }
    return imin;
}

int main()
{
    int n;
    cout << "\n\n\tN ? = "; cin >> n;
    cout << "\n\n";
    for(int i=0; i<n; ++i)
    {
        cout << "\tA[" << i << "] ? = ";
        cin >> A[i];
    }
    cout << "\n\n";
    for(int i=0; i<n-1; ++i)
    {
        int imin = iMin(A,i,n);
        swap(A[i], A[imin]);
    }
    for(int i=0; i<n; ++i)
    {
        cout << "\tA[" << i << "]  = " << A[i] << endl;
    }
    cout << "\n\n";
    return 0;
}