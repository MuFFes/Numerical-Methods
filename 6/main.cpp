#include <iostream>
#include <iomanip>
#define ARR_SIZE 6

using namespace std;

void print_vector(double v[ARR_SIZE]) {
    cout << "[";
    for (int i = 0; i < ARR_SIZE; i++){
        cout << v[i];
        if (i != ARR_SIZE - 1)
            cout << ", ";
    }
    cout << "]" << endl;
}

void thomas_algorithm(double u[ARR_SIZE], double d[ARR_SIZE], double l[ARR_SIZE], double b[ARR_SIZE]) {
    for (int i = 1; i < ARR_SIZE; i++) {
        l[i - 1] /= d[i - 1];
        d[i] -= (l[i - 1] * u[i]);
        b[i] -= l[i - 1] * b[i - 1];
    }
}

void calculate_x(double u[ARR_SIZE], double d[ARR_SIZE], double x[ARR_SIZE], double b[ARR_SIZE]) {
    // Obliczenie wartości ostatniego x
    x[ARR_SIZE - 1] = b[ARR_SIZE - 1] / d[ARR_SIZE - 1];
    // Obliczenie wartości pozostałych x
    for (int i = ARR_SIZE - 2; i >= 0; i--) {
        x[i] = (b[i] - u[i + 1] * x[i + 1]) / d[i];
    }
}

int main() {
    cout << fixed;
    cout << setprecision(5);

    double u[ARR_SIZE] = {    0.0,   1.0/2.0,    1.0/4.0,    1.0/6.0,     1.0/8.0,   1.0/10.0};
    double d[ARR_SIZE] = {   10.0,      20.0,       30.0,       30.0,        20.0,       10.0};
    double l[ARR_SIZE] = {1.0/3.0,   1.0/5.0,    1.0/7.0,    1.0/9.0,    1.0/11.0,        0.0};

    double b[ARR_SIZE] = {   31.0, 165.0/4.0, 917.0/30.0, 851.0/28.0, 3637.0/90.0, 332.0/11.0};

    cout << " u = ";
    print_vector(u);    
    cout << " d = ";
    print_vector(d);    
    cout << " l = ";
    print_vector(l);    
    cout << " b = ";
    print_vector(b);
    cout << endl;

    // Zastosowanie algorytmu Thomasa
    thomas_algorithm(u, d, l, b);

    cout << " u = ";
    print_vector(u);    
    cout << " d = ";
    print_vector(d);    
    cout << " l = ";
    print_vector(l);    
    cout << " b = ";
    print_vector(b);
    cout << endl;

    // Obliczenie wartości wektora x 
    double x[ARR_SIZE] = {0};
    calculate_x(u, d, x, b);

    cout << " u = ";
    print_vector(u);    
    cout << " d = ";
    print_vector(d);    
    cout << " l = ";
    print_vector(l);    
    cout << " b = ";
    print_vector(b);
    cout << " x = ";
    print_vector(x);
    cout << endl;

}