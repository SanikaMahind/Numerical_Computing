#include <iostream>
#include <cmath>
#include <iomanip>
#include "RootFinding.hpp"

using namespace std;

// f(x) = 4x^3 - 3x
double RootFinding::func(double x)
{
    return 4 * x * x * x - 3 * x;
}

// f'(x) = 12x^2 - 3
double RootFinding::dfunc(double x)
{
    return 12 * x * x - 3;
}

// ---------------- Bisection ----------------
double Bisection::solve(double a, double b, double tol)
{
    if (func(a) * func(b) >= 0)
    {
        cout << "Bisection condition not satisfied\n";
        return NAN;
    }

    double c;
    int iter = 0;

    while ((b - a) >= tol)
    {
        c = (a + b) / 2;

        if (func(c) == 0.0)
            break;

        if (func(a) * func(c) < 0)
            b = c;
        else
            a = c;

        iter++;
    }

    cout << "Bisection iterations: " << iter << endl;
    return c;
}

// ---------------- Newton Raphson ----------------
double NewtonRaphson::solve(double x, double, double tol)
{
    int iter = 0;
    double x1;

    while (iter < 100)
    {
        if (dfunc(x) == 0)
        {
            cout << "Derivative zero. Stopping.\n";
            return NAN;
        }

        x1 = x - func(x) / dfunc(x);

        if (fabs(x1 - x) < tol)
            break;

        x = x1;
        iter++;
    }

    cout << "Newton iterations: " << iter << endl;
    return x1;
}

// ---------------- Fixed Point ----------------
// g(x) = cos(x)  (example transformation)
double FixedPoint::solve(double x, double, double tol)
{
    int iter = 0;
    double x1;

    while (iter < 100)
    {
        x1 = cos(x);

        if (fabs(x1 - x) < tol)
            break;

        x = x1;
        iter++;
    }

    cout << "Fixed Point iterations: " << iter << endl;
    return x1;
}
