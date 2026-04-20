#include "../include/doolittle.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

void Doolittle::solve()
{
    int n = rows;

    Matrix L(n, n);
    Matrix U(n, n);

    // ---- Doolittle LU Decomposition ----
    for (int i = 0; i < n; i++)
    {
        // Upper triangular U
        for (int k = i; k < n; k++)
        {
            double sum = 0;
            for (int j = 0; j < i; j++)
                sum += L(i, j) * U(j, k);
            U(i, k) = data[i][k] - sum;
        }

        // Lower triangular L
        for (int k = i; k < n; k++)
        {
            if (i == k)
                L(i, i) = 1.0;  // Diagonal of L is 1 in Doolittle
            else
            {
                double sum = 0;
                for (int j = 0; j < i; j++)
                    sum += L(k, j) * U(j, i);
                L(k, i) = (data[k][i] - sum) / U(i, i);
            }
        }
    }

    // Forward substitution: L*y = b
    std::vector<double> y = forwardSubstitution(L, b);

    // Backward substitution: U*x = y
    std::vector<double> x = backwardSubstitution(U, y);

    // Print to console
    printSolutionToConsole("Doolittle LU", x);

    // Save to file
    saveSolutionToFile(x);

    std::cout << "Vector saved  --> resultvector.txt\n";
}
