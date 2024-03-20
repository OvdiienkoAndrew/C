#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
void fillMatrixFromFile(int** matrix1, int rows1, int cols1, int** matrix2, int rows2, int cols2, const char* filename) 
{
    ifstream file(filename);
    if(file.peek() == ifstream::traits_type::eof())
    {   
        cerr << "\tФайл пустий.\n";
        file.close();
        return;
    }
    if (!file.is_open())
    {
        cerr << "\tПомилка відкриття файлу.\n";
        return;
    }     
    if(!file.good())
    {
        cerr << "\tПомилка переведення данних із файлу.\n";
        file.close();
        return;
    }
    for (int i = 0; i < rows1; i++) 
    {
        for (int j = 0; j < cols1; j++) 
        {
            if (!(file >> matrix1[i][j])) 
            {
                cerr << "\tНекорректний формат данних у файлі.\n";
                file.close();
                return;
            }
        }
    }
    for (int i = 0; i < rows2; i++) 
    {
        for (int j = 0; j < cols2; j++) 
        {
            if (!(file >> matrix2[i][j])) 
            {
                cerr << "\tНекорректний формат данних у файлі.\n";
                file.close();
                return;
            }
        }
    }
    if (!file.eof()) 
    {
        cerr << "\tНевдалося прочитати всі дані з файлу.\n";
        file.close();
        return;
    }
    for (int i = 0; i < rows1; i++) 
    {
        for (int j = 0; j < cols1; j++) 
        {
            file >> matrix1[i][j];
        }
    }
    for (int i = 0; i < rows2; i++) 
    {
        for (int j = 0; j < cols2; j++) 
        {
            file >> matrix2[i][j];
        }
    }
    cout << "\tМатриця A[" << rows1 << "][" << cols1 << "]:\n\n";
    for (int i=0; i<rows1; i++)
    {
        cout << "\t|";
        for (int j=0; j<cols1; j++)
        {
            cout << setw(7) << matrix1[i][j] << " ";
        }
        cout << setw(7) << "|\n";
    }
    cout << "\n\n\tМатриця B[" << rows2 << "][" << cols2 << "]:\n\n";
    for (int i=0; i<rows2; i++)
    {
        cout << "\t|";
        for (int j=0; j<cols2; j++)
        {
            cout << setw(7) << matrix2[i][j] << " ";
        }
        cout << setw(7) << "|\n";
    }
    file.close();
}
void fillrandMatrix(int **A, int n, int m)
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            A[i][j] = rand()%201-100;
        }
    }
}
void coutMatrix(int **A, int n, int m)
{
    for (int i=0; i<n; i++)
    {
        cout << "\t|";
        for (int j=0; j<m; j++)
        {
            cout << setw(7) << A[i][j] << " ";
        }
        cout << setw(7) << "|\n";
    }
    cout << "\n\n";
}
void printToFile(int **matrix1, int rows1, int cols1, int **matrix2, int rows2, int cols2, const char* filename, int o1, int o2, int min, int* matrix3) {
    ofstream file(filename);
    if (!file.is_open()) 
    {
        cerr << "\tПомилка відкриття файлу.\n";
        return;
    }
    file << "\n\tМінімальний елемент матриці А[" << rows1 << "][" << cols1 << "] = " << min << ", де цей елемент в матриці А[" << o1 + 1 << "][" << o2 + 1 << "].\n\t" << "Мінімальний елементом матриці А замінив всі від’ємні елементи матриці B.\n\n\tМатриця B[" << rows2 << "][" << cols2 << "]:\n\n";
    for (int i = 0; i < rows2; i++) 
    {
        file << "\t|";
        for (int j = 0; j < cols2; j++) 
        {
            file << setw(7) << matrix2[i][j] << " ";
        }
        file << setw(7) << "|\n";
    }
    file << "\n\tКожний i-й елемент лінійного вектора С являє собою суму елементів i-го рядка матриці А.\n\n\tС = | ";
    for (int i = 0; i < rows1; i++) 
    {
        file << matrix3[i] << " ";
    }
    file << "|\n\n\tМінімальне значення матриці А[" << rows1 << "][" << cols1 << "] = " << min << ", де цей елемент в матриці А[" << o1 + 1 << "][" << o2 + 1 << "]." << "\n\tМатриця А[" << rows1 << "][" << cols1 << "] після упорядкування за зростанням значення елементів стовпця, де знаходиться мінімальний елемент матриці.\n\n\tМатриця A[" << rows1 << "][" << cols1 << "]:\n\n";
    for (int i = 0; i < rows1; i++) 
    {
        file << "\t|";
        for (int j = 0; j < cols1; j++) 
        {
            file << setw(7) << matrix1[i][j] << " ";
        }
        file << setw(7) << "|\n";
    }
    file.close();
}
int main(int argc, char *argv[])
{
    srand(time(nullptr));
    int n1, n2, m1, m2;
    cout << "\n\tMатриці А та В розміром n x m, де n і m ≥ 6.\n\n\tРозмірність матриці А[n][m]:\n\n";
    do
    {
        cout << "\tn = ";
        cin >> n1;
        if(n1<6)
        {
            cout << "\n\tОДЗ: n ≥ 6\n";
        }
    }while(n1<6);
    cout << "\n";
    do
    {
        cout << "\tm = ";
        cin >> m1;
        if(m1<6)
        {
            cout << "\n\tОДЗ: m ≥ 6\n";
        }
    }while(m1<6);
    cout << "\n\tРозмірність матриці B[n][m]:\n\n";
    do
    {
        cout << "\tn = ";
        cin >> n2;
        if(n2<6)
        {
            cout << "\n\tОДЗ: n ≥ 6\n";
        }
    }while(n2<6);
    cout << "\n";
    do
    {
        cout << "\tm = ";
        cin >> m2;
        if(m2<6)
        {
            cout << "\n\tОДЗ: m ≥ 6\n";
        }
    }while(m2<6);
    int **A = new int*[n1]; for (int i=0; i<n1; i++) A[i] = new int[m1];
    int **B = new int*[n2]; for (int i=0; i<n2; i++) B[i] = new int[m2];
    int* C = new int[n1]; delete[] C;
    bool x = false;
    char choice;
    cout << "\n\tЗаповнити матрицю із файлу? (y/n) ";
    while (x == false)
    {
        cin >> choice;
        switch(choice)
        {
            case 'y':
                    x = true;
                    break;
            case 'n':
                    x = true;
                    break;
            default: 
                    cout << "\tА я такого не казав вводити.\nСпробуйте ще раз.\n";
                    break;
        }
    }
    char choice2;
    char* filename;
    cout << "\n\n";
    if (choice == 'y') 
    {
        x = false;
        cout << "\n\tІмʼя файлу задано в командному рядку? (y/n) ";
        while (x == false)
        {
            cin >> choice2;
            switch(choice2)
            {
              case 'y':
                        x = true;
                        break;
              case 'n':
                        x = true;
                        break;
             default: 
                        cout << "\tА я такого не казав вводити.\nСпробуйте ще раз.\n";
                        break;
            }
        }
        if (choice2 == 'y')
        {
            if (argc == 2) 
            {
                filename = argv[1];
            }
            else 
            {
                cout << "\tІмʼя файлу не задано. Введіть імʼя файлу (повне імʼя файлу): ";
                cin >> filename[100];
            }
        }
        if (choice2 == 'n')
        {
            cout << "\tВведіть імʼя файлу (повне імʼя файлу): ";
            cin >> filename[100];
        }
        fillMatrixFromFile(A, n1, m1, B, n2, m2, filename);
    }
    if (choice == 'n') 
    {
        fillrandMatrix(A, n1, m1);
        fillrandMatrix(B, n2, m2);
        cout << "\tМатриця A[" << n1 << "][" << m1 << "]:\n\n";
        coutMatrix(A, n1, m1);
        cout << "\tМатриця B[" << n2 << "][" << m2 << "]:\n\n";
        coutMatrix(B, n2, m2);
    }
    int min = A[0][0];
    int o1 = 0, o2 = 0;
    for (int i=0; i<n1; i++)
    {
        for (int j=0; j<m1; j++)
        {
            if (A[i][j]< min)
            {
                min = A[i][j];
                o1 = i;
                o2 = j;
            }
        }
    }
    for (int i=0; i<n2; i++)
    {
        for (int j=0; j<m2; j++)
        {
            if (B[i][j]< 0)
            {
                B[i][j] = min;
            }
        }
    }
    cout  << "\tМінімальний елемент матриці А[" << n1 << "][" << m1 << "] = " << min << ", де цей елемент в матриці А[" << o1+1 << "][" << o2+1 << "].\n\t" << "Mінімальний елементом матриці А замінив всі від’ємні елементи матриці B.\n\n\tМатриця B[" << n2 << "][" << m2 << "]:\n\n";
    coutMatrix(B, n2, m2);
    cout << "\tКожний i-й елемент лінійного вектора С являє собою суму елементів i-го рядка матриці А.\n\n\tС = | ";
    for (int i=0; i<n1; i++)
    {
        int sum = 0;
        for (int j=0; j<m1; j++)
        {
            sum += A[i][j];
        }
        C[i] = sum;
        cout << C[i] << " ";
    }
    cout << "|\n\n";
    for (int i =0; i<n1-1; i++)
    {
        for(int j=i+1; j<n1; j++)
        {
            if (A[i][o2]>A[j][o2])
            {  
                for (int k=0; k<m1; k++)
                {
                    swap(A[i][k], A[j][k]);
                }
            }
        }
    }
    cout << "\tМінімальне значення матриці А[" << n1 << "][" << m1 << "] = " << min << ", де цей елемент в матриці А[" << o1+1 << "][" << o2+1 << "]." << "\n\tМатриця А[" << n1 << "][" << m1 << "] після упорядкування за зростанням значення елементів стовпця, де знаходиться мінімальний елемент матриці.\n\n\tМатриця A[" << n1 << "][" << m1 << "]:\n\n";
    coutMatrix(A, n1, m1);  
    x = false;
    cout << "\tЗаписати дані у файл? (y/n) ";
    while (x == false)
    {
        cin >> choice;
        switch(choice)
        {
            case 'y':
                    x = true;
                    break;
            case 'n':
                    x = true;
                    break;
            default: 
                    cout << "\tА я такого не казав вводити.\n\tСпробуйте ще раз.\n";
                    break;
        }
    }
    if (choice == 'y') 
    {
        char outFilename[100];
        cout << "\tВведіть імʼя файлу (повне імʼя файлу): ";
        cin >> outFilename;
        printToFile(A, n1, m1, B, n2, m2, outFilename, o1, o2, min, C);
    }
    cout << "\n\n";
    return 0;
}