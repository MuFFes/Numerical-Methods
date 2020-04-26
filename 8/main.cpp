#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

#define STEP 0.1
#define STEPS 20

using namespace std;

template <typename T>
T func(T x) { return sin(x); }

template <typename T>
T derivative(T x) { return cos(x); }

template <typename T>
T forward_2point_difference (T x, T h) { return (func(x + h) - func(x)) / h; }

template <typename T>
T backward_2point_difference(T x, T h) { return (func(x) - func(x - h)) / h; }

template <typename T>
T central_2point_difference (T x, T h) { return (func(x + h) - func(x - h)) / (T(2) * h); }

template <typename T>
T forward_3point_difference (T x, T h) { return (T(-1.5) * func(x) + T(2) * func(x + h) - T(0.5) * func(x + h * T(2))) / h; }

template <typename T>
T backward_3point_difference(T x, T h) { return (T(0.5) * func(x - h * T(2)) - T(2) * sin(x - h) + T(1.5) * sin(x)) / h; }

template <typename T>
void calculate_differences(T steps[STEPS], T results[7][STEPS]) {
	T start_x = T(0);
	T center_x = M_PI_4;
	T end_x = M_PI_2;
	T step = STEP;

	for (int i = 0; i < STEPS; i++) {
		steps[i] = step;

		results[0][i] = fabs(derivative(start_x)  - forward_2point_difference (start_x,  step));
		results[1][i] = fabs(derivative(start_x)  - forward_3point_difference (start_x,  step));
		results[2][i] = fabs(derivative(center_x) - forward_2point_difference (center_x, step));
		results[3][i] = fabs(derivative(center_x) - central_2point_difference (center_x, step));
		results[4][i] = fabs(derivative(center_x) - backward_2point_difference(center_x, step));
		results[5][i] = fabs(derivative(end_x)    - backward_2point_difference(end_x,    step));
		results[6][i] = fabs(derivative(end_x)    - backward_3point_difference(end_x,    step));

		step *= STEP;
	}
}

template <typename T>
void save_results(T steps[STEPS], T results[7][STEPS]) {
	fstream file;
	string filename = "out_" + string(typeid(T).name()) + ".txt";

	file.open(filename.c_str(), fstream::out);

	for (int j = 0; j < STEPS; j++) {
		file << log10(steps[j]) << " ";

		for (int i = 0; i < 7; i++) {
			file << log10(results[i][j]) << " ";
		}

		file << endl;
	}
	file.close();
}

int main() {
	float float_steps[STEPS];
	float float_results[7][STEPS];

	double double_steps[STEPS];
	double double_results[7][STEPS];

	calculate_differences(float_steps, float_results);
	calculate_differences(double_steps, double_results);

	save_results(float_steps, float_results);
	save_results(double_steps, double_results);

	return 0;
}
