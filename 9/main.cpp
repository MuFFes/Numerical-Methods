#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

#define P 1.0
#define Q 0.0
#define R -4.0

#define ALPHA 0.0
#define BETA 1.0
#define GAMMA -1.0
#define PHI 0.0
#define PSI 1.0
#define THETA 0.0

#define START_X 0.0
#define END_X 1.0

using namespace std;

double analytic(double x) {
    return ((exp(2.0 - 2.0 * x) - 4.0 * exp(4.0 - 2.0 * x) + 4.0 * exp(2.0 * x) - exp(2.0 + 2.0 * x) - x + x * exp(4.0)) / (4.0 - 4.0 * exp(4.0)));
}

void thomas(double *d, double *u, double *l, int n) {
	for (int i = 1; i < n; i++)
		d[i] -= ((l[i - 1] / d[i - 1]) * u[i - 1]);
}

void solve(double *d, double *u, double *l, double *b, double *x, int n) {
	for (int i = 1; i < n; i++)
		b[i] = b[i] - ((l[i - 1] / d[i - 1]) * b[i - 1]);

	x[n - 1] = b[n - 1] / d[n - 1];

	for (int i = n - 2; i >= 0; i--)
		x[i] = (b[i] - u[i] * x[i + 1]) / d[i];
}

double maximum_error(double *err, int n) {
	double max = 0.0;

	for (int i = 0; i < n; i++)
		if (fabs(err[i]) > max)
			max = fabs(err[i]);

	return max;
}

double tripoint_conventional_discretization(double h, int n) {
	double x1 = START_X;
    double x2 = START_X;
    double s  = START_X;

	double* d   = new double[n];
	double* u   = new double[n];
	double* l   = new double[n];
	double* b   = new double[n];
	double* x   = new double[n];
	double* err = new double[n];

	u[0] = ALPHA / h;
	d[0] = BETA - ALPHA / h;
	b[0] = -GAMMA;

	for (int i = 1; i < n - 1; i++) {
		l[i - 1] = P / (h * h) - Q / (2.0 * h);
		u[i] = P / (h * h) + Q / (2.0 * h);
		d[i] = R + -2.0 * P / (h * h);
		b[i] = (s + h * i);
	}

	l[n - 2] = -PHI / h;
	d[n - 1] = PHI / h + PSI;
	b[n - 1] = -THETA;

	thomas(d, u, l, n);
	solve(d, u, l, b, x, n);

	for (int i = 0; i < n; i++, x1 += h)
		err[i] = fabs(x[i] - analytic(x1));

	if (n == 50) {
        fstream file;
	    file.precision(10);
		file.open("out_conventional.txt", fstream::out);

		cout << "------------------------------" << endl;
		     << "Trzypunktowa dyskretyzacja konwencjonalna" << endl;
		     << "------------------------------" << endl;

		cout << setw(5) << "i"
		     << setw(15) << "punkt"
		     << setw(15) << "x[n]"
		     << setw(15) << "U(x)" << endl;

		for (int i = 0; i < n; i++, x2 += h) {
			err[i] = fabs(x[i] - analytic(x2));

			file << x2 << " " 
                 << x[i] << " " 
                 << analytic(x2) << " " << endl;

            cout << setw(5) << i
                 << setw(15) << x2
                 << setw(15) << x[i]
                 << setw(15) << analytic(x2) << endl;
		}
		file.close();
	}

	delete[] d;
	delete[] u;
	delete[] l;
	delete[] b;
	delete[] x;

    double max_err = maximum_error(err, n);
	delete[] err;
	return max_err;
}

double numerov_discretization(double h, int n) {
	double x1 = START_X;
    double x2 = START_X;
    double s  = START_X;

	double* d   = new double[n];
	double* u   = new double[n];
	double* l   = new double[n];
	double* b   = new double[n];
	double* x   = new double[n];
	double* err = new double[n];

	u[0] = ALPHA / h;
	d[0] = BETA - ALPHA / h;
	b[0] = -GAMMA;

	for (int i = 1; i < n - 1; i++) {
		l[i - 1] = P / (h * h) + R / (12.0);
		d[i] = (-2.0 * P) / (h * h) + R * (10.0 / 12.0);
		u[i] = P / (h * h) + R / 12.0;
		b[i] = (s + i * h - h) / 12.0 + (10.0 / 12.0) * (s + i * h) + (s + i * h + h) / 12.0;
	}

	l[n - 2] = -PHI / h;
	d[n - 1] = PHI / h + PSI;
	b[n - 1] = -THETA;

	thomas(d, u, l, n);
	solve(d, u, l, b, x, n);

	for (int i = 0; i < n; i++, x1 += h)
		err[i] = fabs(x[i] - analytic(x1));

	if (n == 50) {
        fstream file;
	    file.precision(10);
		file.open("out_numerow.txt", fstream::out);

		cout << "------------------------------" << endl;
             << "Dyskretyzacja Numerowa"         << endl;
		     << "------------------------------" << endl;

		cout << setw(5)  << "i"
		     << setw(15) << "punkt"
		     << setw(15) << "x[n]"
		     << setw(15) << "U(x)" << endl;

		for (int i = 0; i < n; i++, x2 += h) {
			err[i] = fabs(x[i] - analytic(x2));

			file << x2 << " " 
                 << x[i] << " " 
                 << analytic(x2) << " " << endl;

			cout << setw(5) << i
			     << setw(15) << x2
			     << setw(15) << x[i]
			     << setw(15) << analytic(x2) << endl;
		}
		file.close();
	}

	delete[] u;
	delete[] d;
	delete[] l;
	delete[] b;
	delete[] x;
    
    double max_err = maximum_error(err, n);
	delete[] err;
	return max_err;
}

int main() {
	fstream file;
	file.open("out_errors.txt", fstream::out);
    file.precision(10);

	for (int i = 10; i < 50000; i += 40) {
		double h = (END_X - START_X) / (i - 1);
		file << log10(h) << " " 
             << log10(tripoint_conventional_discretization(h, i)) << " " 
             << log10(numerov_discretization(h, i)) << endl;
	}
	file.close();
	return 0;
}
