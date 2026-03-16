#include "../include/gaussian.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <fstream>

void GaussianElimination::solve()
{
    if (rows != cols)
        throw std::logic_error("Matrix must be square");

    Matrix A = *this;
    std::vector<double> tempB = b;

    std::ofstream matrixFile("resultmatrix.txt");
    std::ofstream vectorFile("resultvector.txt");

    if (!matrixFile || !vectorFile)
        throw std::runtime_error("Error creating output files");

    matrixFile << "Coefficient Matrix (After Elimination):\n";

    // Forward Elimination
    for (int k = 0; k < rows - 1; k++)
    {
        int pivotRow = k;

        for (int i = k + 1; i < rows; i++)
        {
            if (std::fabs(A(i,k)) > std::fabs(A(pivotRow,k)))
                pivotRow = i;
        }

        if (std::fabs(A(pivotRow,k)) < 1e-12)
            throw std::runtime_error("Singular Matrix");

        if (pivotRow != k)
        {
            for (int j = 0; j < cols; j++)
                std::swap(A(k,j), A(pivotRow,j));

            std::swap(tempB[k], tempB[pivotRow]);
        }

        for (int i = k + 1; i < rows; i++)
        {
            double factor = A(i,k) / A(k,k);

            for (int j = k; j < cols; j++)
                A(i,j) -= factor * A(k,j);

            tempB[i] -= factor * tempB[k];
        }
    }

    // Save matrix
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            matrixFile << A(i,j) << " ";

        matrixFile << "\n";
    }

    // Back Substitution
    std::vector<double> solution(rows);

    for (int i = rows - 1; i >= 0; i--)
    {
        solution[i] = tempB[i];

        for (int j = i + 1; j < rows; j++)
            solution[i] -= A(i,j) * solution[j];

        solution[i] /= A(i,i);
    }

    vectorFile << "# X Y\n";

    for (int i = 0; i < rows; i++)
        vectorFile << i + 1 << " " << solution[i] << "\n";

    std::ofstream plot("plot.gnu");

    plot << "set title 'Gaussian Elimination Solution'\n";
    plot << "set xlabel 'Index'\n";
    plot << "set ylabel 'Value'\n";
    plot << "set grid\n";
    plot << "plot 'resultvector.txt' using 1:2 with linespoints\n";
    plot << "pause -1\n";

    std::cout << "\nMatrix saved in resultmatrix.txt\n";
    std::cout << "Vector saved in resultvector.txt\n";
    std::cout << "Run: gnuplot plot.gnu\n";
}