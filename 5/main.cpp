#include <iostream>
#include <iomanip>
#include <math.h>

#define ARR_SIZE 4

using namespace std;

void print_array(double arr[ARR_SIZE][ARR_SIZE]){
    for (int i = 0; i < ARR_SIZE; i++){
        for (int j = 0; j < ARR_SIZE; j++){
            cout << setw(10) << arr[i][j] << ",";
        }
        cout << endl;
    }
    cout << endl;
}

void print_vector(double v[ARR_SIZE]) {
    cout << "[";
    for (int i = 0; i < ARR_SIZE; i++){
        cout << v[i];
        if (i != ARR_SIZE - 1)
            cout << ", ";
    }
    cout << "]" << endl;
}


void decomposition(double A[ARR_SIZE][ARR_SIZE], double L[ARR_SIZE][ARR_SIZE], double b[ARR_SIZE]) {
    for (int i = 0; i < ARR_SIZE; i++) {
        // Częściowy wybór elementu podstawowego
        if (A[i][i] == 0.0) {
            double max = 0;
            int index_max = 0;
            for (int j = i + 1; j < ARR_SIZE; j++) {
                if (fabs(A[j][i]) > max) {
                    max = fabs(A[j][i]);
                    index_max = j;
                }
            }
            // Zamiana kolejności wierszy macierzy U
            swap(A[i], A[index_max]);
            // Zamiana kolejności wierszy macierzy L
            swap(L[i], L[index_max]);
            // Zamiana kolejności wierszy wektora b
            swap(b[i], b[index_max]);
        }
        for (int j = i + 1; j < ARR_SIZE; j++) {
            // Obliczenie współczynnika do metody eliminacji Gaussa
            double multiplier = A[j][i] / A[i][i];
            L[j][i] = multiplier;
            for (int k = i; k < ARR_SIZE; k++) {
                // Sumowanie wierszy w celu wyzerowania wartości pod przekątną
                A[j][k] -= A[i][k] * multiplier;
            }
        }
    }
}

void calculate_y(double L[ARR_SIZE][ARR_SIZE], double b[ARR_SIZE], double y[ARR_SIZE]) {
    for (int i = 0; i < ARR_SIZE; i++) {
        for (int j = 0; j <= i; j++) {
            if (i == j)
                y[i] += b[i];
            else
                y[i] -= L[i][j] * y[j];
        }
    }
}


void calculate_x(double A[ARR_SIZE][ARR_SIZE], double y[ARR_SIZE], double x[ARR_SIZE]) {
    for (int i = ARR_SIZE - 1; i >= 0; i--) {
        for (int j = i; j < ARR_SIZE; j++) {
            if (i == j)
                x[i] += y[i] / A[i][i];
            else
                x[i] -= A[i][j] * x[j] / A[i][i];
        }
    }
}

int main()
{
    cout << fixed;
    cout << setprecision(3);

    double A[ARR_SIZE][ARR_SIZE] = {
        {  1.0,  -20.0,   30.0,  -4.0},
        {  2.0,  -40.0,   -6.0,  50.0},
        {  9.0, -180.0,   11.0, -12.0},
        {-16.0,   15.0, -140.0,  13.0}
    };

    double b[ARR_SIZE] = {35.0, 104.0, -366.0, -354.0};
    
    double L[ARR_SIZE][ARR_SIZE] = {
        { 1.0,  0.0,  0.0,  0.0},
        { 0.0,  1.0,  0.0,  0.0},
        { 0.0,  0.0,  1.0,  0.0}, 
        { 0.0,  0.0,  0.0,  1.0}
    };

    decomposition(A, L, b);
    cout << " U : " << endl;
    print_array(A);
    cout << " L : " << endl;
    print_array(L);
    // Po przebiegu powyższej pętli tablica A przechowuje wartości macierzy górnotrójkątnej U
    // Tablica L przechowuje wartości macierzy dolnotrójkątnej L

    // Wektor pomocniczy y: Ly = b
    double y[ARR_SIZE] = {0.0, 0.0, 0.0, 0.0};
    // Wektor rozwiązania x: Ux = y 
    double x[ARR_SIZE] = {0.0, 0.0, 0.0, 0.0};
    
    // Wyświetlenie wartości wektora b
    cout << "b = ";
    print_vector(b);
    // Obliczenie wartości wektora y
    calculate_y(L, b, y);
    // Wyświetlenie wartości wektora y
    cout << "y = ";
    print_vector(y);
    // Obliczenie wartości wektora x
    calculate_x(A, y, x);
    // Wyświetlenie wartości wektora x
    cout << "x = ";
    print_vector(x);
}  