#ifndef LU_HPP
#define LU_HPP

#include "LinearSystem.hpp"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>

class LU : public LinearSystem
{
protected:
    std::vector<double> forwardSubstitution(const Matrix &L,
                                            const std::vector<double> &b);

    std::vector<double> backwardSubstitution(const Matrix &U,
                                             const std::vector<double> &y);

    // Print solution to console — consistent output pattern across all solvers
    void printSolutionToConsole(const std::string &methodName,
                                const std::vector<double> &solution);

    // Save solution to resultvector.txt
    void saveSolutionToFile(const std::vector<double> &solution);
};

#endif
