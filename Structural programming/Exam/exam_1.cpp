// Оголосити вказівник на дійсне значення та продемонструвати використання.
#include <iostream>
using namespace std;
int main()
{
    int a;
    while (true) 
    {
        cout << "a = ? ";
        cin >> a;
        if (!cin) 
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Try again.\n";
        } else 
        {
            break;
        }
    }
    cout << "a = " << a << ".\n";
    int *px = &a;
    cout << "Сell address: " << px << ";\tDereferencing: " << *px << ".\n";
    int *px1 = &a;
    cout << "Сell address: " << px1 << ";\tDereferencing: " << *px1 << ".\n";
    *px1 = 2;
    cout << "a = " << a << ".\n";
    cout << "Сell address: " << px << ";\tDereferencing: " << *px << ".\n";
    return 0;
}