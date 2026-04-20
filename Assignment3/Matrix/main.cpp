#include "gaussian.hpp"
#include "doolittle.hpp"
#include "crout.hpp"
#include "cholesky.hpp"
#include "gaussjacobi.hpp"
#include "gaussseidel.hpp"
#include "gerschgorin.hpp"
#include "lagrange.hpp"

#include <iostream>
#include <string>
#include <filesystem>

using namespace std;

int main()
{
    int choice;

    cout << "\n========================================\n";
    cout << "        Numerical Methods Solver\n";
    cout << "========================================\n";

    cout << "  --- Direct Methods ---\n";
    cout << "  1. Gaussian Elimination\n";
    cout << "  2. Doolittle  (LU)\n";
    cout << "  3. Crout      (LU)\n";
    cout << "  4. Cholesky   (LU)\n";

    cout << "\n  --- Iterative Methods ---\n";
    cout << "  5. Gauss-Jacobi\n";
    cout << "  6. Gauss-Seidel\n";

    cout << "\n  --- Eigenvalue Methods ---\n";
    cout << "  7. Gerschgorin Circle Theorem\n";

    cout << "\n  --- Interpolation Methods ---\n";
    cout << "  8. Lagrange Interpolation\n";

    cout << "========================================\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice < 1 || choice > 8)
    {
        cout << "Invalid choice.\n";
        return 1;
    }

    // ==============================
    // 🔷 GERSCHGORIN
    // ==============================
    if (choice == 7)
    {
        int fmt;
        cout << "\nFile input format:\n";
        cout << "  1. Matrix file only\n";
        cout << "  2. Two files (A + b, A used)\n";
        cout << "Choice: ";
        cin >> fmt;

        Gerschgorin g;

        try
        {
            if (fmt == 1)
            {
                string file;
                cin >> file;
                g.loadMatrix(file);
            }
            else if (fmt == 2)
            {
                string fileA, fileB;
                cin >> fileA >> fileB;
                g.loadMatrix(fileA);
            }
            else
            {
                cout << "Invalid format\n";
                return 1;
            }

            g.analyze();
            cout << "\nGerschgorin result saved.\n";
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << "\n";
        }

        return 0;
    }

    // ==============================
    // 🔷 LAGRANGE
    // ==============================
    if (choice == 8)
    {
        Lagrange lag;

        try
        {
            string file;
            cout << "Enter input file: ";
            cin >> file;

            lag.loadData(file);
            lag.solve();

            cout << "\nLagrange result saved in lagrange_result.txt\n";
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << "\n";
        }

        return 0;
    }

    // ==============================
    // 🔷 LINEAR SYSTEM
    // ==============================
    LinearSystem* solver = nullptr;

    if      (choice == 1) solver = new GaussianElimination();
    else if (choice == 2) solver = new Doolittle();
    else if (choice == 3) solver = new Crout();
    else if (choice == 4) solver = new Cholesky();
    else if (choice == 5) solver = new GaussJacobi();
    else if (choice == 6) solver = new GaussSeidel();

    try
    {
        int fmt;
        cout << "\nFile input format:\n";
        cout << "  1. Two files (A and b)\n";
        cout << "  2. One file (A|b)\n";
        cout << "Choice: ";
        cin >> fmt;

        if (fmt == 1)
        {
            string fileA, fileB;
            cin >> fileA >> fileB;

            ifstream finA(fileA), finB(fileB);
            if (!finA || !finB)
                throw runtime_error("File error");

            int r, c;
            finA >> r >> c;

            Matrix A(r, c);
            for (int i = 0; i < r; i++)
                for (int j = 0; j < c; j++)
                    finA >> A(i, j);

            int br, bc;
            finB >> br >> bc;

            Matrix B(br, bc);
            for (int i = 0; i < br; i++)
                for (int j = 0; j < bc; j++)
                    finB >> B(i, j);

            solver->loadFromMatrices(A, B);
        }
        else
        {
            string file;
            cin >> file;

            ifstream fin(file);
            if (!fin)
                throw runtime_error("File error");

            int n, m;
            fin >> n >> m;

            Matrix A(n, n), B(n, 1);

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                    fin >> A(i, j);
                fin >> B(i, 0);
            }

            solver->loadFromMatrices(A, B);
        }

        solver->solve();

        cout << "\nSolution completed. Check output files.\n";
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << "\n";
    }

    delete solver;
    return 0;
}