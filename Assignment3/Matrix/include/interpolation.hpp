#ifndef INTERPOLATION_HPP
#define INTERPOLATION_HPP

#include "matrix.hpp"
#include <vector>
#include <string>

class Interpolation : public Matrix
{
protected:
    std::vector<double> x;   // x values
    std::vector<double> fx;  // f(x) values
    double value;            // value at which interpolation is needed

public:
    Interpolation();

    // Load data from file
    void loadData(const std::string &filename);

    // Virtual solve
    virtual void solve() = 0;

    virtual ~Interpolation() {}
};

#endif