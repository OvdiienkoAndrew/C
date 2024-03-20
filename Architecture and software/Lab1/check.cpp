#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;
int main()
{
    srand(time(NULL));

    double t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
    int  n = 3;
    int **M = new int*[n]; 
    for (int i=0; i<n; i++)
    M[i] = new int[n];
    int *V = new int[n]; 
    int *MV = new int[n]; 
    int *VM = new int[n];
    int *VM2 = new int[n];

   for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {        
           M[i][j] = rand()%19-9;        
        }
    }
    cout << "\nMатриця:\n\n";
    for (int i=0; i<n; i++)
    {
        cout << "| ";
        for (int j=0; j<n; j++)
        {
            cout << M[i][j];
            if (j < n - 1) cout << " ";
            else cout << " |" << endl;
        }
    }
   for (int i=0; i<n; i++)
    {
        V[i] = rand()%19-9;        
    }
    cout << "\n\nВектор:\n\n| ";
    for (int i=0; i<n; i++)
    {
        cout << V[i] << " ";
    }
    cout << "|\n\n";
    for (int i=0; i<n; i++)
    {
        MV[i] = 0;
    }
    t1= clock();
    for (int i=0; i<n; i++)
    {
        for (int j=0; j < n; j++)
        {
            MV[i] += M[i][j] * V[j];
        }
    }
    t2 = clock(); 
    cout << "\nМноження матриці на вектор:\n\n";
    for (int i=0; i<n; i++)
    {
        cout << "| " << MV[i] << " |\n";
    }
    cout << "\nЧас множення матриці на вектор у секундах: " << (t2-t1)/CLOCKS_PER_SEC << ".\n\n";
    for (int i=0; i < n; i++)
    {
        VM[i]=0;
    }
    t3 = clock(); 
    for (int i=0; i < n; i++)
    {
        for (int j=0; j < n; j++)
        {
            VM[i] += M[j][i] * V[j];
        }
    }
    t4 = clock(); 
    cout << "\n\nМноження вектора на матрицю:\n\n| ";
    for (int i=0; i < n; i++)
    {
        cout << VM[i] << " ";
    }
    cout << "|" << endl;
    cout << "\nЧас множення вектора на матрицю в секундах: " << (t4-t3)/CLOCKS_PER_SEC << ".\n\n";
    for (int i=0; i < n; i++)
    {
        VM2[i]=0;
    }
    t5 = clock();
    for (int j=0; j < n; j++)
    { 
        for (int i=0; i < n; i++)
        {   
            VM2[i] += M[j][i] * V[j];
        }
    }
    t6 = clock();
    cout << "\nMOD\nМноження вектора на матрицю:\n\n| ";
    for (int i=0; i < n; i++)
    {
        cout << VM2[i] << " ";
    }
    cout << "|" << endl;
    cout << "\nMOD\nЧас множення вектора на матрицю у секундах: " << (t6-t5)/CLOCKS_PER_SEC << ".\n\n";
    return 0;
}