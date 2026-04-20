#include "../include/cholesky.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <fstream>

void Cholesky::solve()
{
    int n = rows;

    Matrix L(n, n);

    // ---- Cholesky Decomposition (A = L * L^T) ----
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            double sum = 0;

            for (int k = 0; k < j; k++)
                sum += L(i, k) * L(j, k);

            if (i == j)
            {
                double value = data[i][i] - sum;

                if (value <= 0)
                    throw std::runtime_error("Matrix is not positive definite");

                L(i, j) = std::sqrt(value);
            }
            else
            {
                L(i, j) = (data[i][j] - sum) / L(j, j);
            }
        }
    }

    // Solve L*y = b
    std::vector<double> y = forwardSubstitution(L, b);

    // Solve L^T * x = y
    Matrix LT = L.transpose();
    std::vector<double> x = backwardSubstitution(LT, y);

    // Print to console
    printSolutionToConsole("Cholesky", x);

    // Save to file
    saveSolutionToFile(x);

    std::cout << "Vector saved  --> resultvector.txt\n";
}
