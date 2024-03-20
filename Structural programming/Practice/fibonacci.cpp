#include <iostream>
using namespace std;
const int N=1000;
long memo[N];
long long int fibonacci_r(int n) // рекурсивній метод
{
    if(n>1)
    {
        if(memo[n]>0) return memo[n];
        long tmp = fibonacci_r(n-1)+fibonacci_r(n-2);
        memo[n] = tmp;
        return tmp;
    }
    if (n==1) return 1;
    return 0;
}
long long int fibonacci_nr(int n) // нерекурсивній метод
{
    if(n<0) return 0;
    long arr[n+1];
    arr[0]=0;
    arr[1]=1;
    for(int i=2; i<=n; i++) arr[i]=arr[i-1]+arr[i-2]; 
    return arr[n];
}
int main()
{
    int n;
    cin >> n;
    cout << "Fibo(" << n << ") = " << fibonacci_r(n) << endl; // рекурсивній метод
    cout << "Fibo(" << n << ") = " << fibonacci_nr(n) << endl; // нерекурсивній метод
}