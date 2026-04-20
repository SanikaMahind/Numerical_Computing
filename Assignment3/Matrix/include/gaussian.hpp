#ifndef GAUSSIAN_HPP
#define GAUSSIAN_HPP

#include "LinearSystem.hpp"
#include <vector>
#include <fstream>

class GaussianElimination : public LinearSystem
{
public:
    GaussianElimination() = default;

    // Override virtual function from LinearSystem
    void solve() override;

private:
    void saveSolutionToFile(const std::vector<double> &solution);
    void printSolutionToConsole(const std::vector<double> &solution);
};

#endif
