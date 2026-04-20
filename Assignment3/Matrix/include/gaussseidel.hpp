#ifndef GAUSSSEIDEL_HPP
#define GAUSSSEIDEL_HPP

#include "iterative.hpp"


// Formula:
//   x_i^(k+1) = ( b_i - SUM_{j<i} a_ij * x_j^(k+1) - SUM_{j>i} a_ij * x_j^(k) ) / a_ii
//
// Key property: uses the MOST RECENTLY updated values within the same iteration.
// This makes it converge faster than Gauss-Jacobi.

class GaussSeidel : public IterativeMethod
{
public:
    // maxIter: max iterations (default 1000)
    // tol    : convergence tolerance (default 1e-6)
    GaussSeidel(int maxIter = 1000, double tol = 1e-6);

    void solve() override;
};

#endif
