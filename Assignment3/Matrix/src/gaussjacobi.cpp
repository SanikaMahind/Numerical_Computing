#include "../include/gaussjacobi.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>


// Constructor
GaussJacobi::GaussJacobi(int maxIter, double tol)
    : IterativeMethod(maxIter, tol)
{}

// -----------------------------------------------------------
// solve()
// Steps:
// 1. Check diagonal dominance
// 2. Perform Jacobi iterations
// 3. If fails → fallback to direct solve
// 4. Print + save results
// -----------------------------------------------------------
void GaussJacobi::solve()
{
    // Matrix must be square
    if (rows != cols)
        throw std::logic_error("Matrix must be square for Gauss-Jacobi");

    // ---- Step 1: Check dominance ----
    checkAndFixDominance();

    int n = rows;

    // Initial guess
    std::vector<double> x(n, 0.0);

    // New values stored separately (IMPORTANT difference)
    std::vector<double> xNew(n, 0.0);

    std::cout << "\n===== Gauss-Jacobi Iterations =====\n";
    printIterationHeader();

    int iter = 0;
    bool converged = false;

    // ---- Step 2: Iteration loop ----
    for (iter = 0; iter < maxIterations; iter++)
    {
        // Compute new values using OLD x
        for (int i = 0; i < n; i++)
        {
            double sigma = 0.0;

            for (int j = 0; j < n; j++)
            {
                if (j != i)
                    sigma += data[i][j] * x[j];   // OLD values
            }

            xNew[i] = (b[i] - sigma) / data[i][i];
        }

        // ---- Print iteration ----
        std::cout << std::setw(6) << iter + 1 << "  |";
        for (int i = 0; i < n; i++)
            std::cout << std::setw(14)
                      << std::fixed << std::setprecision(6)
                      << xNew[i];
        std::cout << "\n";

        // ---- Convergence check ----
        double maxDiff = 0.0;

        for (int i = 0; i < n; i++)
            maxDiff = std::max(maxDiff, std::fabs(xNew[i] - x[i]));

        // Update x
        x = xNew;

        // ---- Divergence check ----
        if (!std::isfinite(maxDiff))
        {
            std::cout << "\n  WARNING: Iterates diverged (non-finite value) after "
                      << iter + 1 << " iterations.\n";
            break;
        }

        // ---- Stop if converged ----
        if (maxDiff < tolerance)
        {
            std::cout << "\n  Converged after " << iter + 1
                      << " iterations (max change = " << maxDiff << ")\n";
            converged = true;
            iter++;
            break;
        }
    }

    // ---- If not converged → fallback ----
    if (!converged)
    {
        std::cout << "\n  WARNING: Did not converge after "
                  << maxIterations << " iterations.\n";
        std::cout << "  Falling back to direct solve.\n";

        x = directSolve();
    }

    // ---- Step 3: Output ----
    

    saveSolutionToFile(x);
    saveMatrixToFile();
    

    std::cout << "Matrix saved  --> resultmatrix.txt\n";
    std::cout << "Vector saved  --> resultvector.txt\n";
    std::cout << "Gnuplot file  --> plot.gnu (run: gnuplot plot.gnu)\n";
}