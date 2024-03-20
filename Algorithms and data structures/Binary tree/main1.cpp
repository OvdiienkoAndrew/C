// перевірка, чи є масив бінарною купою
#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}

struct Node
{
    int data;
    Node* next;
};

Node* CreateNode(int x)
{
    Node* node = new Node;
    node->data = x;
    node->next = nullptr;
    return node;
}

void AddEnd(Node* &List, Node* &New)
{
    if (List == nullptr)
        List = New;
    else
    {
        Node* node = List;
        while (node->next != nullptr)  
            node = node->next;
        node->next = New;
    }
}

void DisplayListWithIndices(Node* List)
{
    Node* Node = List;
    if (Node == nullptr) {}
    else
    {
        while (Node != nullptr)
        {
            cout << Node->data;
            Node = Node->next;
            if (Node != nullptr) cout << ", ";
            else cout << ".\n";
        }
    }
}

void MinToMaxHeapify(int A[], int &n, Node* &List)
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
            Node* curr = CreateNode(A[largest]);
            AddEnd(List, curr);
            curr = CreateNode(A[i]);
            AddEnd(List, curr);
            MinToMaxHeapify(A, n, List);
        }
    }
}

void MaxToMinHeapify(int A[], int &n, Node* &List)
{
    for(int i = n/2-1; i>=0; i--)
    {
        int smallest = i;
        int left = 2*i+1;
        int right = 2*i+2;
        if (left < n && A[left] < A[smallest]) 
            smallest = left;
        if (right < n && A[right] < A[smallest]) 
            smallest = right;
        if (smallest != i) 
        {
            swap(A[smallest], A[i]);
            Node* curr = CreateNode(A[smallest]);
            AddEnd(List, curr);
            curr = CreateNode(A[i]);
            AddEnd(List, curr);
            MaxToMinHeapify(A, n, List);
        }
    }
}

bool isValidIndex(Node* List, int index)
{
    index--;
    int length = 0;
    Node* Node = List;

    while (Node != nullptr)
    {
        length++;
        Node = Node->next;
    }
    return (index >= 0 && index < length);
}

void RemoveDuplicates(Node* &List)
{
    Node* current = List;

    while (current != nullptr)
    {
        Node* runner = current;

        while (runner->next != nullptr)
        {
            if (runner->next->data == current->data)
            {
                Node* duplicate = runner->next;
                runner->next = duplicate->next;
                delete duplicate;
            }
            else
            {
                runner = runner->next;
            }
        }

        current = current->next;
    }
}

int main()
{
    int A[] = {5, 10, 7, 24, 12, 15, 11, 30, 28, 16};
    int n = sizeof(A) / sizeof(A[0]);
    Node* MinMax = nullptr;
    Node* MaxMin = nullptr;
    cout << "\nКоличество элементов: " << n << ".\n"; 
    cout << "\nМассив: ";
    for(int i=0; i<n; i++) 
        cout << A[i] << ", ";
    cout << "\b\b.\n";
    MaxToMinHeapify(A, n, MinMax);
    RemoveDuplicates(MinMax);
    if(isValidIndex(MinMax, 1))
    {
        cout << "\nМасив не є бінарною купою (від найменшого згори до найбільшого знизу).\nЕлементи, які заважають бути бінарною купою: ";
        DisplayListWithIndices(MinMax);
    }
    else cout << "\nМасив є бінарною купою (від найменшого згори до найбільшого знизу).\n";
    MinToMaxHeapify(A, n, MaxMin);
    RemoveDuplicates(MaxMin);
    if(isValidIndex(MaxMin, 1))
    {
        cout << "\nМасив не є бінарною купою (від найбільшого згори до найменшого знизу).\nЕлементи, які заважають бути бінарною купою: ";
        DisplayListWithIndices(MaxMin);
    }
    else cout << "\nМасив є бінарною купою (від найбільшого згори до найменшого знизу).\n";
    cout << "\n\n";
    return 0;
}
