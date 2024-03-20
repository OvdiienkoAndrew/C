#include <iostream>
using namespace std;
int main()
/*  Так
    char a[3];
    cin >> a;
    cout << a;
*/

/* Ні
    a = {1,2,3};
        int b[3]; (Так)
    a=b;
    cout << b;
    cin >> b;
*/
{
    int a[3]={11,22,33};
    cin >> a[0] >> a[1] >> a[2];
    double b[]={3.14159265, 2.7182845, -1.0101};
    if(b[1]<b[2]) cout << b[0];
}