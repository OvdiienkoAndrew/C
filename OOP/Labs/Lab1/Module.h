#ifndef Module_h
#define Module_h
#include <iostream> // Підключення бібліотеки для введення та виведення даних у консоль.
#include <fstream> // Підключення бібліотеки для роботи з файлами.
#include <iomanip> // Підключення бібліотеки для форматованого виведення.
#include <string> // Підключення бібліотеки для роботи з рядками.
using namespace std; // використання простору імен std.
class Array { // Оголошення класу Array.
private: // Приватні змінні. 
    int poz; // Оголошення кількості позитивних чисел.
    int neg; // Оголошення кількості негативних чисел.
    int zer; // Оголошення кількості нульових чисел.
    int size; // Оголошення кількості елементів у масиві.
    double* A; // Оголошення масиву.
    char choice; // Оголошення змінної вибору.
    char* filename2; // Оголошення файлу, у який будуть записані результати.
public: // Публічні методи класу.
    Array(); // Конструктор за замовчуванням.
    Array(int argc, char* argv[]); // Конструктор з параметрами.
    void show(); // Метод для відображення послідовності чисел.
    void argcmoreone(int argc, char* argv[]); // Метод для обробки параметрів командного рядка.
    void ilessone(); // Метод для обробки введення з консолі.
    void zerotask(int argc, char* argv[]); // Метод для створення та заповнення масиву елементами.
    void merge(int&, int&, int&); // Метод для злиття двох підмасивів.
    void mergeSort(int, int); // Метод для сортування методом злиття (оберненний).
    void firsttask(); // Метод для упорядковуємо надану послідовність за критерієм "Спочатку гарні(позитивні) потім погані (негативні)".
    void secondtask(); // Метод для зʼясування кількості позитивниг, неативних та нульових елементів.
    void lasttask(); // Метод для запису данних у файл.
};
#endif
