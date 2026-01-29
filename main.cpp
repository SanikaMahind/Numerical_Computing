#include <iostream>
#include "myComplex.h"
using namespace std;

int main()
{
    float r1, i1, r2, i2;

    cout << "Enter real part and imaginary part of first complex number: ";
    cin >> r1 >> i1;

    cout << "Enter real part and imaginary part of second complex number: ";
    cin >> r2 >> i2;

    myComplex c1(r1, i1);
    myComplex c2(r2, i2);
    myComplex c3;

    cout << "\nC1 = ";
    c1.display();

    cout << "\nC2 = ";
    c2.display();

    c3 = c1.add(c2);
    cout << "\n\nAddition = ";
    c3.display();

    c3 = c1.multiply(c2);
    cout << "\nMultiplication = ";
    c3.display();

    c3 = c1.divide(c2);
    cout << "\nDivision = ";
    c3.display();

    c3 = c1.conjugate();
    cout << "\nConjugate of first complex number = ";
    c3.display();

    cout << "\nNorm of first complex number = " << c1.norm() << endl;

    return 0;
}
