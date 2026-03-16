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

    // load system from file
    void loadSystem(const std::string &filename);

    // display augmented matrix
    void printAugmented() const;

    // virtual solve function
    virtual void solve() = 0;
};

#endif