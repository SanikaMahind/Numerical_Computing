#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>


class Matrix
{
protected:
    int rows, cols;                                 // Number of rows and columns
    std::vector<std::vector<double>> data;          // 2D vector to store matrix elements

public:
    
    Matrix();                                       // Default constructor: creates an empty matrix (0x0)
    Matrix(int rows, int cols);                     // Parameterized constructor: creates a rows x cols matrix initialized with 0
    Matrix(const Matrix &m);                        // Copy constructor: creates a deep copy of another matrix


    void readFromFile(std::ifstream &fin);              // Reads matrix dimensions and data from a file
    void displayToFile(std::ofstream &fout) const;   // Writes matrix data to a file


    int getRows() const { return rows; }               // Returns number of rows
    int getCols() const { return cols; }              // Returns number of columns


    //  Element access 
    double &operator()(int i, int j);               // Access/modify element at row i, column j
    double operator()(int i, int j) const;          // Access element at row i, column j (read-only)

    
    Matrix operator+(const Matrix &m) const;           // Matrix addition
    Matrix operator-(const Matrix &m) const;           // Matrix subtraction
    Matrix operator*(const Matrix &m) const;         // Matrix multiplication

    
    bool operator==(const Matrix &m) const;          // Checks if two matrices are equal(compaire)

    // Stream operators 
    friend std::istream &operator>>(std::istream &in, Matrix &m);   // Read matrix from input stream
    friend std::ostream &operator<<(std::ostream &out, const Matrix &m); // Print matrix to output stream

    
    bool isSquare() const;                       // Checks if matrix is square (rows == cols)
    bool isSymmetric() const;                    // Checks if matrix is symmetric (A == A^T)
    bool isIdentity() const;                     // Checks if matrix is identity matrix
    bool isNull() const;                         // Checks if all elements are zero
    bool isDiagonal() const;                     // Checks if matrix is diagonal
    bool isDiagonallyDominant() const;          // Checks if matrix is diagonally dominant
    bool isTranspose(const Matrix &m) const;    // Checks if current matrix is the transpose of another

    // Utility functions 
    bool makeDiagonallyDominant();               // Rearrange rows to make diagonally dominant (returns false if impossible)
    Matrix transpose() const;                    // Returns the transpose of the matrix
    double determinant() const;                  // Computes determinant (recursive for n>2)
};

#endif
