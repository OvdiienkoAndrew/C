#include <iostream>
using namespace std;
int main()
{
    long long int n, d = 1;
    cout << "Enter n: ";
    cin >> n;
    int Arr[n];
    cout << "Array:\n";
    for (int i=0; i<n; i++) 
    {
        cin >> Arr[i];
    }
    for (int i = 0; i < n; i+=2)
    { 

        d *= Arr[i];

    }
    cout << "\n\n" << d << "\n\n";
    return 0;
}  