#include "../include/LinearSystem.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>

// Default Constructor
// Initializes empty matrix and augmented matrix

LinearSystem::LinearSystem() : Matrix(), augmented(0, 0) {}


// Parameterized Constructor
// Creates:
// A → n x n matrix
// augmented → n x (n+1) matrix
// b → RHS vector of size n]


LinearSystem::LinearSystem(int n) : Matrix(n, n), augmented(n, n + 1)
{
    b.resize(n);   // RHS vector
}

// loadSystem()
// Reads system from file
// Format:
// rows cols
// A matrix values
// b vector values

void LinearSystem::loadSystem(const std::string &filename)
{
    std::ifstream fin(filename);

    // Error if file not opened
    if (!fin)
        throw std::runtime_error("Cannot open file: " + filename);

    // Read dimensions
    fin >> rows >> cols;

    // Resize matrix A
    data.resize(rows, std::vector<double>(cols));

    // Resize RHS vector
    b.resize(rows);

    // Read matrix A
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fin >> data[i][j];

    // Read vector b
    for (int i = 0; i < rows; i++)
        fin >> b[i];

    // -------------------------------------------------------
    // Build augmented matrix [A | b]
    // -------------------------------------------------------
    augmented = Matrix(rows, cols + 1);

    for (int i = 0; i < rows; i++)
    {
        // Copy A
        for (int j = 0; j < cols; j++)
            augmented(i, j) = data[i][j];

        // Add b as last column
        augmented(i, cols) = b[i];
    }

    fin.close();
}

// directSolve()
// Gaussian elimination with partial pivoting, returning solution vector
std::vector<double> LinearSystem::directSolve() const
{
    if (rows != cols)
        throw std::logic_error("Matrix must be square for direct solve");

    int n = rows;

    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    std::vector<double> tempB(n);

    for (int i = 0; i < n; i++)
    {
        tempB[i] = b[i];
        for (int j = 0; j < n; j++)
            A[i][j] = data[i][j];
    }

    // Forward elimination with partial pivoting
    for (int k = 0; k < n - 1; k++)
    {
        int pivotRow = k;
        for (int i = k + 1; i < n; i++)
            if (std::fabs(A[i][k]) > std::fabs(A[pivotRow][k]))
                pivotRow = i;

        if (std::fabs(A[pivotRow][k]) < 1e-12)
            throw std::runtime_error("Singular or near-singular matrix detected in directSolve");

        if (pivotRow != k)
        {
            std::swap(A[k], A[pivotRow]);
            std::swap(tempB[k], tempB[pivotRow]);
        }

        for (int i = k + 1; i < n; i++)
        {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < n; j++)
                A[i][j] -= factor * A[k][j];
            tempB[i] -= factor * tempB[k];
        }
    }

    if (std::fabs(A[n - 1][n - 1]) < 1e-12)
        throw std::runtime_error("Singular matrix: no unique solution in directSolve");

    std::vector<double> solution(n);
    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++)
            sum += A[i][j] * solution[j];
        solution[i] = (tempB[i] - sum) / A[i][i];
    }

    return solution;
}

// -----------------------------------------------------------
// loadFromMatrices()
// Takes A and B directly instead of file
// A must be square
// B must be column vector
// -----------------------------------------------------------
void LinearSystem::loadFromMatrices(const Matrix &A, const Matrix &B)
{
    int n = A.getRows();
    int c = A.getCols();

    // Check if A is square
    if (n != c)
        throw std::logic_error("Coefficient matrix A must be square");

    // Check if B is column vector
    if (B.getRows() != n || B.getCols() != 1)
        throw std::logic_error("RHS matrix B must be n x 1");

    rows = n;
    cols = c;

    // Copy A into data[][]
    data.resize(rows, std::vector<double>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            data[i][j] = A(i, j);

    // Copy B into vector b
    b.resize(rows);
    for (int i = 0; i < rows; i++)
        b[i] = B(i, 0);

    // Build augmented matrix [A | b]
    augmented = Matrix(rows, cols + 1);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            augmented(i, j) = data[i][j];

        augmented(i, cols) = b[i];
    }
}

// -----------------------------------------------------------
// printAugmented()
// Displays matrix like:
// a11 a12 | b1
// a21 a22 | b2
// -----------------------------------------------------------
void LinearSystem::printAugmented() const
{
    std::cout << "Augmented Matrix [A|b]:\n";

    for (int i = 0; i < rows; i++)
    {
        // Print A
        for (int j = 0; j < cols; j++)
            std::cout << augmented(i, j) << "\t";

        // Print b
        std::cout << "| " << augmented(i, cols);
        std::cout << "\n";
    }
}