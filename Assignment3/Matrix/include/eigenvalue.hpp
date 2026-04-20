#ifndef EIGENVALUE_HPP
#define EIGENVALUE_HPP

#include "matrix.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

// =========================================================
//  Class Hierarchy:
//
//  Matrix
//   └── EigenValue          <-- this file
//         └── Gerschgorin   <-- gerschgorin.hpp
//
//  EigenValue is the BASE class for all eigenvalue methods.
//  It inherits Matrix so it has access to matrix data.
//
//  It provides:
//   - loadMatrix()        : load matrix from file
//   - printMatrix()       : display matrix (small only)
//   - saveResultsToFile() : write results to output file
//   - virtual analyze()   : pure virtual — child classes implement
// =========================================================

class EigenValue : public Matrix
{
public:
    EigenValue();
    EigenValue(int n);
    virtual ~EigenValue() = default;

    // Load square matrix from file
    void loadMatrix(const std::string &filename);

    // Load from an already-constructed Matrix object
    void loadFromMatrix(const Matrix &m);

    // Display matrix on terminal (small matrices only)
    void printMatrix() const;

    // Pure virtual — each child implements its own analysis
    // Results must be saved to file, NOT printed to terminal
    virtual void analyze() = 0;

protected:
    // Helper: save results to output file
    // Each child calls this with its computed results
    void saveResultsToFile(const std::string &filename,
                           const std::string &methodName,
                           const std::string &content) const;

    // Helper: write a single line to terminal (progress only)
    void printProgress(const std::string &msg) const;
};

#endif
