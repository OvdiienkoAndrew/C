// Написати програму, яка транспонує (відображує) на місці квадратну матрицю. З цією метою програма вводить ціле N (1<=N<=100), потім матрицю цілих розміру N*N, транспонує її на місці (за допомогою відповідної функції, яку Вам треба написати) і виводить на екран у зручному вигляді (по рядках). Спосіб відображення: відносно побічної діагоналі.

#include <iostream>
#include <iomanip>
using namespace std;

int ** arr;

void arrs(int n) {
    arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
    }
}

void free(int n) {
    for (int i = 0; i < n; i++) {
        delete[] arr[i];}
    delete[] arr;}

void tM(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i + j < n - 1) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[n - j - 1][n - i - 1];
                matrix[n - j - 1][n - i - 1] = temp;}}}}

int main() {
    int n;
    cout << "Enter the value of N (1 <= N <= 100): ";
    while (true) {
        cout << "N = ? ";
        cin >> n;
        if (!cin) { cin.clear();
            cin.ignore();
            cout << "Invalid input. Try again.\n";
        }
        if (n < 1 || n > 100) {
            cout << "N (1 <= N <= 100). Try again.\n";
        }
        else { break; }
    }
  
    arrs(n);

    cout << "Enter the elements of the matrix:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << "A[" << i << "][" << j << "] = ? ";
            cin >> arr[i][j];}}

    cout << "Matrix:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << setw(6) << arr[i][j] << " "; } cout << "\n";}

    tM(arr, n);

    cout << "\nThe transposed matrix is:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << setw(6) << arr[i][j] << " ";} cout << "\n";}

    free(n);

    return 0;
}