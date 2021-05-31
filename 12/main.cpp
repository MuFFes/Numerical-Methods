#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>

using namespace std;

const int N = 10000;
const int DATA_POINTS = 60;
const double MIN_X  = -1.0;
const double MAX_X  =  1.0;
const double STEP   = (MAX_X - MIN_X) / (N - 1);
const double DATA_POINT_STEP = (MAX_X - MIN_X) / (DATA_POINTS - 1);

double analytic(double x) {
	return 1.0 / (1.0 + 10.0 * x * x * x * x * x * x);
}

double lagrange(double x, double *xi, double *yi) {
	double term[DATA_POINTS];
	double result = 0.0;

	for (int i = 0; i < DATA_POINTS; i++) {
		term[i] = 1.0;
		for (int j = 0; j < DATA_POINTS; j++)
			if (j != i)
				term[i] *= (x - xi[j]) / (xi[i] - xi[j]);
		result += yi[i] * term[i];
	}
	return result;
}

double chebyshev(double x) {
	double xi[DATA_POINTS];
	double yi[DATA_POINTS];

	for (int i = 0; i < DATA_POINTS; i++) {
		double ksi = cos(((2.0 * i + 1.0) * M_PI) / (2.0 * DATA_POINTS));
		xi[i] = ((MAX_X + MIN_X) / 2) + ((MAX_X - MIN_X) / 2) * ksi;
		yi[i] = analytic(xi[i]);
	}
	return lagrange(x, xi, yi);
}

double equispaced(double x) {
	double xi[DATA_POINTS];
	double yi[DATA_POINTS];

	for (int i = 0; i < DATA_POINTS; i++) {
		xi[i] = MIN_X + i * DATA_POINT_STEP;
		yi[i] = analytic(xi[i]);
	}
	return lagrange(x, xi, yi);
}

int main() {
	fstream dane;
	dane.open("out.txt", fstream::out);

	double x = MIN_X;
	for (int i = 0; i < N; i++, x += STEP)
		dane << setw(12) << x
			 << setw(12) << analytic(x)
			 << setw(12) << chebyshev(x)
			 << setw(12) << equispaced(x) << endl;

	dane.close();
	return 0;
}