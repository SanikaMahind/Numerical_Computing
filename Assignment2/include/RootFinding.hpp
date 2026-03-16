#ifndef ROOTFINDING_HPP
#define ROOTFINDING_HPP

class RootFinding
{
public:
    virtual double solve(double a, double b, double tol) = 0;

    double func(double x);
    double dfunc(double x);
};

class Bisection : public RootFinding
{
public:
    double solve(double a, double b, double tol);
};

class NewtonRaphson : public RootFinding
{
public:
    double solve(double a, double b, double tol);
};

class FixedPoint : public RootFinding
{
public:
    double solve(double a, double b, double tol);
};

#endif
