#include "../include/gaussseidel.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

// -----------------------------------------------------------
// Constructor
// Initializes max iterations and tolerance using base class
// -----------------------------------------------------------
GaussSeidel::GaussSeidel(int maxIter, double tol)
    : IterativeMethod(maxIter, tol)
{}

// -----------------------------------------------------------
// solve()
// Steps:
// 1. Check / fix diagonal dominance
// 2. Perform Gauss-Seidel iterations
// 3. If not converged → fallback to direct solve
// 4. Print + save results
// -----------------------------------------------------------
void GaussSeidel::solve()
{
    // Matrix must be square
    if (rows != cols)
        throw std::logic_error("Matrix must be square for Gauss-Seidel");

    // ---- Step 1: Check diagonal dominance ----
    checkAndFixDominance();

    int n = rows;

    // Initial guess (all zeros)
    std::vector<double> x(n, 0.0);

    std::cout << "\n===== Gauss-Seidel Iterations =====\n";
    printIterationHeader();

    int iter = 0;
    bool converged = false;

    // ---- Step 2: Iteration loop ----
    for (iter = 0; iter < maxIterations; iter++)
    {
        // Store previous values (for convergence check)
        std::vector<double> xOld = x;

        // ---------------------------------------------------
        // Core Gauss-Seidel logic
        // Updates values immediately
        // ---------------------------------------------------
        for (int i = 0; i < n; i++)
        {
            double sigma = 0.0;

            for (int j = 0; j < n; j++)
            {
                if (j != i)
                    // Uses updated x[j] for j < i
                    sigma += data[i][j] * x[j];
            }

            // Update current variable
            x[i] = (b[i] - sigma) / data[i][i];
        }

        // ---- Print iteration ----
        std::cout << std::setw(6) << iter + 1 << "  |";
        for (int i = 0; i < n; i++)
            std::cout << std::setw(14)
                      << std::fixed << std::setprecision(6)
                      << x[i];
        std::cout << "\n";

        // ---- Convergence check ----
        double maxDiff = 0.0;

        for (int i = 0; i < n; i++)
            maxDiff = std::max(maxDiff, std::fabs(x[i] - xOld[i]));

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

        x = directSolve();   // Direct method (Gaussian/LU etc.)
    }

    // ---- Step 3: Output ----
   

    saveSolutionToFile(x);     // saves vector
    saveMatrixToFile();        // saves matrix
    

    std::cout << "Matrix saved  --> resultmatrix.txt\n";
    std::cout << "Vector saved  --> resultvector.txt\n";
    std::cout << "Gnuplot file  --> plot.gnu (run: gnuplot plot.gnu)\n";
}