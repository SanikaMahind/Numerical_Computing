#include <iostream>
#include <cmath>
#include "RootFinding.hpp"

using namespace std;

int main()
{
    cout << "Bisection Method for f(x) = 4x^3 - 3x\n";

    double a = 0.5;
    double b = 1.0;
    double tol = 0.0001;

    // Create object of class
    RootFinding obj;

    double root = obj.bisection(a, b, tol);

    if (!isnan(root))
        cout << "Approximate Root: " << root << endl;

    return 0;
}
