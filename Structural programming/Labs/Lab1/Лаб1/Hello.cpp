#include <iostream>
#include <iomanip>
using namespace std;
int add(int a, int b)
{
    int z;
    z=a+b;
    return z;
}
int main()
{
    int a, b;
    cout << "\na=";
    cin >> a;
    cout << "\nb=";
    cin >> b;
    cout << "Summa" << add(a,b);
    return 0;
}