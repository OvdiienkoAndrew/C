#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
void swap(int* a, int* b) // Функція для обміну значень елементів.
{
  *a = *a + *b; // Перше значення приймає суму двух значен.
  *b = *a - *b; // Друге значення приймає суму двох значень та віднімає своє значення і отримає значення іншого елемента.
  *a = *a - *b; // Перше значення приймає суму двох значень та віднімає значення, яке вже прийняло форму поточного значення і отримає значення іншого елемента.
}
class BinaryHeap // Клас для представлення бінарної купи.
{
    public: // Публічне, може використовуватися де завгодно у коді.
        int* array; // Вказівник на масив елементів купи.
        int capacity; // Максимальний розмір купи.
        int heap_size; // Поточний розмір купи.
        BinaryHeap(int capacity) // Конструктор для ініціалізації купи з заданим розміром.
        {
            this->capacity = capacity; // Встановлюємо розмір купи на підставі переданого значення.
            heap_size = 0; // Встановлюємо розмір купи 0, так як на початку купа не містить жодного елемента.
            array = new int[capacity]; // Створюємо новий масив із заданим розміром для зберігання елементів купи.
        }
        int parent(int i) { return (i - 1) / 2; } // Функція для знаходження індекса батька елемента.
        int left(int i) { return (2 * i + 1); } // Функція для знаходження лівого дочірнього елемента.
        int right(int i) { return (2 * i + 2); } // Функція для знаходження правого дочірнього елемента.
        void insertKey(int k) // Функція для додавання нового елемента до купи.
        {
            if (heap_size == capacity) // Перевірка, чи купа вже досягла максимального розміру.
            {
                cout << "\nКупа вже досягла максимального розміру.\n"; // Вивід повідомлення про те що купа заповнена повністью, додавання неможливе.
                return; // Завершення функції.
            }
            int i = heap_size++; // Збільшуємо кількість елементів у купі і зберігаємо значення у змінну "i".
            array[i] = k; // Додаємо новий елемент "k" до купи на позицію "i".
            while (i != 0 && array[parent(i)] > array[i]) // Виконуємо цикл, доки індекс не дорівнює 0, і значення батьківського елемента більше за значення на позиції "i".
            {
                swap(&array[i], &array[parent(i)]); // Міняємо місцями значення елементів на позиціях нового елемента в купі та його батька.
                i = parent(i); // Оновлення значення батьківського елемента.
            }
        }
        void MinHeapify(int i) // Функція для відновлення властивостей купи після видалення мінімального елемента.
        {
            int l = left(i); // Отримання індексу лівого дочірнього елемента поточного елемента.
            int r = right(i); // Отримання індексу правого дочірнього елемента поточного елемента.
            int smallest = i; // Змінна для збереження індексу поточного найменшого елемента.
            if (l < heap_size && array[l] < array[i]) smallest = l; // Якщо індекс лівого елемента в межах купи "heap_size" і його значення менше поточного найменшого - зберігаємо його індекс в змінну "smallest".
            if (r < heap_size && array[r] < array[smallest]) smallest = r; // Якщо індекс правого елемента в межах купи "heap_size" і його значення менше поточного найменшого - зберігаємо його індекс в змінну "smallest".
            if (smallest != i) // Якщо отриманий найменший індекс не дорівнює поточному індексу.
            {
                swap(&array[i], &array[smallest]); // Міняємо місцями значення елементів на позиціях найменшого елемента в купі і нового елемента в купі.
                MinHeapify(smallest); // Виклик рекурсивної функції "MinHeapify" з індексом smallest для відновлення властивостей купи для елемента з новим найменшим індексом.
            }
        }
        int extractMin() // Функція для видалення мінімального елемента з купи.
        {
            if (heap_size <= 0) return 0; // Перевіряємо, чи купа не порожня. Якщо так, повертаємо 0.
            if (heap_size == 1) // Перевіряємо, чи купа має розмір 1.
            {
                heap_size--; // Зменшуємо розмір купи на 1.
                return array[0]; // Повертаємо єдиний елемент купи.
            }
            int root = array[0]; // Зберігаємо мінімальний елемент.
            array[0] = array[--heap_size]; // Переносимо останній елемент масиву у корінь.
            MinHeapify(0); // Відновлюємо властивості купи, починаючи з кореня.
            return root; // Повертаємо збережений мінімальний елемент.
        }
};
void heapSort(int* arr, int n) // Функція для сортування за допомогою пірамідальної сортування.
{
    BinaryHeap heap(n); // Створення нової бінарної купи.
    for (int i = 0; i < n; i++) heap.insertKey(arr[i]); // Додавання елементів масиву до купи.
    for (int i = 0; i < n; i++) arr[i] = heap.extractMin(); // Видалення елементів з купи у відсортованому порядку.
}
void Swap(int *&Array, int &i) // Функція для обміну значень елементів: останнього, передостаннього.
{
    Array[i] = Array[i] + Array[i - 1]; // Значення приймає суми самого себе та попереднього елемента.
    Array[i - 1] = Array[i] - Array[i - 1]; // Попереднє значення приймає суму двох значень та віднімає своє значення і отримає значення іншого елемента.
    Array[i] = Array[i] - Array[i - 1]; // Значення приймає суму двох значень та віднімає значення, яке вже прийняло форму поточного значення і отримає значення попереднього елемента.
}
void myShakerSort(int *&Array, int &size, int &leftMark, int &rightMark, int &isSorted) // Функція для сортування за допомогою Шейкерного сортування з виконанням умови Айверсона.
{
    while (leftMark <= rightMark && !isSorted) // Триває, поки всі елементи не будуть відсортовані або ліва і права межі не перекриває праву.
    {
        isSorted = 1; // Спочатку припускаємо, що масив відсортований.
        for (int i = rightMark; i >= leftMark; i--) // Прохід від правої межі до лівої межі.
            if (Array[i - 1] > Array[i]) // Якщо попередній елемент більший за поточний.
            {
                Swap(Array, i); // Обміняти поточний елемент з попереднім елементом.
                isSorted = 0; // Встановлюємо прапорець, що масив ще не відсортований.
            }
        leftMark++; // Збільшуємо ліву межу для наступного проходу.
        for (int i = leftMark; i <= rightMark; i++) // Прохід від лівої межі до правої межі.
            if (Array[i - 1] > Array[i]) // Якщо попередній елемент більший за поточний.
            {
                Swap(Array, i); // Обміняти поточний елемент з попереднім елементом.
                isSorted = 0; // Встановлюємо прапорець, що масив ще не відсортований.
            }
        rightMark--; // Зменшуємо праву межу для наступного проходу.
    }
}
void merge(int* &Array, int &l, int &m, int &r) // Функція для злиття двох відсортованих підмасивів в один відсортований масив.
{
    int n1 = m - l + 1; // Обчислення розміру лівого підмасиву.
    int n2 = r - m; // Обчислення розміру правого підмасиву.
    int L[n1], R[n2]; // Створення тимчасових масивів для збереження підмасивів.
    for (int i = 0; i < n1; i++)  L[i] = Array[l + i]; // Копіювання лівого підмасиву в тимчасовий масив "L".
    for (int j = 0; j < n2; j++)  R[j] = Array[m + 1 + j]; // Kопіювання правого підмасиву в тимчасовий масив "R".
    int i = 0, j = 0, k = l; // Iніціалізація змінних для проходу через підмасиви та злиття їх елементів.
    while (i < n1 && j < n2) // Прохід через елементи обох підмасивів.
    {
        if (L[i] <= R[j]) // Порівняння елементів з лівого та правого підмасивів.
        {
            Array[k] = L[i]; // Присвоєння меншого елемента з лівого підмасиву в масив "Array".
            i++; // Перехід до наступного елемента в лівому підмасиві.
        }
        else
        {
            Array[k] = R[j]; // Присвоєння меншого елемента з правого підмасиву в масив "Array".
            j++; // Перехід до наступного елемента в правому підмасиві.
        }
        k++; // Перехід до наступної позиції в масиві "Array".
    }
    while (i < n1) // Якщо в лівому підмасиві залишились елементи.
    {
        Array[k] = L[i]; // Присвоєння решти елементів лівого підмасиву в масив "Array".
        i++; // Перехід до наступного елемента в лівому підмасиві.
        k++; // Перехід до наступної позиції в масиві "Array".
    }
    while (j < n2) // Якщо в правому підмасиві залишились елементи.
    {
        Array[k] = R[j]; // Присвоєння решти елементів правого підмасиву в масив "Array".
        j++; // Перехід до наступного елемента в правому підмасиві.
        k++; // Перехід до наступної позиції в масиві "Array".
    }
}
void mergeSort(int* &Array, int l, int r) // Функція для сортування масиву злиттям.
{
    if (l < r) // Перевірка, чи є ще елементи для сортування.
    {
        int m = l + (r - l) / 2; // Обчислення середини масиву.
        mergeSort(Array, l, m); // Рекурсивний виклик для першої половини масиву.
        mergeSort(Array, m + 1, r); // Рекурсивний виклик для другої половини масиву.
        merge(Array, l, m, r); // Злиття двох відсортованих половин масиву.
    }
}
void FirstSort()
{
    int size;
    char filename[1000];
    cout << "\nІм'я файлу, який буде відсортований методом \"Шейкерне сортування(з використанням умови Айверсона)\" ?= ";
    cin >> filename;
    ifstream outputfile;
    outputfile.open(filename);
    if (!outputfile.is_open()) cout << "\nПомилка відкриття файлу.\n";
    else
    {
        outputfile >> size;
        int* Array = new int[size];
        for(int i=0; i<size; i++) outputfile >> Array[i];
        outputfile.close();
        if( size == 11 | size == 1000 || size == 5000 || size == 10000 || size == 50000 || size == 100000 || size == 300000 || size == 500000)
        {
            int leftMark = 1;
            int rightMark = size-1;
            int isSorted = 0;
            cout << "\nСортування файлу...\n";
            double time1, time2;
            time1 = clock();
            myShakerSort(Array, size, leftMark, rightMark, isSorted);
            time2 = clock();
            cout << "\nЧас сортування: " << (time2-time1)/CLOCKS_PER_SEC << " секунд.\n";
            ofstream  inputfile;
            inputfile.open(filename);
            if (!inputfile.is_open()) 
            {
                cout << "\nПомилка відкриття файлу для введеня результатів.\n";
                return;
            }
            else
            {
                inputfile << size << "\n";
                for(int i=0; i<size; i++) inputfile << Array[i] << " ";
                cout << "\nОбробка даних занесена у файл: \"" << filename << "\".\n";
            }
            inputfile.close();
        }
        else cout << "\nРозмір масива може бути: 11, 1000, 5000, 10000, 50000, 100000, 300000, 500000.\n";
    }
}
void SecondSort()
{
    int size;
    char filename[1000];
    cout << "\nІм'я файлу, який буде відсортований методом \"Сортування злиттям\" ?= ";
    cin >> filename;
    ifstream outputfile;
    outputfile.open(filename);
    if (!outputfile.is_open()) cout << "\nПомилка відкриття файлу.\n";
    else
    {
        outputfile >> size;
        int* Array = new int[size];
        for(int i=0; i<size; i++) outputfile >> Array[i];
        outputfile.close();
        if( size == 11 | size == 1000 || size == 5000 || size == 10000 || size == 50000 || size == 100000 || size == 300000 || size == 500000)
        {
            cout << "\nСортування файлу...\n";
            double time1, time2;
            time1 = clock();
            mergeSort(Array, 0, size - 1);
            time2 = clock();
            cout << "\nЧас сортування: " << (time2-time1)/CLOCKS_PER_SEC << " секунд.\n";
            ofstream  inputfile;
            inputfile.open(filename);
            if (!inputfile.is_open()) 
            {
                cout << "\nПомилка відкриття файлу для введеня результатів.\n";
                return;
            }
            else
            {
                inputfile << size << "\n";
                for(int i=0; i<size; i++) inputfile << Array[i] << " ";
                cout << "\nОбробка даних занесена у файл: \"" << filename << "\".\n";
            }
            inputfile.close();
        }
        else cout << "\nРозмір масива може бути: 11, 1000, 5000, 10000, 50000, 100000, 300000, 500000.\n";
    }
}
void ThirdSort()
{
    int size;
    char filename[1000];
    cout << "\nІм'я файлу, який буде відсортований методом \"Пірамідального сортування (з використанням структури даних «бінарна купа»)\" ?= ";
    cin >> filename;
    ifstream outputfile;
    outputfile.open(filename);
    if (!outputfile.is_open()) cout << "\nПомилка відкриття файлу.\n";
    else
    {
        outputfile >> size;
        int* Array = new int[size];
        for(int i=0; i<size; i++) outputfile >> Array[i];
        outputfile.close();
        if( size == 11 | size == 1000 || size == 5000 || size == 10000 || size == 50000 || size == 100000 || size == 300000 || size == 500000)
        {
            cout << "\nСортування файлу...\n";
            double time1, time2;
            time1 = clock();
            heapSort(Array, size);
            time2 = clock();
            cout << "\nЧас сортування: " << (time2-time1)/CLOCKS_PER_SEC << " секунд.\n";
            ofstream  inputfile;
            inputfile.open(filename);
            if (!inputfile.is_open()) 
            {
                cout << "\nПомилка відкриття файлу для введеня результатів.\n";
                return;
            }
            else
            {
                inputfile << size << "\n";
                for(int i=0; i<size; i++) inputfile << Array[i] << " ";
                cout << "\nОбрoбка даних занесена у файл: \"" << filename << "\".\n";
            }
            inputfile.close();
        }
        else cout << "\nРозмір масива може бути: 11, 1000, 5000, 10000, 50000, 100000, 300000, 500000.\n";
    }
}
void FillArray1()
{
    int start, end, size;
    char filename[1000];
    double size2, start2, end2;
    do
    {
        cout << "\nКількість елементів масиву ?= ";
        cin >> size2;
        size = size2;
        if(cin.fail()) cout << "\nНеправильно введена кількість елементів.\nМає бути число.\n";
        else
        {
            if(size2 != size) cout << "\nНеправильно введена кількість елементів.\nМає бути ціле число.\n";
            else
            {
                if(size <= 0) cout << "\nНеправильно введена кількість елементів.\nМає бути натуральне число.\n";
                else
                {
                    if( size == 11 | size == 1000 || size == 5000 || size == 10000 || size == 50000 || size == 100000 || size == 300000 || size == 500000)
                    {
                        cout << "\nВведіть ліву та праву границю випадкових чисел для файлу\n\nЛіва границя ?= ";
                        cin >> start2;
                        start = start2;
                        if(cin.fail()) cout << "\nНеправильно введена ліва границя.\nМає бути число.\n";
                        else
                        {
                            if(start != start2) cout << "\nНеправильно введена ліва границя.\nМає бути ціле число.\n";
                            else
                            {
                                cout << "\nПрава границя ?= ";
                                cin >> end2;
                                end = end2;
                                if(cin.fail()) cout << "\nНеправильно введена права границя.\nМає бути число.\n";
                                else
                                {
                                    if(start != start2) cout << "\nНеправильно введена права границя.\nМає бути ціле число.\n";
                                    else
                                    {
                                        if(start > end) cout << "\nНеправильно введені границі.\nЛіва границя має бути менша або дорівнювати правій.\n";
                                        else break;
                                    }
                                }
                                
                            }
                        }
                    }
                    else cout << "\nРозмір масива може бути: 11, 1000, 5000, 10000, 50000, 100000, 300000, 500000.\n";
                }
            }
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }while(true);
    cout << "\nIм'я файлу ?= ";
    cin >> filename;
    cout << "\nКількість елементів: \"" << size << "\" - ліва границя: \"" << start << "\" - права границя: \"" << end << "\" - імʼя файлу: \"" << filename << "\".\n\nЗаповнення файлу...\n";
    int* Array = new int[size];
    for(int i=0; i<size; i++) Array[i] = start + rand()%(end-start+1);
    heapSort(Array, size);
    ofstream  inputfile;
    inputfile.open(filename);
    if (!inputfile.is_open()) cout << "\nПомилка відкриття файлу.\n";
    else
    {
        inputfile << size << "\n";
        for(int i=0; i<size; i++) inputfile << Array[i] << " ";
    }
    inputfile.close();
    cout << "\nФайл заповнено.\n";
}
void FillArray2()
{
    int start, end, size;
    char filename[1000];
    double size2, start2, end2;
    do
    {
        cout << "\nКількість елементів масиву ?= ";
        cin >> size2;
        size = size2;
        if(cin.fail()) cout << "\nНеправильно введена кількість елементів.\nМає бути число.\n";
        else
        {
            if(size2 != size) cout << "\nНеправильно введена кількість елементів.\nМає бути ціле число.\n";
            else
            {
                if(size <= 0) cout << "\nНеправильно введена кількість елементів.\nМає бути натуральне число.\n";
                else
                {
                    if( size == 11 | size == 1000 || size == 5000 || size == 10000 || size == 50000 || size == 100000 || size == 300000 || size == 500000)
                    {
                        cout << "\nВведіть ліву та праву границю випадкових чисел для файлу\n\nЛіва границя ?= ";
                        cin >> start2;
                        start = start2;
                        if(cin.fail()) cout << "\nНеправильно введена ліва границя.\nМає бути число.\n";
                        else
                        {
                            if(start != start2) cout << "\nНеправильно введена ліва границя.\nМає бути ціле число.\n";
                            else
                            {
                                cout << "\nПрава границя ?= ";
                                cin >> end2;
                                end = end2;
                                if(cin.fail()) cout << "\nНеправильно введена права границя.\nМає бути число.\n";
                                else
                                {
                                    if(start != start2) cout << "\nНеправильно введена права границя.\nМає бути ціле число.\n";
                                    else
                                    {
                                        if(start > end) cout << "\nНеправильно введені границі.\nЛіва границя має бути менша або дорівнювати правій.\n";
                                        else break;
                                    }
                                }
                                
                            }
                        }
                    }
                    else cout << "\nРозмір масива може бути: 11, 1000, 5000, 10000, 50000, 100000, 300000, 500000.\n";
                }
            }
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }while(true);
    cout << "\nIм'я файлу ?= ";
    cin >> filename;
    cout << "\nКількість елементів: \"" << size << "\" - ліва границя: \"" << start << "\" - права границя: \"" << end << "\" - імʼя файлу: \"" << filename << "\".\n\nЗаповнення файлу...\n";
    int* Array = new int[size];
    ofstream  inputfile;
    inputfile.open(filename);
    if (!inputfile.is_open()) 
    {
        cout << "\nПомилка відкриття файлу.\n";
    }
    else
    {
        inputfile << size << "\n";
        for (int i=0; i<size; i++)
        {
            Array[i] = start + rand()%(end-start+1);
            inputfile << Array[i] << " ";
        }
    }
    inputfile.close();
    cout << "\nФайл заповнено.\n";
}
void FillArray3()
{
    int start, end, size;
    char filename[1000];
    double size2, start2, end2;
    do
    {
        cout << "\nКількість елементів масиву ?= ";
        cin >> size2;
        size = size2;
        if(cin.fail()) cout << "\nНеправильно введена кількість елементів.\nМає бути число.\n";
        else
        {
            if(size2 != size) cout << "\nНеправильно введена кількість елементів.\nМає бути ціле число.\n";
            else
            {
                if(size <= 0) cout << "\nНеправильно введена кількість елементів.\nМає бути натуральне число.\n";
                else
                {
                    if( size == 11 | size == 1000 || size == 5000 || size == 10000 || size == 50000 || size == 100000 || size == 300000 || size == 500000)
                    {
                        cout << "\nВведіть ліву та праву границю випадкових чисел для файлу\n\nЛіва границя ?= ";
                        cin >> start2;
                        start = start2;
                        if(cin.fail()) cout << "\nНеправильно введена ліва границя.\nМає бути число.\n";
                        else
                        {
                            if(start != start2) cout << "\nНеправильно введена ліва границя.\nМає бути ціле число.\n";
                            else
                            {
                                cout << "\nПрава границя ?= ";
                                cin >> end2;
                                end = end2;
                                if(cin.fail()) cout << "\nНеправильно введена права границя.\nМає бути число.\n";
                                else
                                {
                                    if(start != start2) cout << "\nНеправильно введена права границя.\nМає бути ціле число.\n";
                                    else
                                    {
                                        if(start > end) cout << "\nНеправильно введені границі.\nЛіва границя має бути менша або дорівнювати правій.\n";
                                        else break;
                                    }
                                }
                                
                            }
                        }
                    }
                    else cout << "\nРозмір масива може бути: 11, 1000, 5000, 10000, 50000, 100000, 300000, 500000.\n";
                }
            }
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }while(true);
    cout << "\nIм'я файлу ?= ";
    cin >> filename;
    cout << "\nКількість елементів: \"" << size << "\" - ліва границя: \"" << start << "\" - права границя: \"" << end << "\" - імʼя файлу: \"" << filename << "\".\n\nЗаповнення файлу...\n";
    int* Array = new int[size];
    for(int i=0; i<size; i++) Array[i] = start + rand()%(end-start+1);
    heapSort(Array, size);
    ofstream  inputfile;
    inputfile.open(filename);
    if (!inputfile.is_open()) cout << "\nПомилка відкриття файлу.\n";
    else
    {
        inputfile << size << "\n";
        for(int i=0; i<size; i++) inputfile << Array[size-i-1] << " ";
    }
    inputfile.close();
    cout << "\nФайл заповнено.\n";
}
void Exit()
{
    cout << "\nВихід..." << "\n\n\n";
}
void UnReal()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nНевірний вибір. Будь ласка спробуйте ще раз.\n";
}
int main()
{
    srand(time(nullptr));
    double dmenu;
    int menu;
    do
    {
        cout << "\nМеню:\n";
        cout << "     1. Заповнити файл відсортованими числами (найкращий випадок).\n";
        cout << "     2. Заповнити файл випадковими числами (середній випадок).\n";
        cout << "     3. Заповнити файл відсортований у зворотному порядку - за спаданням (найгірший випадок).\n";
        cout << "     4. Шейкерне сортування (з використанням умови Айверсона).\n";
        cout << "     5. Сортування злиттям.\n";
        cout << "     6. За методом пірамідального сортування (з використанням структури даних «бінарна купа»).\n";
        cout << "     7. Вихід з програми.\n";
        cout << "\nВведіть свій вибір: ";
        cin >> dmenu;
        menu = dmenu;
        if (dmenu != menu) menu = 0;
        switch (menu)
        {
            case 1:
                FillArray1();
                break;
            case 2:
                FillArray2();
                break;
            case 3:
                FillArray3();
                break;
            case 4:
                FirstSort();
                break;
            case 5:
                SecondSort();
                break;
            case 6:
                ThirdSort();
                break;
            case 7:
                Exit();
                break;
            default:
                UnReal();
                break;
        }
    }while(menu != 7);
    return 0;
}