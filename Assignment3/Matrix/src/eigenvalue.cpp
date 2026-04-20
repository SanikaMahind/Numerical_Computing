#include "../include/eigenvalue.hpp"
#include <fstream>
#include <stdexcept>

// Default constructor
EigenValue::EigenValue() : Matrix() {}

// Constructor with size
EigenValue::EigenValue(int n) : Matrix(n, n) {}

// Load square matrix from file
// File format: first line = "rows cols", then matrix elements
void EigenValue::loadMatrix(const std::string &filename)
{
    std::ifstream fin(filename);
    if (!fin)
        throw std::runtime_error("Cannot open file: " + filename);

    fin >> rows >> cols;

    if (rows != cols)
        throw std::logic_error("Gerschgorin requires a SQUARE matrix");

    data.assign(rows, std::vector<double>(cols, 0.0));

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fin >> data[i][j];

    fin.close();
    std::cout << "Matrix loaded: " << rows << " x " << cols << "\n";
}

// Load from an already-constructed Matrix object (e.g. from LinearSystem)
void EigenValue::loadFromMatrix(const Matrix &m)
{
    rows = m.getRows();
    cols = m.getCols();

    if (rows != cols)
        throw std::logic_error("Gerschgorin requires a SQUARE matrix");

    data.assign(rows, std::vector<double>(cols, 0.0));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            data[i][j] = m(i, j);
}

// Print matrix to terminal — only for small matrices
void EigenValue::printMatrix() const
{
    if (rows > 10)
    {
        std::cout << "(Matrix too large to display: "
                  << rows << "x" << cols << ")\n";
        return;
    }

    std::cout << "\nMatrix (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            std::cout << std::setw(10) << std::fixed
                      << std::setprecision(4) << data[i][j];
        std::cout << "\n";
    }
}

// Save analysis results to output file
void EigenValue::saveResultsToFile(const std::string &filename,
                                   const std::string &methodName,
                                   const std::string &content) const
{
    std::ofstream fout(filename);
    if (!fout)
        throw std::runtime_error("Cannot create file: " + filename);

    fout << "========================================\n";
    fout << "  " << methodName << " Results\n";
    fout << "  Matrix size: " << rows << " x " << cols << "\n";
    fout << "========================================\n\n";
    fout << content;
    fout.close();
}

// Print a short progress message to terminal
void EigenValue::printProgress(const std::string &msg) const
{
    std::cout << msg << "\n";
}
