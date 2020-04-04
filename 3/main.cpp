#include <math.h>
#include <iostream>
#define MAX_ITERATIONS 100
#define REQUIRED_ACCURACY 2.22045e-16

using namespace std;

double f1(double x) {
    return sin(x / 4.0) * sin(x / 4.0) - x;
}

double f1_derivative(double x) {
    return 0.25 * sin(x / 2.0) - 1;
}

double f1_picard(double x) {
    return sin(x / 4.0) * sin(x / 4.0);
}

double f1_picard_derivative(double x) {
    return 0.25 * sin(x / 2.0);
}

double f2(double x) {
    return tan(2.0 * x) - x - 1;
}

double f2_derivative(double x) {
    return -1.0 + 2.0 / (cos(2.0 * x) * cos(2.0 * x));
}

double f2_picard(double x) {
    return tan(2.0 * x) - 1;
}

double f2_picard_derivative(double x) {
    return 2.0 / (cos(2.0 * x) * cos(2.0 * x));
}

double picards_method(double (*f)(double), double (*derivative)(double), double x0) {
    if (fabs(derivative(x0)) >= 1)
        throw "Wartosc bezwzgledna fi(x) nie jest mniejsza od 1, zatem funkcja nie jest zbiezna.";
    
    double result;
    for (int i = 1; i <= MAX_ITERATIONS; i++){
        result = f(x0);

        double estimator = fabs(result - x0);
        double residuum  = fabs(f(result));

        cout << "Iteracja " << i 
             << ":\t Wartosc przyblizona: " << result 
             << "\t est: " << estimator
             << "\t res: " << residuum 
             << endl;
        
        if (estimator <= REQUIRED_ACCURACY)
            break;
        if (residuum <= REQUIRED_ACCURACY)
            break;

        x0 = result;
    }
    return result;
}

int sign(double a){
    if (a >= 0.0)
        return 1;
    else 
        return -1;
}

double bisection_method(double (*f)(double), double start_x, double end_x) {
    if (sign(f(start_x)) == sign(f(end_x)) || sign(f(start_x)) == sign(f(end_x)))
        throw "Początek i koniec przedziału mają taki sam znak.";
    
    double result = (start_x + end_x) / 2;
    for (int i = 1; i <= MAX_ITERATIONS; i++){
        if (sign(f(result)) == sign(f(start_x)))
            start_x = result;
        else
            end_x = result;

        result = (start_x + end_x) / 2;

        double estimator = fabs((end_x - start_x) / 2);
        double residuum  = fabs(f(result));

        cout << "Iteracja " << i 
             << ":\t Wartosc przyblizona: " << result 
             << "\t est: " << estimator
             << "\t res: " << residuum 
             << endl;

        if (estimator <= REQUIRED_ACCURACY)
            break;
        if (residuum <= REQUIRED_ACCURACY)
            break;
    }
    return result;
}

double newtons_method(double (*f)(double), double (*derivative)(double), double x0) {
    double result;
    for (int i = 1; i <= MAX_ITERATIONS; i++){
        result = x0 - (f(x0) / derivative(x0));

        double estimator = fabs(result - x0);
        double residuum  = fabs(f(result));

        cout << "Iteracja " << i 
             << ":\t Wartosc przyblizona: " << result 
             << "\t est: " << estimator
             << "\t res: " << residuum 
             << endl;

        if (estimator <= REQUIRED_ACCURACY)
            break;
        if (residuum <= REQUIRED_ACCURACY)
            break;
        
        x0 = result;
    }
    return result;
}

double secant_method(double (*f)(double), double x0, double x1) {
    double result;
    for (int i = 1; i <= MAX_ITERATIONS; i++){
        result = x1 - f(x1) / ((f(x1) - f(x0)) / (x1 - x0));

        double estimator = fabs(result - x0);
        double residuum  = fabs(f(result));

        cout << "Iteracja " << i 
             << ":\t Wartosc przyblizona: " << result 
             << "\t est: " << estimator
             << "\t res: " << residuum 
             << endl;

        if (estimator <= REQUIRED_ACCURACY)
            break;
        if (residuum  <= REQUIRED_ACCURACY)
            break;

        x0 = x1;
        x1 = result;
    }
    return result;
}

int main() {
    // 1.
    try {
        cout << "Metoda Picarda:" << endl;
        cout << "--------------------" << endl;
        picards_method(f1_picard, f1_picard_derivative, 0.2);
        cout << "--------------------" << endl;
    }
    catch (const char* ex) { cout << "Error: " << ex << endl; }

    try {
        cout << "Metoda bisekcji:" << endl;
        cout << "--------------------" << endl;
        bisection_method(f1, -0.1, 0.1);
        cout << "--------------------" << endl;
    }
    catch (const char* ex) { cout << "Error: " << ex << endl; }

    try {
        cout << "Metoda Newtona:" << endl;
        cout << "--------------------" << endl;
        newtons_method(f1, f1_derivative, 0.2);
        cout << "--------------------" << endl;
    }
    catch (const char* ex) { cout << "Error: " << ex << endl; }

    try {
        cout << "Metoda siecznych:" << endl;
        cout << "--------------------" << endl;
        secant_method(f1, -0.1, 0.1);
        cout << "--------------------" << endl;
    }
    catch (const char* ex) { cout << "Error: " << ex << endl; }

    // 2.
    try {
        cout << "Metoda Picarda:" << endl;
        cout << "--------------------" << endl;
        picards_method(f2_picard, f2_picard_derivative, 0.5);
        cout << "--------------------" << endl;
    }
    catch (const char* ex) { cout << "Error: " << ex << endl; }

    try {
        cout << "Metoda bisekcji:" << endl;
        cout << "--------------------" << endl;
        bisection_method(f2, 0.4, 0.5);
        cout << "--------------------" << endl;
    }
    catch (const char* ex) { cout << "Error: " << ex << endl; }

    try {
        cout << "Metoda Newtona:" << endl;
        cout << "--------------------" << endl;
        newtons_method(f2, f2_derivative, 0.5);
        cout << "--------------------" << endl;
    }
    catch (const char* ex) { cout << "Error: " << ex << endl; }

    try {
        cout << "Metoda siecznych:" << endl;
        cout << "--------------------" << endl;
        secant_method(f2, 0.4, 0.5);
        cout << "--------------------" << endl;
    }
    catch (const char* ex) { cout << "Error: " << ex << endl; }
}