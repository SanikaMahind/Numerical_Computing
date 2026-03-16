#ifndef LU_HPP
#define LU_HPP

#include "LinearSystem.hpp"
#include <vector>

class LU : public LinearSystem
{
protected:
    std::vector<double> forwardSubstitution(const Matrix &L,
                                            const std::vector<double> &b);

    std::vector<double> backwardSubstitution(const Matrix &U,
                                             const std::vector<double> &y);
};

#endif