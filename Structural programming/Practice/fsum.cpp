#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char *argv[])
{
    if(argc==1 || argc > 2)
    {
        cout << "Error:no params.";
        return 1;
    }
    ifstream fin(argv[1]);
    int a, s=0;
    while(fin >> a)
        s+=a;
    cout << "Sum = " << s << endl;
    return 0;
}