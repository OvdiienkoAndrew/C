#include <iostream> // Бібліотека, що містить стандартні потоки вводу-виводу (input/output stream).
#include <iomanip> // Бібліотека, що містить набір функцій для форматованого виводу.
using namespace std; // Директива, яка показує, що використовуються стандартні імена простору імен (namespace) зі стандартної бібліотеки С++.

const int N = 100; // Константа визначає розмір стеку, який складається зі 100 символів.
int i, j, index_Symbol1, index_Symbol2, errorCount, maxValue = numeric_limits<int>::max(); // Змінні для використання в циклах як індекси, які використовуються як у головному коді, так і в індивідуальному завданні, а також максимальне значення кількості елементів у виразі індивідуального завдання, щоб програма не зациклилася при великому вводі.
char Text[N], Symbol1, Symbol2; // Масив для вводу арифметичного виразу в індивідуальному завданні; а також одновимірні масиви для зберігання елементів дужок, для індивідуального завдання.

struct Bracket // Структура, яка визначає тип даних, який містить інформацію про дужки та їх індекси.
{
    char symbol; // Символ дужки.
    int OpenIndex; // Індекс відкритої дужки.
    int CloseIndex; // Iндекс закритої дужки.
};

template <class T> // Шаблонні класи дозволяють створювати класи, які можуть працювати з різними типами даних.
class MyStack // Створення свого класу.
{
public:
    T stack[N]; // Масив, який зберігає елементи стеку.
    int topIndex; // Змінна, зберігає кількість елементів у масиві.

    MyStack() : topIndex(-1) {} // Присвоєння значення кількості елементів.

    bool isFull() // Оголошення функції isFull без параметрів, яка перевіряє, чи стек повний.
    {
        return topIndex == N - 1; // Повертаємо значення true, якщо індекс останнього елемента дорівнює N-1, тобто стек повний, інакше повертаємо значення false.
    }

    void push(T element) // Оголошення функції push із параметром element, яка додає елементу до стеку.
    {
        if (topIndex >= N - 1) // Перевірка, чи стек заповненний.
        {
            return; // Не робимо нічого і завершуємо виконання методу.
        }
        stack[++topIndex] = element; // Збільшуємо значення індексу останнього елемента на 1 та присвоюємо йому значення елемента, що додається.
    }

    T pop() // Оголошення функції pop без параметрів, яка видаляє останній елемент зі стеку.
    {
        if (topIndex < 0) // Перевірка, чи стек порожній.
        {
            return T(); // Повертаємо пустий об'єкт типу T як підтвердження, що операція видалення не вдалася.
        }
        return stack[topIndex--]; // Повертаємо значення останнього елемента стеку і зменшуємо індекс останнього елемента на 1.
    }

    bool empty() // Оголошення функції empty без параметрів, яка перевіряє, чи стек порожній.
    {
        return topIndex < 0; // Повертаємо значення true, якщо індекс останнього елемента менший 0, тобто стек порожній, інакше повертаємо значення false.
    }

    T top() // Оголошення функції top без параметрів, яка повертає значення останнього елемента стеку, без його видалення.
    {
        if (topIndex < 0)  // Перевірка, чи стек порожній.
            return T();  // Повертаємо пустий об'єкт типу T як підтвердження, що операція неможлива.
        return stack[topIndex]; // Повертаємо значення останнього елемента стеку.
    }
};

MyStack<Bracket> stack;  // Створення об'єкту stack типу MyStack<Bracket>. Це змінна, яка представляє стек елементів типу Bracket.
MyStack<Bracket> tempStack; // Створення об'єкту tempStack типу MyStack<Bracket> для індивідуального завдання. Це змінна, яка представляє тимчасовий стек елементів типу Bracket.
Bracket c; // Створення змінної c типу Bracket. Це змінна, яка представляє один елемент типу Bracket.

void Push(char symbol) // Оголошення функції Push з одним параметром, який має тип char. Ця функція використовується для додавання нового елементу до стеку.
{
    if (stack.isFull()) // Перевірка, чи стек заповнений. 
    {
        cout << endl << "Вибачте, але стек переповнений. Неможливо додати ще один елемент." << endl; // Виведення повідомлення про те, що стек переповнений і неможливо додати ще один елемент.
    }
    else // Виконується, якщо стек не є повним.
    {
        cin.clear(); // Очищення потоку введення.
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Пропуск всіх символів до кінця рядка у введенні, якщо такі символи існують.
        cout << endl << "Введіть значення елемента: "; // Виведення повідомлення, щоб користувач ввів значення нового елементу для стеку.
        cin >> symbol; // Зчитування введеного користувачем значення для нового елементу стеку.
        c.symbol = symbol; // Присвоєння значення symbol змінній c типу Bracket.
        stack.push(c); // Додавання елементу c до стеку stack.
        cout << endl << "Успішно додано елемент: \"" << symbol << "\" - до стеку." << endl;  // Виведення повідомлення про успішне додавання елементу до стеку.
    }
} 

void stackScreen() // Оголошення функції stackScreen без параметрів. Ця функція використовується для відображення елементів стеку на екрані.
{
    if (stack.empty()) // Перевірка, чи стек є порожнім.
    {
        cout << endl << "Стек порожній." << endl; // Виведення повідомлення про те, що стек порожній.
    }
    else // Виконується, якщо стек не є порожнім.
    {
        if (stack.topIndex == 0) // Перевірка, чи індекс верхнього елементу стеку дорівнює 0. Виконується, якщо стек містить лише один елемент.
        {
            cout << endl << "Елемент стеку:" << endl;  // Виведення повідомлення про те, що стек містить лише один елемент.
            cout << endl << "               Символ: " << stack.stack[0].symbol << ", iндекс: " << 1;  // Виведення значення символу і індекса першого елементу стеку.
            if (i == 0) cout << ".\n"; // Умовна конструкція для форматованого виведення крапки в кінці рядка.
            else cout << ";\n"; // Умовна конструкція для форматованого виведення крапки з комою в кінці рядка.
            cout << endl; // Виведення порожнього рядка для форматування виводу.
        }
        else // Виконується, якщо стек містить більше одного елемента.
        {
            cout << endl << "Елементи стеку:" << endl; // Виведення повідомлення про те, що стек містить більше одного елемента.
            for (i = stack.topIndex; i >= 0; i--)  // Цикл для виведення всіх елементів стеку, починаючи з верхнього.
            {
                cout << endl << "               Символ: " << stack.stack[i].symbol << ", iндекс: " << i+1; // Виведення значення символу і індекса поточного елементу стеку.
                if (i == 0) cout << ".\n"; // Умовна конструкція для форматованого виведення крапки в кінці рядка.
                else cout << ";\n"; // Умовна конструкція для форматованого виведення крапки з комою в кінці рядка.
                cout << endl; // Виведення порожнього рядка для форматування виводу.
            }
        }
    }
}

void Pop() // Оголошення функції Pop без параметрів. Ця функція використовується для видалення останнього елемента зі стеку.
{
    if (stack.empty()) // Перевірка, чи стек є порожнім. 
    {
        cout << endl << "Вибачте, але стек порожній. Неможливо видалити останній елемент." << endl; // Виведення повідомлення про те, що стек порожній і неможливо видалити останній елемент.
    }
    else // Виконується, якщо стек не є порожнім.
    {
        stack.pop(); // Видалення останнього елемента зі стеку.
        cout << endl << "Успішно видалено останній елемент стеку." << endl; // Виведення повідомлення про успішне видалення останнього елемента стеку.
    }
}  

void ClearElements() // Оголошення функції ClearElements без параметрів. Ця функція використовується для видалення всіх елементів зі стеку.
{
    if (stack.empty()) // Перевірка, чи стек є порожнім. 
    {
        cout << endl << "Вибачте, але стек порожній. Неможливо видалити всі елементи стеку." << endl;  // Виведення повідомлення про те, що стек порожній і неможливо видалити всі елементи.
    }
    else // Виконується, якщо стек не є порожнім.
    {
        while(!stack.empty()) // Цикл, який видаляє всі елементи зі стеку до тих пір, поки стек не буде порожнім.
        {
            stack.pop(); // Видалення останнього елемента зі стеку.
        }
        cout << endl << "Успішно видалено всі елементи стеку." << endl; // Виведення повідомлення про успішне видалення всіх елементів стеку.
    }
}

void CountElementsIndex() // Оголошення функції CountElementsIndex без параметрів. Ця функція використовується для визначення кількості елементів у стеку, а також символів та індексів крайніх елементів.
{
    if (stack.empty()) // Перевірка, чи стек є порожнім.
    {
        cout << endl << "Кількість елементів у стеці: 0.\nВибачте, але стек порожній. Неможливо вказати перший і останній елементи стеку з індексами." << endl; // Виведення повідомлення про те, що стек порожній і неможливо вказати індекси першого і останнього елементів стеку.
    }
    else // Виконується, якщо стек не є порожнім.
    {
        cout << endl << "Кількість елементів у стеці: " << stack.topIndex+1 << ".\n"; // Виведення кількості елементів у стеку.
        if (stack.topIndex == 0) // Перевірка, чи стек містить лише один елемент.
        {
            cout << endl << "Єдиний елемент стеку: \"" << stack.stack[0].symbol << "\" - індекс єдиного елемента стеку: 1." << endl; // Виведення значення символу та індекса єдиного елемента стеку.
        }
        else // Виконується, якщо стек містить більше одного елемента.
        {
            cout << endl << "Перший елемент стеку: \"" << stack.stack[0].symbol << "\" - індекс першого елемента стеку: 1." << endl; // Виведення значення символу і індекса першого елемента стеку.
            cout << endl << "Останній елемент стеку: \"" << stack.stack[stack.topIndex].symbol << "\" - індекс останнього елемента стеку: " << stack.topIndex+1 << "." << endl;  // Виведення значення символу і індекса останнього елемента стеку.
        }
    }
}

void Task() // Оголошення функції Task без параметрів. Ця функція виконує індивідуальне завдання.
{
    index_Symbol1 = 0, index_Symbol2 = 0; // Ініціалізація індексів для сиволів нулями.
    Symbol1 = 0, Symbol2 = 0; // Ініціалізація сиволів нулями.
    errorCount = 0; // ініціалізація помилок нульом.
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Пропуск всіх символів до кінця рядка у введенні, якщо такі символи існують.
    cout << endl << "Введіть арифметичний вираз до індивідуального завдання (0 < кількість елементів виразу < 1000).\nЯкщо не дотримаєтесь границь - буде порожній рядок, натисність Enter.\nBираз: "; // У цьому рядку виводиться повідомлення з інструкціями для користувача щодо введення арифметичного виразу.
    cin.getline(Text, maxValue); // Зчитується ввід введений користувачем із стандартного вводу та зберігається в масиві Text.
    while(true) // Дійсний цикл, який робить свою роботу, поки не буде введений вираз із заданими умовами.
    {
        if(strlen(Text)>=1000 || strlen(Text)==0) // Перевіряємо, чи кількість символів в рядку Text не задовольняє встановлені умови (вираз має хочаб одне знначення та елементів елементів у виразі менше або дорівнює 1000). 
        {
            cin.clear(); // Oчищення флагів та стану вхідного потоку.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Пропуск всіх символів до кінця рядка у введенні, якщо такі символи існують.
            cout << "(0 < кількість елементів виразу < 1000)\nВираз: "; // Bиводиться повідомлення про необхідну кількість символів і проситься знову ввести вираз.
            cin.getline(Text, maxValue); // Зчитується ввід введений користувачем із стандартного вводу та зберігається в масиві Text.
        }
        else // Перевіряємо, чи кількість символів в рядку Text задовольняє встановлені умови (вираз має хочаб одне знначення та елементів елементів у виразі менше або дорівнює "N-1"). 
        {
            break; // Вихід із циклу, бо правильно введений вираз із умовами.
        }
    }
    cout << endl << "У першому стовпчику вкажіть положення відкриваючої дужки;\nУ другому – закриваючої;\nУ третьому – відповідні дужки." << endl << endl; // У цьому рядку виводиться повідомлення з інструкціями для користувача щодо вказування положення відкриваючої та закриваючої дужок у виразі.
    for ( i = 0; Text[i] != '\0'; i++) // Дійсний цикл, який зчитує вираз введений користувачем поки не закінчиться вираз.
    {
        if (Text[i] == '(') // Перевірка, чи значення у виразі є відкриваючою дужкою.
        {
            Symbol1 = Text[i]; // Присвоєння значення відкритої дужки змінній Symbol1.
            index_Symbol1 = i; // Присвоєння значення індекса відкритої дужки змінній index_Symbol1.
            c.symbol = Symbol1; // Присвоєння значення відкритої дужки змінній c типу Bracket (symbol).
            c.OpenIndex = index_Symbol1; // Присвоєння значення індекса відкритої дужки змінній c типу Bracket (OpenIndex).
            tempStack.push(c); // Додавання елементу c до стеку tempStack.
        }
        if (Text[i] == ')') // Перевірка, чи значення у виразі є закриваючою дужкою.
        {
            Symbol2 = Text[i]; // Присвоєння значення закритої дужки змінній Symbol2.
            index_Symbol2 = i; // Присвоєння значення індекса закритої дужки змінній index_Symbol2.
            if (!tempStack.empty()) // Перевірка, чи стек не є порожнім.
            {
                c = tempStack.top(); // Присвоєння останнього значенняв стеці змінній c типу Bracket.
                c.CloseIndex = index_Symbol2; // Присвоєння значення індекса закриваючої дужки змінній c типу Bracket (CloseIndex).
                cout << setw(8) << c.OpenIndex + 1 << setw(8) << c.CloseIndex + 1 << setw(8) << c.symbol << ")" << endl; // Вивід індексів правильно розставленних дужок та самі ці дужки.
                tempStack.pop(); // Видалення останнього елементу зі стеку tempStack.
            }
            else // Перевірка, чи стек не порожнім.
            {
                c.symbol = Symbol2; // Присвоєння значення закритої дужки змінній c типу Bracket (symbol).
                c.CloseIndex = index_Symbol2; // Присвоєння значення індекса закриваючої дужки змінній c типу Bracket (CloseIndex).
                cout << setw(8) << 0 << setw(8) << c.CloseIndex + 1 << setw(8) << c.symbol << endl; // Вивід індексів неправильно розставленних дужок та дужку закриття, яка не має пари відкритої дужки.
                errorCount++; // Збільшення значення помилки на 1.
            }
        }
    }
    while (!tempStack.empty()) // Цикл, який працює до тих пір, поки стек не буде порожнім.
    {
        c = tempStack.top(); // Присвоєння останнього значенняв стеці змінній c типу Bracket.
        cout << setw(8) << c.OpenIndex + 1 << setw(8) << 0 << setw(8) << c.symbol << endl; // Вивід індексів неправильно розставленних дужок та дужку відкриття, яка не має пари закритої дужки.
        tempStack.pop(); // Видалення останнього елементу зі стеку tempStack.
        errorCount++; // Збільшення значення помилки на 1.
    }
    if (errorCount == 0) // Перевірка, чи немає помилок.
    {
        cout << endl << "Немає помилок у розстановці дужок. Чудово." << endl; // Вивід повідомлення про конкретне розставляння дужок.
    }
    else // Перевірка, чи є помилки.
    {
        cout << endl << "Кількість помилок: " << errorCount << ". Уважніше розсталяйте дужки." << endl; // Вивід повідомлення про неконкретне розставляння дужок.
    }
}

void Exit() // Оголошення функції Exit без параметрів. Ця функція виводить повідомлення про завершення програми.
{
    cout << endl << "Вихід..." << "\n\n\n"; // Виводить повідомлення про вихід із програми.
}

void UnReal() // Оголошення функції UnReal без параметрів. Ця функція недозволяє програмі зациклитися при неправильному вводі користувача пунктів меню.
{
    cin.clear(); // Очищення потоку введення.
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Пропуск всіх символів до кінця рядка у введенні, якщо такі символи існують.
    cout << endl << "Невірний вибір. Будь ласка спробуйте ще раз." << endl; // Виводить повідомлення про неправильний вибір і просить спробувати ще раз.
}

int main(int argc, char** argv) // Оголошення функції main з параметрами argc (кількість аргументів командного рядка) і argv (масив з аргументами командного рядка) і поверненням цілого значення.
{
    int choice = 0; // Ініціалізація змінної "choice" значенням 0, для вибору пункту меню.
    char symbol; // Оголошення змінної "a" типу char, для гри зі структурою данних.
    do // Робити.
    {
        cout << endl << "Меню:" << endl; // Вивести повідомлення про те, що відображається меню.
        cout << "     1. Додати елемент до структури даних." << endl; // Вивести повідомлення: "1. Додати елемент до структури даних.".
        cout << "     2. Видалити елемент зі структури даних." << endl; // Вивести повідомлення: "2. Видалити елемент зі структури даних.".
        cout << "     3. Вивести елементи структури на екран." << endl; // Вивести повідомлення: "3. Вивести елементи структури на екран.".
        cout << "     4. Вивести кількість елементів структури. Для черги – індекси першого та останнього елементів (голови та хвоста)." << endl; // Вивести повідомлення: "4. Вивести кількість елементів структури. Для черги – індекси першого та останнього елементів (голови та хвоста).".
        cout << "     5. Очистити структуру." << endl; // Вивести повідомлення: "5. Очистити структуру.".
        cout << "     6. Пункти щодо індивідуальних завдань згідно з варіантом." << endl; // Вивести повідомлення: "6. Пункти щодо індивідуальних завдань згідно з варіантом.".
        cout << "     7. Завершення роботи." << endl; // Вивести повідомлення: "7. Завершення роботи.".
        cout << endl << "Введіть свій вибір: ";  // Вивести повідомлення про можливість ообрання пункту меню.
        cin >> choice; // Зчитування вибору пункта меню, який бажає відкрити користувач.
        switch (choice)  // Перехід до відповідного варіанту в залежності від вибору користувача.
        {
            case 1: // Якщо веденно "1".
                Push(symbol); // Виклик функції для додавання елементу до структури даних.
                break; // Завершення виконання case 1.
            case 2: // Якщо веденно "2".
                Pop(); // Виклик функції для видалення останнього елемента зі структури даних.
                break; // Завершення виконання case 2.
            case 3: // Якщо веденно "3".
                stackScreen(); // Виклик функції для виведення елементів структури на екран.
                break; // Завершення виконання case 3.
            case 4: // Якщо веденно "4".
                CountElementsIndex(); // Виклик функції для виведення кількості елементів структури та індексів голови та хвоста.
                break; // Завершення виконання case 4.
            case 5: // Якщо веденно "5".
                ClearElements(); // Виклик функції для очищення структури.
                break; // Завершення виконання case 5.
            case 6: // Якщо веденно "6".
                Task(); // Виклик функції для виконання пунктів індивідуального завдання.
                break; // Завершення виконання case 6.
            case 7: // Якщо веденно "7".
                Exit(); // Виклик функції для завершення роботи.
                break; // Завершення виконання case 7.
            default: // Інші випадки.
                UnReal(); // Виклик функції для обробки нереалізованих пунктів.
                break; // Завершення виконання default.
        }
        cout << endl; // Виведення порожнього рядка для форматування виводу.
    } while (choice != 7); // Повторення циклу, доки користувач не вибере пункт 7 (завершення роботи).
    return 0; // Повертається значення 0 для позначення успішного завершення програми.
}