#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char *argv[]) 
{
    cout << "\n";
    char fileName[1000001];
    int N, A, B;
    if (argc == 5) 
    {
        strcpy(fileName, argv[1]);
        N = atoi(argv[2]);
        A = atoi(argv[3]);
        B = atoi(argv[4]);
        while(A>B)
        {
            cout << "\nA <= B.\nA = ? ";
            cin >> A;
            cout << "B = ? ";
            cin >> B;
        }
        while (N < 1 || 1000000 < N || N>abs(B-(A-1)))
        {
            cout << "\n1 <= N <= 1 000 000;\tN < |B-A|;\tN = ? ";
            cin >> N;
        }
    }
    else
    {
        cout << "fileName = ? ";
        cin >> fileName;
        cout << "\nA <= B.\nA = ? ";
        cin >> A;
        cout << "B = ? ";
        cin >> B;
        while(A>B)
        {
            cout << "\nA <= B.\nA = ? ";
            cin >> A;
            cout << "B = ? ";
            cin >> B;
        }
        cout << "\n1 <= N <= 1 000 000;\tN < |B-A|;\tN = ? ";
        cin >> N;
        while (N < 1 || 1000000 < N || N>abs(B-(A-1)))
        {
            cout << "\n1 <= N <= 1 000 000;\tN < |B-A|;\tN = ? ";
            cin >> N;
        }
    }
    N += 1;
    cout << "\nFileName = " << fileName << ", N = " << N << ", A = " << A << ", B = " << B << ".\n\n"; 
    
    int a[N];
    double step = (B - A) / (double) (N - 1);

    a[0] = A;

    for (int i = 1; i < N; i++) 
    {
        a[i] = a[i-1] + step;
        cout << a[i] << " ";
    }

    cout << "\n\n";
    return 0;
}