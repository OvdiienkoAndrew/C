#include <iostream>
using namespace std;
const int N_MAX = 10000;
int A[N_MAX][N_MAX];
void swap(int & a, int & b)
{
    int t = a; a = b; b=t;
}
void swap (int x[], int y[], int size)
{
    for(int i=0; i<size; ++i)
        swap(x[i], y[i]);
}
int iMin(int A[N_MAX][N_MAX], int N, int l)
{
    int imin = l;
    for(int i=l+1; i<N; ++i)
    {
        if(A[imin][0]>A[i][0])
        imin = i;
    }
    return imin;
}
void input_arr(int A[N_MAX][N_MAX], int n, int m)
{
    for(int i=0; i<n; ++i)
        for(int j=0; j<m; ++j)
            cin >> A[i][j];
}
void sort(int A[N_MAX][N_MAX], int n, int m)
{
    for(int i=0; i<n-1; ++i)
    {
        int imin = iMin(A, i, n);
        swap(A[i], A[imin], m);
    }
}
int main()
{

}