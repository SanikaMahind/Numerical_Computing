#include <iostream>
#include <cmath>
#include "RootFinding.hpp"

using namespace std;

int main()
{
    double a = 0.5;
    double b = 1.0;
    double tol = 0.0001;

    // Bisection
    cout << "\n--- Bisection Method ---\n";
    Bisection bisection;
    double root1 = bisection.solve(a, b, tol);
    cout << "Root: " << root1 << endl;

    // Newton Raphson
    cout << "\n--- Newton Raphson Method ---\n";
    NewtonRaphson newton;
    double root2 = newton.solve(1.0, 0, tol);   // start from 1
    cout << "Root: " << root2 << endl;

    // Fixed Point
    cout << "\n--- Fixed Point Method ---\n";
    FixedPoint fp;
    double root3 = fp.solve(0.5, 0, tol);
    cout << "Root: " << root3 << endl;

    return 0;
}
