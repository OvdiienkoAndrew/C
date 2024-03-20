#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;
int main()
{
    srand(time(NULL));
    
    double t1, t2, t3, t4, t5, t6, t7, t8;
    int  n = 22000;
    float **M = new float*[n]; 
    for (int i=0; i<n; i++)
    M[i] = new float[n];
    float *V = new float[n]; 
    float *MV = new float[n]; 
    float *VM = new float[n];
    float *VM2 = new float[n];

    for (long long int o=1000; o<=n; o+=1000)
    {   
        for (int i=0; i<o; i++)
        {
            for (int j=0; j<o; j++)
            {        
                M[i][j] = rand()%19-9;        
            }
        }
        for (int i=0; i<o; i++)
        {
            V[i] = rand()%19-9;        
        }
        for (int i=0; i<o; i++)
        {
            MV[i] = 0;
        }
        t1= clock();
        for (int i=0; i<o; i++)
        {
            for (int j=0; j<o; j++)
            {
                MV[i] += M[i][j] * V[j];
            }
        }
        t2 = clock(); 
        cout << "\nЧас множення матриці на вектор у секундах: " << (t2-t1)/CLOCKS_PER_SEC << ".   N = " << o << ".\n\n";
        for (int i=0; i<o; i++)
        {
            VM[i]=0;
        }
        t3 = clock(); 
        for (int i=0; i<o; i++)
        {
            for (int j=0; j<o; j++)
            {
                VM[i] += M[j][i] * V[j];
            }
        }
        t4 = clock(); 
        cout << "\nЧас множення вектора на матрицю в секундах: " << (t4-t3)/CLOCKS_PER_SEC << ".   N = " << o << ".\n\n";
        for (int i=0; i<o; i++)
        {
            VM2[i]=0;
        }
        t5 = clock();
        for (int j=0; j<o; j++)
        {
            for (int i=0; i<o; i++)
            {
                VM2[i] += M[j][i] * V[j];
            }
        }
        t6 = clock();
        cout << "\nMOD\nЧас множення вектора на матрицю у секундах: " << (t6-t5)/CLOCKS_PER_SEC << ".   N = " << o << ".\n\n";
    }
  return 0;
}