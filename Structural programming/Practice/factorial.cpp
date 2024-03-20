#include <iostream>
using namespace std;
long long int factorial_r(int n) // рекурсивній метод
{
    if(n<=1) return 1;
    else return n*factorial_r(n-1);
}
long long int factorial_nr(int n) // нерекурсивній метод
{
    if(n<=1) return 1;
    long long res=1;
    for (int i=1; i<=n; i++) res=res*i;
    return res;
}  
int main()
{
    int n;
    cin >> n;
    cout << n << "! = " << factorial_r(n) << endl; // рекурсивній метод
    cout << n << "! = " << factorial_nr(n) << endl; // нерекурсивній метод
}