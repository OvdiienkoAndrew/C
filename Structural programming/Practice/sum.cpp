#include <iostream>
using namespace std;
int main()
{
    cout << "\n";
    srand(time(NULL));
    int n=3, s1=0, s2=0;
    int**arr = new int*[n];
    for (int i=0; i<n; i++)
    arr[i] = new int [n];
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            arr[i][j]=rand()%10; 
            if (i+j<n-1)
            {
                s1+=arr[i][j];
            }
            if (i+j>n-1)
            {
                s2+=arr[i][j];
            } 
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n\nСума елементів матриці строго вище побічної діагоналі: " << s1 << "\n\n";
    cout << "Сума елементів матриці строго нижче побічної діагоналі: " << s2 << "\n\n";
    return 0;
}