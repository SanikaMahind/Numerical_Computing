#include <iostream>
#include <cmath>
#include <iomanip>
#include "RootFinding.hpp"

using namespace std;

// Function definition using class name
double RootFinding::func(double x)
{
    return 4 * x * x * x - 3 * x;
}

// Bisection method inside class
double RootFinding::bisection(double a, double b, double tol)
{
    if (func(a) * func(b) >= 0)
    {
        cout << "Bisection condition not satisfied.\n";
        return NAN;
    }

    cout << "\nIter"
         << setw(12) << "a"
         << setw(12) << "b"
         << setw(12) << "c"
         << setw(15) << "f(c)" << "\n";

    cout << "-----------------------------------------------------------------\n";

    double c;
    int iter = 1;

    while ((b - a) >= tol)
    {
        c = (a + b) / 2;

        cout << setw(4) << iter
             << setw(12) << a
             << setw(12) << b
             << setw(12) << c
             << setw(15) << func(c) << "\n";

        if (func(c) == 0.0)
            break;

        if (func(a) * func(c) < 0)
            b = c;
        else
            a = c;

        iter++;
    }

    cout << "\nNumber of iterations: " << iter - 1 << endl;

    return c;
}
