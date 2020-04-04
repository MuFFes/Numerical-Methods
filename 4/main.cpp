#include <iostream>
#include <math.h>
#include <algorithm>

#define MAX_ITERATIONS 100
#define REQUIRED_ACCURACY 2.22045e-16

using namespace std;

double f1(double x, double y, double z) {
    return x * x + y * y + z * z - 2.0;
}

double f2(double x, double y) {
    return x * x + y * y - 1.0;
}

double f3(double x, double y) {
    return x * x - y;
}

int main() {
    double x = 1.0;
    double y = 0.5;
    double z = 1.0;

    auto delta    = new double[3];
    auto values   = new double[3];
    auto matrix   = new double[3][3]; 

    values[0] = f1(x, y, z);
    values[1] = f2(x, y);
    values[2] = f3(x, y);

    for (int i = 1; i <= MAX_ITERATIONS; i++) {
        if (x == 0 || z == 0){
            cout << "Nie mozna wykonac dzielenia przez 0" << endl ;
            return 1;
        }

		matrix[0][0] =  0;
		matrix[0][1] = -2 * z;
		matrix[0][2] = -4 * y * z;
		matrix[1][0] =  0;
		matrix[1][1] = -4 * x * z;
		matrix[1][2] =  4 * x * z;
		matrix[2][0] = -2 * x - 4 * x * y;
		matrix[2][1] =  2 * x + 4 * x * y;
		matrix[2][2] =  0;

        if (((-4 * x * z) - (8 * x * y * z)) == 0){
            cout << "Macierz jest osobliwa";
            return 1;
        }

        double reversed_determinant = 1 / ((-4 * x * z) - (8 * x * y * z));

        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                matrix[i][j] *= reversed_determinant;
            }
        }

        for (int j = 0; j < 3; j++){
            delta[j] = 0;
            for (int k = 0; k < 3; k++){
                delta[j] += matrix[j][k] * values[k];
            }
        }

        x = x - delta[0];
        y = y - delta[1];
        z = z - delta[2];

        values[0] = f1(x, y, z);
		values[1] = f2(x, y);
		values[2] = f3(x, y);

		double estimator = max(max(fabs(delta[0]),  fabs(delta[1])),  fabs(delta[2]));
		double residuum  = max(max(fabs(values[0]), fabs(values[1])), fabs(values[2]));

        cout << "Iteracja " << i 
             << "\t x: "    << x 
             << "\t y: "    << y 
             << "\t z: "    << z 
             << "\t est: "  << estimator
             << "\t res: "  << residuum << endl;

		if (fabs(residuum) < REQUIRED_ACCURACY) 
            break;
		if (fabs(estimator) < REQUIRED_ACCURACY) 
            break;
    }
}