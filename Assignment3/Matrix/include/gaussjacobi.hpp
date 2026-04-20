#ifndef GAUSSJACOBI_HPP
#define GAUSSJACOBI_HPP

#include "iterative.hpp"


// Formula:
//   x_i^(k+1) = ( b_i - SUM_{j != i} a_ij * x_j^(k) ) / a_ii
//
// Key property: uses ONLY values from the PREVIOUS iteration (k).

class GaussJacobi : public IterativeMethod
{
public:
    // maxIter: max iterations (default 1000)
    // tol    : convergence tolerance (default 1e-6)
    GaussJacobi(int maxIter = 1000, double tol = 1e-6);

    void solve() override;
};

#endif
