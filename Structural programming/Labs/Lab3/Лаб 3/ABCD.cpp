#include <iostream> // Підключаємо бібліотека для вводу й виводу тексту на консоль.
using namespace std; // Вказуємо, який простір імен.
int main() // Програма на С++ починається із виконання функції main.
{ /// Фігурні дужки в яких пишется основний код програми (початок).
    int A, B, C, D, temp; // Задаємо змінні.
    cout << "Задайте числа для А, В, С і D, а програма виконає умову А <= B <= C <= D.\n"; // Виводимо на консоль символи, нова строка.
    cout << "A="; // Виводимо на консоль символи.
    cin >> A; // Користувач вводить число.
    cout << "B="; // Виводимо на консоль символи.
    cin >> B; // Користувач вводить число.
    cout << "C="; // Виводимо на консоль символи.
    cin >> C; // Користувач вводить число.
    cout << "D="; // Виводимо на консоль символи.
    cin >> D; // Користувач вводить число.
    cout << "Дані значення: А=" << A << ", В=" << B << ", С=" << C << ", D=" << D << ".\n"; // Виводимо на консоль символи, і значення, які користувач прописував раніше, нова строка.
    if (B < A) // Якщо значення B менше значення A.
    { // Фігурні дужки перед початком виконання даної умови "Якщо значення B менше значення A".
    temp=A; // temp приймає значення A.
    A=B; // А приймає значення В.
    B=temp; // B приймає значення temp.
    } // Фігурні дужки після кінця виконання даної умови "Якщо значення B менше значення A".
    if (C < B) // Якщо значення C менше значення B.
    { // Фігурні дужки перед початком виконання даної умови "Якщо значення C менше значення B".
    temp=B; // temp приймає значення B.
    B=C; // B приймає значення C.
    C=temp; // C приймає значення temp.
    } // Фігурні дужки після кінця виконання даної умови "Якщо значення C менше значення B".
    if (D < C) // Якщо значення D менше значення C.
    { // Фігурні дужки перед початком виконання даної умови "Якщо значення D менше значення C".
    temp=D; // temp приймає значення D.
    D=C; // D приймає значення C.
    C=temp; // C приймає значення temp.
    } // Фігурні дужки після кінця виконання даної умови "Якщо значення D менше значення C".
    if (B < A) // Якщо значення B менше значення A.
    { // Фігурні дужки перед початком виконання даної умови "Якщо значення B менше значення A".
    temp=A; // temp приймає значення A.
    A=B; // А приймає значення В.
    B=temp; // B приймає значення temp.
    } // Фігурні дужки після кінця виконання даної умови "Якщо значення B менше значення A".
    if (C < B) // Якщо значення C менше значення B.
    { // Фігурні дужки перед початком виконання даної умови "Якщо значення C менше значення B".
    temp=B; // temp приймає значення B.
    B=C; // B приймає значення C.
    C=temp; // C приймає значення temp.
    } // Фігурні дужки після кінця виконання даної умови "Якщо значення C менше значення B".
    if (B < A) // Якщо значення B менше значення A.
    { // Фігурні дужки перед початком виконання даної умови "Якщо значення B менше значення A".
    temp=A; // temp приймає значення A.
    A=B; // А приймає значення В.
    B=temp; // B приймає значення temp.
    } // Фігурні дужки після кінця виконання даної умови "Якщо значення B менше значення A".
    cout << "Значення при умові А <= B <= C <= D: А=" << A << ", В=" << B << ", С=" << C << ", D=" << D << ".\n"; // Виводимо на консоль символи, і значення, які користувач прописував раніше, нова строка.
    return 0; // Без повторень.
} // Фігурні дужки в яких пишется основний код програми (кінець).