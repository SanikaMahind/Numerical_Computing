#ifndef LAGRANGE_HPP
#define LAGRANGE_HPP

#include "interpolation.hpp"

class Lagrange : public Interpolation
{
public:
    void solve() override;
};

#endif