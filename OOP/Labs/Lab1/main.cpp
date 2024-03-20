#include <iostream> // Підключення заголовкового файлу для використання стандартного вводу/виводу.
#include "Module.h" // Включення заголовного файлу для використання класу Array.
using namespace std; // Використання простору імен для стандартних об'єктів та функцій.

int main(int argc, char *argv[]) // Оголошення головної функції з параметрами командного рядка.
{
    cout << "\n\n"; // Вивід порожнього рядка для візуального розділення виводу.
    Array arr(argc, argv); // Створення об'єкту класу Array з передачею аргументів командного рядка.
    arr.zerotask(argc, argv); // Виклик методу zerotask() для заповнення масиву числами.
    arr.firsttask(); // Виклик методу firsttask() для сортування масиву за критерієм "Спочатку гарні(позитивні) потім погані (негативні)".
    arr.secondtask(); // Виклик методу secondtask() для знаходження кількості позитивних, нульових та негативних чисел.
    arr.lasttask(); // Виклик методу lasttask() для відображення данних у файлі.
    cout << "\n\n"; // Вивід порожнього рядка для візуального розділення виводу.
    return 0; // Повернення нульового значення для позначення успішного завершення програми.
}




/*

g++ -c Module.cpp -o Module.o
g++ -c main.cpp -o main.o
g++ Module.o main.o -o main
./main

open main

*/