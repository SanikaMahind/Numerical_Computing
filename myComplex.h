#ifndef MYCOMPLEX_H
#define MYCOMPLEX_H

#include <iostream>
using namespace std;

class myComplex
{
public:
    float a, b;   // a = real part, b = imaginary part

    myComplex();                       // default constructor
    myComplex(float x, float y);       // parameterized constructor

    myComplex add(myComplex);
    myComplex multiply(myComplex);
    myComplex divide(myComplex);
    myComplex conjugate();
    float norm();

    void display();
};

#endif
