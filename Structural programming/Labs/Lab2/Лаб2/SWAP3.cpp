#include <iostream> // Підключаємо бібліотека для вводу й виводу тексту на консоль.
using namespace std; // Вказуємо, який простір імен.
int main() // Програма на С++ починається із виконання функції main.
{ /// Фігурні дужки в яких пишется основний код програми (початок).
    int A, B, C, temp; // Задаємо змінні.
    cout << "Задайте числа для А, В, С."<< endl;  // Виводимо на консоль символи, переходимо на наступний рядок.
    cout << "A="; // Виводимо на консоль символи.
    cin >> A; // Користувач вводить число.
    cout << "B="; // Виводимо на консоль символи.
    cin >> B; // Користувач вводить число.
    cout << "C="; // Виводимо на консоль символи.
    cin >> C; // Користувач вводить число.
    cout << "Дані значення: А=" << A << ", В=" << B << ", С=" << C << "." << endl; // Виводимо на консоль символи, і значення, які користувач прописував раніше, переходимо на наступний рядок.
    temp=A; // temp приймає значення A.
    A=C; // А приймає значення С.
    C=temp; // // C приймає значення temp.
    temp=C; // temp приймає значення C.
    C=B; // C приймає значення B.
    B=temp; // B приймає значення temp.
    cout << "Значення після обміну: А=" << A << ", В=" << B << ", С=" << C << "."; // Виводимо на консоль символи, і значення, які користувач прописував раніше, але змінені програмою.
    return 0; // Робимо так, щоб програма працювала без повторень.
} // Фігурні дужки в яких пишется основний код програми (кінець).

