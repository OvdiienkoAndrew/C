#include <iostream> // Підключаємо бібліотека для вводу й виводу тексту на консоль.
using namespace std; // Вказуємо, який простір імен.
int main() // Програма на С++ починається із виконання функції main.
{ // Фігурні дужки в яких пишется основний код програми (початок).
    int i, res=1; // Задаємо змінну та сталу.
    long long n; // Задаємо змінну, у якої великий обʼєм вмісту.
    cout << "Для обчислення N! введіть:\nN = "; // Виводимо на консоль символи, нова строка.
    cin >> n; // Вводимо число.
    i=n; // присвоюємо значенню i значення n.
    for (i=1; i<=n; i++) // Доки i дорівнює одиниці, і менш або дорівнює n, до і додається одиниця.
    {
        res=res*i; // Обчислюємо факторіал, множемо число, яке ввів користуач на число, яке на одиницю менше.
    }
    cout << n << "! = " <<res;
    return 0; // Робимо так, щоб програма працювала без повторень.
} // Фігурні дужки в яких пишется основний код програми (кінець).