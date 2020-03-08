#include <iostream>
#include <limits>

using namespace std;

int main()
{
    float floatEpsilon = 1;
    int floatMantissaBytes = 0;

    while (floatEpsilon / 2 + 1 > 1)
    {
        floatEpsilon /= 2;
        floatMantissaBytes++;
    }
    cout << endl;
    cout << "Dla zmiennych typu float: " << endl;
    cout << "--------------------------" << endl;
    cout << "Liczba bitow mantysy: " 
        << floatMantissaBytes << endl;
    cout << "Obliczona wartosc epsylona maszynowego: " 
        << floatEpsilon << endl;
    cout << "Wartosc epsylona maszynowego z biblioteki limits: " 
        << numeric_limits<float>::epsilon() << endl << endl;

    double doubleEpsilon = 1;
    int doubleMantissaBytes = 0;

    while (doubleEpsilon / 2 + 1 > 1)
    {
        doubleEpsilon /= 2;
        doubleMantissaBytes++;
    }
    
    cout << endl;
    cout << "Dla zmiennych typu double: " << endl;
    cout << "--------------------------" << endl;
    cout << "Liczba bitow mantysy: " 
        << doubleMantissaBytes << endl;
    cout << "Obliczona wartosc epsylona maszynowego: " 
        << doubleEpsilon << endl;
    cout << "Wartosc epsylona maszynowego z biblioteki limits: " 
        << numeric_limits<double>::epsilon() << endl << endl;
}