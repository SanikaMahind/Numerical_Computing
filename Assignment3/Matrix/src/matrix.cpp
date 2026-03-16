#include "../include/matrix.hpp"
#include <cmath>       
#include <stdexcept>   


Matrix::Matrix() : rows(0), cols(0) {}             // Default constructor: creates an empty matrix with 0 rows and co
Matrix::Matrix(int r, int c) : rows(r), cols(c)    // Parameterized constructor: creates a matrix with r rows and c columns, all initialized to 0

{
    data.resize(rows, std::vector<double>(cols, 0));        // resize 2D vector
}


Matrix::Matrix(const Matrix &m)                         // Copy constructor: creates a deep copy of another matrix
{
    rows = m.rows;
    cols = m.cols;
    data = m.data;
}


// Read matrix from a file: first row=rows, second=cols, then matrix elements

void Matrix::readFromFile(std::ifstream &fin)
{
    fin >> rows >> cols;
    data.resize(rows, std::vector<double>(cols));  // resize vector to new dimensions
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fin >> data[i][j];                     // read each element
}

// Write matrix to a file
void Matrix::displayToFile(std::ofstream &fout) const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            fout << data[i][j] << " ";    // write each element separated by space
        fout << "\n";                      // new line for each row
    }
}



// Access or modify element at (i,j)
double &Matrix::operator()(int i, int j) { return data[i][j]; }

// Access element at (i,j) for read-only operations
double Matrix::operator()(int i, int j) const { return data[i][j]; }


// Matrix addition: element-wise
Matrix Matrix::operator+(const Matrix &m) const
{
    Matrix result(rows, cols);                   // create result matrix
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result(i,j) = data[i][j] + m(i,j);  // sum corresponding elements
    return result;
}

// Matrix subtraction: element-wise
Matrix Matrix::operator-(const Matrix &m) const
{
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result(i,j) = data[i][j] - m(i,j);
    return result;
}

// Matrix multiplication (rows x cols * cols x m.cols)
Matrix Matrix::operator*(const Matrix &m) const
{
    Matrix result(rows, m.cols);           // result has same rows as this and columns as m
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < m.cols; j++)
            for (int k = 0; k < cols; k++)
                result(i,j) += data[i][k] * m(k,j);  // dot product of row i with column j
    return result;
}



// Check if two matrices are equal (same size + same elements(compaire))
bool Matrix::operator==(const Matrix &m) const
{
    if (rows != m.rows || cols != m.cols) return false;  // size mismatch
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (data[i][j] != m(i,j)) return false;    // element mismatch
    return true;
}



// Read matrix from standard input or file stream
std::istream &operator>>(std::istream &in, Matrix &m)
{
    in >> m.rows >> m.cols;
    m.data.resize(m.rows, std::vector<double>(m.cols));
    for (int i = 0; i < m.rows; i++)
        for (int j = 0; j < m.cols; j++)
            in >> m(i,j);
    return in;
}

// Write matrix to standard output or file stream
std::ostream &operator<<(std::ostream &out, const Matrix &m)
{
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.cols; j++)
            out << m(i,j) << " ";
        out << "\n";
    }
    return out;
}



// Check if matrix is square
bool Matrix::isSquare() const { return rows == cols; }

// Check if all elements are zero
bool Matrix::isNull() const
{
    for (auto &r : data)
        for (auto &v : r)
            if (v != 0) return false;
    return true;
}

// Check if matrix is diagonal (all non-diagonal elements are zero)
bool Matrix::isDiagonal() const
{
    if (!isSquare()) return false;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (i != j && data[i][j] != 0) return false;
    return true;
}

// Check if matrix is identity (diagonal=1, rest=0)
bool Matrix::isIdentity() const
{
    if (!isSquare()) return false;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            if (i == j && data[i][j] != 1) return false;
            if (i != j && data[i][j] != 0) return false;
        }
    return true;
}

// Check if matrix is symmetric (A == A^T)
bool Matrix::isSymmetric() const
{
    if (!isSquare()) return false;
    for (int i = 0; i < rows; i++)
        for (int j = i+1; j < cols; j++)
            if (data[i][j] != data[j][i]) return false;
    return true;
}

// Check if matrix is diagonally dominant
bool Matrix::isDiagonallyDominant() const
{
    if (!isSquare()) return false;
    for (int i = 0; i < rows; i++)
    {
        double sum = 0;
        for (int j = 0; j < cols; j++)
            if (i != j) sum += std::abs(data[i][j]);  // sum of non-diagonal elements in row
        if (std::abs(data[i][i]) < sum) return false;  // diagonal element must be >= sum
    }
    return true;
}

// Return transpose of matrix
Matrix Matrix::transpose() const
{
    Matrix t(cols, rows);  // swap rows and cols
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            t(j,i) = data[i][j];  // swap indices
    return t;
}

// Check if this matrix is the transpose of another
bool Matrix::isTranspose(const Matrix &m) const
{
    return transpose() == m;
}



double Matrix::determinant() const       // Recursive determinant calculation (Laplace expansion)
{
    if (!isSquare()) throw std::runtime_error("Determinant only for square matrix");
    if (rows == 1) return data[0][0];
    if (rows == 2) return data[0][0]*data[1][1] - data[0][1]*data[1][0];

    double det = 0;
    for (int p = 0; p < cols; p++)
    {
        Matrix sub(rows-1, cols-1);
        for (int i = 1; i < rows; i++)
        {
            int colIndex = 0;
            for (int j = 0; j < cols; j++)
            {
                if (j == p) continue;               // skip current column
                sub(i-1,colIndex) = data[i][j];    // copy remaining elements to submatrix
                colIndex++;
            }
        }
        det += pow(-1, p) * data[0][p] * sub.determinant();  // recursive Laplace expansion
    }
    return det;
}