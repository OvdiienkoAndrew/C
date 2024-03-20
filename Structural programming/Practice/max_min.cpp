// У порядку спадання.
#include <iostream>
using namespace std;
int main()
{
    const int len=5;
    int A[len]={30,50,20,10,40}, temp;  
    for(int starti=0; starti<len-1; ++starti)
    {
        for (int q=0; q<len-1-starti; ++q)
        {
            if(A[q]<A[q+1])
            {
                temp=A[q];
                A[q]=A[q+1];
                A[q+1]=temp;
            }
        }
    }
    for(int i=0; i<len; ++i) cout << A[i] << "\t";
}