#include "myComplex.h"
#include <cmath>

myComplex::myComplex()
{
    a = 0;
    b = 0;
}


myComplex::myComplex(float x, float y)
{
    a = x;
    b = y;
}


myComplex myComplex::add(myComplex c)
{
    myComplex ans;
    ans.a = a + c.a;
    ans.b = b + c.b;
    return ans;
}


myComplex myComplex::multiply(myComplex c)
{
    myComplex ans;
    ans.a = (a * c.a) - (b * c.b);
    ans.b = (a * c.b) + (b * c.a);
    return ans;
}


myComplex myComplex::divide(myComplex c)
{
    myComplex ans;
    float den = (c.a * c.a) + (c.b * c.b);

    ans.a = (a * c.a + b * c.b) / den;
    ans.b = (b * c.a - a * c.b) / den;

    return ans;
}


myComplex myComplex::conjugate()
{
    myComplex ans;
    ans.a = a;
    ans.b = -b;
    return ans;
}

// (modulus)
float myComplex::norm()
{
    return sqrt(a * a + b * b);
}

void myComplex::display()
{
    cout << a;
    if (b >= 0)
        cout << " + " << b << "i";
    else
        cout << " - " << -b << "i";
}
