#include "include/gaussian.hpp"
#include "include/doolittle.hpp"
#include "include/crout.hpp"
#include "include/cholesky.hpp"
#include <iostream>

using namespace std;

int main()
{
    int choice;
    string filename;

    cout << "\n1. Gaussian Elimination\n";
    cout << "2. Doolittle LU\n";
    cout << "3. Crout LU\n";
    cout << "4. Cholesky\n";
    cout << "Choice: ";
    cin >> choice;

    cout << "Enter input file name: ";
    cin >> filename;

    LinearSystem* solver = nullptr;

    if(choice == 1)
        solver = new GaussianElimination();
    else if(choice == 2)
        solver = new Doolittle();
    else if(choice == 3)
        solver = new Crout();
    else if(choice == 4)
        solver = new Cholesky();
    else
    {
        cout << "Invalid choice\n";
        return 1;
    }

    try
    {
        solver->loadSystem(filename);

        cout << "\n----- Matrix Properties -----\n";

        cout << "Square = " << (solver->isSquare() ? "YES" : "NO") << endl;
        cout << "Symmetric = " << (solver->isSymmetric() ? "YES" : "NO") << endl;
        cout << "Identity = " << (solver->isIdentity() ? "YES" : "NO") << endl;
        cout << "Null = " << (solver->isNull() ? "YES" : "NO") << endl;
        cout << "Diagonal = " << (solver->isDiagonal() ? "YES" : "NO") << endl;
        cout << "Diagonally Dominant = "
             << (solver->isDiagonallyDominant() ? "YES" : "NO") << endl;

        cout << "\n----- Matrix Operations -----\n";

        cout << "\nTranspose:\n";
        cout << solver->transpose();

        if(solver->isSquare())
        {
            cout << "\nDeterminant = " << solver->determinant() << endl;
        }

        cout << "\n----- Solving System -----\n";

        solver->solve();

        cout << "\nSolution generated successfully\n";
    }
    catch(const exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    delete solver;

    return 0;
}