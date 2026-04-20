#include "../include/gaussian.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <fstream>

void GaussianElimination::solve()
{
    if (rows != cols)
        throw std::logic_error("Matrix must be square for Gaussian Elimination");

    int n = rows;

    // Work on copies so original data is not modified
    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    std::vector<double> tempB(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            A[i][j] = data[i][j];
        tempB[i] = b[i];
    }

    // ---- Forward Elimination with Partial Pivoting ----
    for (int k = 0; k < n - 1; k++)
    {
        // Find pivot row (max absolute value in column k)
        int pivotRow = k;
        for (int i = k + 1; i < n; i++)
            if (std::fabs(A[i][k]) > std::fabs(A[pivotRow][k]))
                pivotRow = i;

        if (std::fabs(A[pivotRow][k]) < 1e-12)
            throw std::runtime_error("Singular or near-singular matrix detected");

        // Swap rows in A and tempB
        if (pivotRow != k)
        {
            std::swap(A[k], A[pivotRow]);
            std::swap(tempB[k], tempB[pivotRow]);
        }

        // Eliminate entries below pivot
        for (int i = k + 1; i < n; i++)
        {
            double factor = A[i][k] / A[k][k];

            for (int j = k; j < n; j++)
                A[i][j] -= factor * A[k][j];

            tempB[i] -= factor * tempB[k];
        }
    }

    // Check last pivot
    if (std::fabs(A[n-1][n-1]) < 1e-12)
        throw std::runtime_error("Singular matrix: no unique solution");

    // ---- Back Substitution ----
    std::vector<double> solution(n, 0.0);

    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++)
            sum += A[i][j] * solution[j];

        solution[i] = (tempB[i] - sum) / A[i][i];
    }

    // ---- Print solution to console ----
    printSolutionToConsole(solution);

    // ---- Save results to files ----
    saveSolutionToFile(solution);

    // ---- Save upper triangular matrix ----
    std::ofstream matrixFile("resultmatrix.txt");
    if (!matrixFile)
        throw std::runtime_error("Error creating resultmatrix.txt");

    matrixFile << "Upper Triangular Matrix (After Gaussian Elimination):\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            matrixFile << std::setw(12) << std::fixed << std::setprecision(6) << A[i][j];
        matrixFile << "\n";
    }
    matrixFile.close();

    // ---- Update gnuplot script ----
    std::ofstream plot("plot.gnu");
    plot << "set title 'Gaussian Elimination Solution'\n";
    plot << "set xlabel 'Variable Index'\n";
    plot << "set ylabel 'Value'\n";
    plot << "set grid\n";
    plot << "set style data linespoints\n";
    plot << "plot 'resultvector.txt' using 1:2 with linespoints title 'Solution'\n";
    plot << "pause -1\n";
    plot.close();

    std::cout << "\nMatrix saved  --> resultmatrix.txt\n";
    std::cout << "Vector saved  --> resultvector.txt\n";
    std::cout << "Gnuplot file  --> plot.gnu  (run: gnuplot plot.gnu)\n";
}

void GaussianElimination::printSolutionToConsole(const std::vector<double> &solution)
{
    std::cout << "\n---------- Gaussian Elimination Solution ----------\n";
    for (int i = 0; i < (int)solution.size(); i++)
        std::cout << "  x[" << i + 1 << "] = " << std::fixed << std::setprecision(6) << solution[i] << "\n";
    std::cout << "---------------------------------------------------\n";
}

void GaussianElimination::saveSolutionToFile(const std::vector<double> &solution)
{
    std::ofstream vectorFile("resultvector.txt");

    if (!vectorFile)
        throw std::runtime_error("Error creating resultvector.txt");

    vectorFile << "# Index  Value\n";
    for (int i = 0; i < (int)solution.size(); i++)
        vectorFile << i + 1 << "  " << std::fixed << std::setprecision(6) << solution[i] << "\n";

    vectorFile.close();
}
