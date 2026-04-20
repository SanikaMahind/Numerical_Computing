#ifndef CROUT_HPP
#define CROUT_HPP

#include "LU.hpp"

class Crout : public LU
{
public:
    Crout() = default;

    void solve() override;
};

#endif
