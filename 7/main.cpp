#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

#define ARR_SIZE 4
#define MAX_ITERATIONS 32
#define EPS 1e-6
#define OMEGA 0.5

using namespace std;

void print_matrix(double A[ARR_SIZE][ARR_SIZE]) {
    for (int i = 0; i < ARR_SIZE; i++) {
        for (int j = 0; j < ARR_SIZE; j++) {
            cout << A[i][j] << " \t";
        }
        cout << endl;
    }
}

void print_vector(double b[ARR_SIZE], const char* name = "x") {
    cout << "\t" << name << " = [";
    for (int i = 0; i < ARR_SIZE; i++)
        cout << b[i] << ((i == ARR_SIZE - 1) ? "]" : ", ");
    cout << endl;
}

double maximum_norm(double p[ARR_SIZE]) {
    double max_abs = 0.0;
    for (int i = 0; i < ARR_SIZE; i++)
        if (fabs(p[i]) > max_abs)
            max_abs = fabs(p[i]);

    return max_abs;
}

double *residuum(double A[ARR_SIZE][ARR_SIZE], double x[ARR_SIZE], double b[ARR_SIZE]) {
    double *res = new double[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; i++) {
        double sum = 0;
        for (int j = 0; j < ARR_SIZE; j++) {
            sum += A[i][j] * x[j];
        }
        res[i] = sum - b[i];
    }
    return res;
}

void print_info(int iteration, double A[ARR_SIZE][ARR_SIZE], double prev_x[ARR_SIZE], double x[ARR_SIZE], double b[ARR_SIZE]) {
    cout << iteration << " iteracja:" << endl;
    print_vector(x);
    cout << "\tWartosc normy maksimum wektora residualnego: " << fabs(maximum_norm(residuum(A, x, b)))     << endl;
    cout << "\tWartosc normy z przyblizen pierwiastkow: "     << fabs((maximum_norm(x) - maximum_norm(prev_x))) << endl;
}

void jacobi(double A[ARR_SIZE][ARR_SIZE], double prev_x[ARR_SIZE], double x[ARR_SIZE], double b[ARR_SIZE]) {
    for (int iteration = 1; iteration <= MAX_ITERATIONS; iteration++) {
        swap(x, prev_x);
        for (int i = 0; i < ARR_SIZE; i++) {
            double sigma = 0;
            for (int j = 0; j < ARR_SIZE; j++) {
                if (j != i)
                    sigma += A[i][j] * prev_x[j];
            }
            x[i] = (b[i] - sigma) / A[i][i];
        }
        print_info(iteration, A, prev_x, x, b);

        if (fabs((maximum_norm(residuum(A, x, b)))) < EPS)
            break; 
        if (fabs((maximum_norm(x) - maximum_norm(prev_x))) < EPS)
            break; 
    }
}

void gauss_seidel(double A[ARR_SIZE][ARR_SIZE], double prev_x[ARR_SIZE], double x[ARR_SIZE], double b[ARR_SIZE])
{
    for (int iteration = 1; iteration <= MAX_ITERATIONS; iteration++) {
        for (int i = 0; i < ARR_SIZE; i++) {
            double sigma = 0;
            prev_x[i] = x[i];

            for (int j = 0; j <= i - 1; j++) {
                sigma += A[i][j] * x[j];
            }

            for (int j = i + 1; j < ARR_SIZE; j++) {
                sigma += A[i][j] * x[j];
            }

            x[i] = (b[i] - sigma) / A[i][i];
        }
        print_info(iteration, A, prev_x, x, b);

        if (fabs((maximum_norm(residuum(A, x, b)))) < EPS)
            break;
        if (fabs((maximum_norm(x) - maximum_norm(prev_x))) < EPS)
            break;
    }
}

void sor(double A[ARR_SIZE][ARR_SIZE], double prev_x[ARR_SIZE], double x[ARR_SIZE], double b[ARR_SIZE])
{
    for (int iteration = 1; iteration <= MAX_ITERATIONS; iteration++) {
        for (int i = 0; i < ARR_SIZE; i++) {
            double sigma = 0;
            prev_x[i] = x[i];
            
            for (int j = 0; j <= i - 1; j++)
                sigma += A[i][j] * x[j];
            
            for (int j = i; j < ARR_SIZE; j++) {
                if (j == i)
                    sigma += (1 - (1.0 / OMEGA)) * A[i][i] * x[j];
                else
                    sigma += A[i][j] * x[j];
            }
            x[i] = (b[i] - sigma) / A[i][i] * OMEGA;
        }
        print_info(iteration, A, prev_x, x, b);

        if (fabs((maximum_norm(residuum(A, x, b)))) < EPS)
            break; 
        if (fabs((maximum_norm(x) - maximum_norm(prev_x))) < EPS)
            break; 
    }
}

void solve(void (*function)(double [ARR_SIZE][ARR_SIZE], double[ARR_SIZE], double[ARR_SIZE], double[ARR_SIZE]), double start_A[ARR_SIZE][ARR_SIZE], double start_x[ARR_SIZE], double start_b[ARR_SIZE]) {
    // Utworzenie kopii zestawu danych wejściowych
    double A[ARR_SIZE][ARR_SIZE];
    double x[ARR_SIZE];
    double b[ARR_SIZE];
    memcpy(A, start_A, ARR_SIZE * ARR_SIZE * sizeof(double));
    memcpy(x, start_x, ARR_SIZE * sizeof(double));
    memcpy(b, start_b, ARR_SIZE * sizeof(double));
    double prev_x[ARR_SIZE];

    function(A, prev_x, x, b);
}

int main()
{
    cout << setprecision(6);
    double start_A[ARR_SIZE][ARR_SIZE] = {
        {100.0,   -1.0,    2.0,   -3.0},
        {  1.0,  200.0,   -4.0,    5.0},
        { -2.0,    4.0,  300.0,   -6.0},
        {  3.0,   -5.0,    6.0,  400.0}
    };
    double start_x[ARR_SIZE] = {  2.0,     2.0,    2.0,     2.0};
    double start_b[ARR_SIZE] = {116.0,  -226.0,  912.0, -1174.0};
    double omega = 0.5;

    cout << "1. Metoda Jacobiego:" << endl;
    cout << "------------------------------" << endl;
    solve(jacobi, start_A, start_x, start_b);
    cout << "------------------------------" << endl;


    cout << "2. Metoda Gaussa-Seidela:" << endl;
    cout << "------------------------------" << endl;
    solve(gauss_seidel, start_A, start_x, start_b);
    cout << "------------------------------" << endl;


    cout << "3. Metoda SOR:" << endl;
    cout << "------------------------------" << endl;
    solve(sor, start_A, start_x, start_b);
    cout << "------------------------------" << endl;

    return 0;
}
