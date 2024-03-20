// Підключення заголовних файлів iostream та ctime.
#include <iostream>
#include <ctime>

// Використання простору імен std.
using namespace std;

// Визначення константи N, розміру масиву.
const int N = 100;

/* 
    Оголошення масивів A і B, змінної n (кількість елементів у масиві A),
    і змінних a, b, k, а також t для збереження n.
*/
int A[N], B[N], n=0, a=0, b=0, k, t=n;

// Функція заповнення масиву псевдовипадковими значеннями.
void cinn(){
    // Введення меж діапазону випадкових чисел a та b.
    cout << "\nEnter the boundaries of random numbers a and b:\n";
    while (true) {
        cout << "a = ";
        while (!(cin >> a)) {
            cout << "Invalid input. Try again: a should be an integer.\na = ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "b = ";
        while (!(cin >> b)) {
            cout << "Invalid input. Try again: b should be an integer.\nb = ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (a > b) cout << "Invalid input. Try again: a should be less than or equal to b.\n";
        else break;
    }

    // Введення кількості елементів масиву n.
    cout << "Enter the number of elements (n <= " << N << "):\n";
    while (true) {
        cout << "n = ";
        while (!(cin >> n)) {
            cout << "Invalid input. Try again: n should be an integer.\nn = ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (n > N) cout << "Invalid input. Try again: n should be less than or equal to " << N << ".\n";
        else if (n <= 0) cout << "Invalid input. Try again: empty array.\n";
        else { break;}
    }

    // Заповнення масиву A випадковими значеннями діапазону [a, b].
    for (int size = 0; size < n; size++) A[size] = a + rand() % (b - a + 1);
    
    t = n;
    cout << "\n\n";
}

// Функція виведення масиву на екран.
void coutt(){
    n = t;
    // Якщо масив A порожній (n = 0), виводиться повідомлення про це.
    if (n == 0) cout << "\nThe array is empty.";
    else{
        // Виведення заповненої частини масиву.
        cout << "\nThe array will consist of " << n << " elements. Number range from "<< a << " to " << b << ".";
        cout << "\n\nFilled part of the array:\n";
        for (int size = 0; size < n; size++) {
            cout << "Array[" << size << "] = " << A[size];
            if (size == n - 1) cout << ".\n";
            else cout << ";\n";
        }
    }
    
    // Наприкінці виводиться два перекладу рядка для поділу виводу з іншого виводу.
    cout << "\n\n";
}

// Функція завдання 1.
void  Task1(){
    // Якщо масив A порожній (n = 0), виводиться повідомлення про це.
    if (n == 0) cout << "\nThe array is empty.";
    else {
        // Знаходиться індекс мінімального елемента масиву A і виводиться значення цього елемента та його індекс.
        int minIndex = 0;
        for (int size = 0; size < n; size++) if (A[size] < A[minIndex]) minIndex = size;
        cout << "\nMinimum array element: " << A[minIndex] << ", index: " << minIndex << ".\n\n";
        
        // Обчислюється сума елементів із парними індексами, що знаходяться перед мінімальним елементом.
        int sum = 0;
        for (int size = 0; size < minIndex; size+=2) sum += A[size];
         
        // Виводиться значення цієї суми.
        cout << "Sum of elements with even indexes before minimum element: " << sum << ".";
    }
    // Наприкінці виводиться два перекладу рядка для поділу виводу з іншого виводу.
    cout << "\n\n";
}

// Функція завдання 2.
void Task2() {
    // Якщо масив A порожній (n = 0), виводиться повідомлення про це.
    if (n == 0) cout << "\nThe array is empty.";
    else {
        // Створюється нова змінна newSize, яка використовуватиметься для зміни розміру масиву B.
        int newSize = n;

        n = t;

        // Копіюється кожен елемент масиву A відповідний елемент масиву B.
        for (int size = 0; size < newSize; size++) {
            B[size] = A[size];
        }

        /*  
            Зміна масиву B: якщо елемент B[i] є парним числом, він зсувається однією позицію вправо,
            а позицію B[i+1] записується значення 0. При цьому розмір newSize збільшується на 1.
            Якщо масив В більший за N (newSize > N), то  виводиться повідомлення про це.
        */
        for (int i = 0; i < newSize; i++) {
            if (B[i] % 2 == 0) {
                if (newSize > N) {
                    cout << "\n\nCannot add more elements. Maximum array size exceeded.\n\n";
                    return;
                }
                for (int j = newSize; j > i + 1; j--) {
                    B[j] = B[j - 1];
                }
                B[i + 1] = 0;
                newSize++;
                i++;
            }
        }
        
        // Якщо масив В порожній (newSize = 0), виводиться повідомлення про це.
        if (newSize == 0) cout << "\nThe array is empty after the transformation.";
        else {
            // Виведення зміненої частини масиву B.
            cout << "\n\nUpdated part of the array with added elements:\n";
            for (int size = 0; size < newSize; size++) {
                cout << "Array[" << size << "] = " << B[size];
                if (size == newSize - 1) {
                    cout << ".";
                } else {
                    cout << ";";
                }
                cout << "\n";
            }
        }
    }
    // Наприкінці виводиться два перекладу рядка для поділу виводу з іншого виводу.
    cout << "\n\n";
}

// Головна функція програми
int main() {

    // Ініціалізація генераторації псевдовипадкових чисел з урахуванням часу.
    srand(time(nullptr));
    
    // Заповнення масиву A нульовими значеннями.
    for (int size = 0; size < N; size++) A[size] = 0;
    
    // Цикл із меню вибору дій.
    do {
        cout << "1. Fill the array;\n";
        cout << "2. Display array on screen;\n";
        cout << "3. Task 1;\n";
        cout << "4. Task 2;\n";
        cout << "5. Exit.\n";
        cin >> k;
        switch (k) {
            case 1: cinn(); break;
            case 2: coutt(); break;
            case 3: Task1(); break;
            case 4: Task2(); break;
            default: cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); break;
        }
    } while (k!=5);

    cout << "\nGoodbye.\n\n";
    return 0;
}
