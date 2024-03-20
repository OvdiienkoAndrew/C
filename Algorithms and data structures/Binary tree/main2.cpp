// Перетворити масив на бінарну купу
#include <iostream>
using namespace std;
void swap(int &a, int &b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}
void MaxToMinHeapify(int A[], int &n)
{
    for(int i = n/2-1; i>=0; i--)
    {
        int smallest = i;
        int left = 2*i+1;
        int right = 2*i+2;
        if (left < n && A[left] < A[smallest]) smallest = left;
        if (right < n && A[right] < A[smallest]) smallest = right;
        if (smallest != i) 
        {
            swap(A[smallest], A[i]);
            MaxToMinHeapify(A, n);
        }
    }
}
void MinToMaxHeapify(int A[], int &n)
{
    for(int i = n/2-1; i>=0; i--)
    {
        int largest = i;
        int left = 2*i+1;
        int right = 2*i+2;
        if (left < n && A[left] > A[largest]) largest = left;
        if (right < n && A[right] > A[largest]) largest = right;
        if ( largest != i) 
        {
            swap(A[largest], A[i]);
            MinToMaxHeapify(A, n);
        }
    }
}
int main()
{
    int A[] = {4,12,3,8,6,20,18,10,14,15,22};
    int n = sizeof(A)/sizeof(A[0]); 
    cout << "\nКоличество элементов: " << n << ".\n"; 
    cout << "\nМассив: ";
    for(int i=0; i<n; i++) cout << A[i] << ", ";
    cout << "\b\b.\n";
    MaxToMinHeapify(A, n);
    cout << "\nМассив (бинарная купа от меньшего к большему): ";
    for(int i=0; i<n; i++) cout << A[i] << ", ";
    cout << "\b\b.\n";
    MinToMaxHeapify(A, n);
    cout << "\nМассив (бинарная купа от большего к меньшему): ";
    for(int i=0; i<n; i++) cout << A[i] << ", ";
    cout << "\b\b.\n";
    cout << "\n"; return 0;
}
