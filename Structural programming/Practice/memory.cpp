#include <iostream>
using namespace std;
/*
int i = 123;

void f()
{
    int i = 0;
    i++;
    static int si = 0;
    cout << "si=" << si << " i=" << i << endl;
    si++;
}
int main()
{
    for(int i=0; i<10; ++i)
        f();
}
*/
void f()
{
    int i = 45;
    cout << i << "\n";
    static int si = 0;
    cout << si << "\n";
    int *pi = new int;
    cout << *pi << "\n";
    delete pi;
}
int main()
{
    f();
}