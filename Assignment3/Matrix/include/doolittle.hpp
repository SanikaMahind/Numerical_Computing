#ifndef DOOLITTLE_HPP
#define DOOLITTLE_HPP

#include "LU.hpp"

class Doolittle : public LU
{
public:
    Doolittle() = default;

    void solve() override;
};

#endif