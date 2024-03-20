#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;
const int N = 1000000;
int a[N];
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
int my_sort(int A[], int n)
{
    int imin;
    for(int i=0; i<n-1; ++i)
    {
        imin = iMin(A, i, n);
        swap(A[i], A[imin]);
    }
    return imin;
}
int main()
{
    int n;

    cin >> n;
    for(int i=0; i<n; i++)
        cin >> a[i];

    // замер времени для iMin
    double t1, t2;
    t1 = clock();
   // for(int i=0; i<n; i++)
        my_sort(a, n);
    t2 = clock();
    cout << "iMin time: " << (t2-t1)/CLOCKS_PER_SEC << 's' << endl;

    // замер времени для sort
  //  t1 = clock();
   // sort(a, a+n);
  //  t2 = clock();
   // cout << "sort time: " << (t2-t1)/CLOCKS_PER_SEC << 's' << endl;
    
    cout << n << endl;
    for(int i=0; i<n; i++)
        cout << a[i] << " ";
    cout << "\n";
    return 0;
}