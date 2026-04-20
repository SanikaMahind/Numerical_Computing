#ifndef GERSCHGORIN_HPP
#define GERSCHGORIN_HPP

#include "eigenvalue.hpp"
#include <vector>
#include <string>

// =========================================================
//  Gerschgorin Circle Theorem
//
//  For each row i of matrix A:
//    Center c_i = A[i][i]              (diagonal element)
//    Radius r_i = SUM |A[i][j]|, j!=i  (sum of off-diagonal absolutes)
//
//  Every eigenvalue λ of A lies in at least one disc:
//    |λ - c_i| <= r_i
//    => eigenvalue is in range [c_i - r_i , c_i + r_i]
//
//  Output (saved to file):
//    - Table of all discs (row, center, radius, lower bound, upper bound)
//    - Union bound: overall [min_lower, max_upper]
//    - Spectral radius estimate: max(|center| + radius)
// =========================================================

struct GerschgorinDisc
{
    int    row;      // row index (1-based)
    double center;   // diagonal element A[i][i]
    double radius;   // sum of |off-diagonal| in row i
    double lower;    // center - radius
    double upper;    // center + radius
};

class Gerschgorin : public EigenValue
{
public:
    Gerschgorin() = default;
    explicit Gerschgorin(int n);
    virtual ~Gerschgorin() = default;

    // Compute Gerschgorin discs and save results to file
    void analyze() override;

    // Get computed discs (after analyze() is called)
    const std::vector<GerschgorinDisc> &getDiscs() const { return discs; }

    // Get overall eigenvalue bounds (after analyze())
    double getOverallLower()    const { return overallLower; }
    double getOverallUpper()    const { return overallUpper; }
    double getSpectralRadius()  const { return spectralRadius; }

private:
    std::vector<GerschgorinDisc> discs;

    double overallLower    = 0.0;
    double overallUpper    = 0.0;
    double spectralRadius  = 0.0;

    // Build discs from current matrix data
    void computeDiscs();

    // Format result table as string for file output
    std::string buildResultString() const;
};

#endif
