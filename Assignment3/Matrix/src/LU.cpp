#include "../include/LU.hpp"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>

// Forward Substitution — Solves Ly = b for y (L is lower triangular)
std::vector<double> LU::forwardSubstitution(const Matrix &L,
                                            const std::vector<double> &b)
{
    int n = L.getRows();
    std::vector<double> y(n);

    for (int i = 0; i < n; i++)
    {
        y[i] = b[i];

        for (int j = 0; j < i; j++)
            y[i] -= L(i, j) * y[j];

        y[i] /= L(i, i);
    }

    return y;
}

// Backward Substitution — Solves Ux = y for x (U is upper triangular)
std::vector<double> LU::backwardSubstitution(const Matrix &U,
                                             const std::vector<double> &y)
{
    int n = U.getRows();
    std::vector<double> x(n);

    for (int i = n - 1; i >= 0; i--)
    {
        x[i] = y[i];

        for (int j = i + 1; j < n; j++)
            x[i] -= U(i, j) * x[j];

        x[i] /= U(i, i);
    }

    return x;
}

// Print solution to console — consistent format for all LU methods
void LU::printSolutionToConsole(const std::string &methodName,
                                const std::vector<double> &solution)
{
    std::cout << "\n---------- " << methodName << " Solution ----------\n";
    for (int i = 0; i < (int)solution.size(); i++)
        std::cout << "  x[" << i + 1 << "] = "
                  << std::fixed << std::setprecision(6) << solution[i] << "\n";
    std::cout << std::string(40 + methodName.size(), '-') << "\n";
}

// Save solution to resultvector.txt
void LU::saveSolutionToFile(const std::vector<double> &solution)
{
    std::ofstream vectorFile("resultvector.txt");

    if (!vectorFile)
        throw std::runtime_error("Cannot create resultvector.txt");

    vectorFile << "# Index  Value\n";
    for (int i = 0; i < (int)solution.size(); i++)
        vectorFile << i + 1 << "  "
                   << std::fixed << std::setprecision(6) << solution[i] << "\n";

    vectorFile.close();
}
