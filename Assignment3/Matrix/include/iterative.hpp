#ifndef ITERATIVE_HPP
#define ITERATIVE_HPP

#include "LinearSystem.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <algorithm>


class IterativeMethod : public LinearSystem
{
protected:
    int    maxIterations;
    double tolerance;

    // Check diagonal dominance; rearrange rows if needed.
    // Called at the start of each child's solve().
    void checkAndFixDominance();

    // Print iteration table header  (Iter | x[1]  x[2] ...)
    void printIterationHeader() const;

    
    
    // Save solution to resultvector.txt
    void saveSolutionToFile(const std::vector<double> &solution) const;

    // Save augmented matrix [A|b] to resultmatrix.txt
    void saveMatrixToFile() const;

    
    
public:
    IterativeMethod(int maxIter = 1000, double tol = 1e-6);
    virtual ~IterativeMethod() = default;

    // Pure virtual — each child (GaussJacobi / GaussSeidel) implements its own scheme
    virtual void solve() override = 0;
};

#endif
