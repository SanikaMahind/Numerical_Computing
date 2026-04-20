#ifndef CHOLESKY_HPP
#define CHOLESKY_HPP

#include "LU.hpp"

class Cholesky : public LU
{
public:
    Cholesky() = default;

    void solve() override;
};

#endif
