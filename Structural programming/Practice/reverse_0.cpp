// Задача reverse. Ідея, алгоритм і програма.
#include <iostream>
using namespace std;
const int N_MAX = 100000000;
int A[N_MAX];
int main()
{
    int N, i;
    cout << "N = ? (0<=N<=" << N_MAX << ") ";
while (cin >> N, cin.fail()) {
    // Do something with N
    cout << "Return ;)\n";
}
// If cin encounters an error or EOF, it will return false and execution will exit the while loop.
    i = 0;
    while (i<N)
    {
        cout << "A[" << (i+1) << "] = ? ";
        cin >> A[N-1-i];
        i++;
    }
    i = 0;
    while (i<N)
    {
        cout << "A[" << (i+1) << "] = ? " << A[i] << endl;
        i++;
    }
}