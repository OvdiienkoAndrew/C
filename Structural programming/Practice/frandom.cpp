#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    fstream f;
    char filename[100];
    int seed, n;
    cout << "Input file name? = ";
    while(cin >> filename, f.open(filename, ios::in), f.fail() || f.eof() || f.bad())
        cout << "Can't open file: " << filename << ". Come again? ;)" << endl;
    f >> seed >> n;
    f.close();
    cout << "Output file name? = ";
    while(cin >> filename, f.open(filename, ios::in), f.fail() || f.eof() || f.bad())
        cout << "Can't open file: " << filename << ". Come again? ;)" << endl;
    srand(seed);
    for(int i=0; i<n; i++)
        f << rand() << endl;
    f.close();
    return 0;
}