#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

#define N 1000

using namespace std;

double analytic(double t) {
    return 1.0 - exp(-10.0 * (t + atan(t)));
}

double explicit_eulers_method_error(double h) {
    double error = 0.0;
    double t = h;
    double y = 0.0;
    double exact_value;

    for (int i = 0; i < N; i++) {
        exact_value = analytic(t);
        y += h * (-((10.0 * t * t + 20.0) / (t * t + 1.0)) * (y - 1.0));
        exact_value = fabs(exact_value - y);
        if (exact_value > error)
            error = exact_value;
        t += h;
    }
    return error;
}

double implicit_eulers_method_error(double h) {
    double error = 0.0;
    double t = h;
    double y = 0.0;
    double exact_value;
    double value;

    for (int i = 0; i < N; i++) {
        exact_value = analytic(t);
        value = (10.0 * (t + h) * (t + h) + 20.0) / ((t + h) * (t + h) + 1.0);
        y = (y + h * value) / (1 + h * value);
        exact_value = fabs(exact_value - y);
        if (exact_value > error)
            error = exact_value;
        t += h;
    }
    return error;
}

double trapezoidal_method_error(double h) {
    double error = 0.0;
    double t = h;
    double y = 0.0;
    double exact_value;
    double point1;
    double point2;

    for (int i = 0; i < N; i++) {
        exact_value = analytic(t);
        point1 = ((10.0 * t * t + 20.0) / (t * t + 1.0));
        point2 = (10.0 * (t + h) * (t + h) + 20.0) / ((t + h) * (t + h) + 1.0);
        y = ((-h / 2.0) * (point1 * (y - 1.0) - point2) + y) / (1.0 + (h / 2.0) * point2);
        exact_value = fabs(exact_value - y);
        if (exact_value > error)
            error = exact_value;
        t += h;
    }
    return error;
}

double explicit_eulers_method_value(double h, double tmax) {
    double y = 0.0;

    for (double t = 0.0; t < tmax; t += h)
        y += h * (-((10.0 * t * t + 20.0) / (t * t + 1.0)) * (y - 1.0));

    return y;
}

double implicit_eulers_method_value(double h, double tmax) {
    double y = 0.0;
    double value;

    for (double t = 0.0; t < tmax; t += h) {
        value = (10.0 * (t + h) * (t + h) + 20.0) / ((t + h) * (t + h) + 1.0);
        y = (y + h * value) / (1 + h * value);
    }
    return y;
}

double trapezoidal_method_value(double h, double tmax) {
    double y = 0.0;
    double point1;
    double point2;

    for (double t = 0.0; t < tmax; t += h) {
        point1 = ((10.0 * t * t + 20.0) / (t * t + 1.0));
        point2 = (10.0 * (t + h) * (t + h) + 20.0) / ((t + h) * (t + h) + 1.0);
        y = ((-h / 2.0) * (point1 * (y - 1.0) - point2) + y) / (1.0 + (h / 2.0) * point2);
    }
    return y;
}

int main() {
    fstream file;
    file.open("errors.txt", fstream::out);

    for (double step = 0.1; step > 1e-20; step /= 2)
        file << setw(12) << log10(step)
             << setw(12) << log10(implicit_eulers_method_error(step))
             << setw(12) << log10(explicit_eulers_method_error(step))
             << setw(12) << log10(trapezoidal_method_error(step)) << endl;

    file.close();
    file.open("out.txt", fstream::out);
    
    double step = 0.01;

    for (double t = 0.0; t < 5.0; t += step)
        file << setw(4) << t
             << setw(12) << analytic(t)
             << setw(12) << implicit_eulers_method_value(step, t)
             << setw(12) << explicit_eulers_method_value(step, t)
             << setw(12) << trapezoidal_method_value(step, t) << endl;

    file.close();
    file.open("out_unstable.txt", fstream::out );

	for (double t = 0.0; t < 5.0; t += 0.15)
		file << t << " " << explicit_eulers_method_value(0.15, t ) << endl;

	file.close( );

    return 0;
}