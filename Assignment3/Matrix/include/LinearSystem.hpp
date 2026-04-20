#ifndef LINEARSYSTEM_HPP
#define LINEARSYSTEM_HPP

#include "matrix.hpp"
#include <vector>
#include <string>

class LinearSystem : public Matrix
{
protected:
    std::vector<double> b;      // RHS vector
    Matrix augmented;           // augmented matrix [A|b]

public:
    LinearSystem();
    LinearSystem(int n);
    virtual ~LinearSystem() = default;   // virtual destructor — avoids UB when deleting via base pointer

    // Load system from file (reads A matrix + b vector)
    void loadSystem(const std::string &filename);

    // Load system from two matrices: A (coefficient) and B (RHS column vector)
    // Builds the augmented matrix [A|b] internally
    void loadFromMatrices(const Matrix &A, const Matrix &B);

    // Display augmented matrix
    void printAugmented() const;

    // Direct solver used for safe fallbacks in iterative methods
    std::vector<double> directSolve() const;

    // Virtual solve function (pure virtual — must be overridden)
    virtual void solve() = 0;
};

#endif
