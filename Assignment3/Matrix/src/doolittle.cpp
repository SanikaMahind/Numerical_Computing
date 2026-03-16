#include "../include/doolittle.hpp"
#include <iostream>
#include <fstream>
#include <vector>

void Doolittle::solve()
{
    int n = rows;

    Matrix L(n,n);
    Matrix U(n,n);

    // LU decomposition (Doolittle)
    for(int i = 0; i < n; i++)
    {
        // Upper triangular
        for(int k = i; k < n; k++)
        {
            double sum = 0;

            for(int j = 0; j < i; j++)
                sum += L(i,j) * U(j,k);

            U(i,k) = data[i][k] - sum;
        }

        // Lower triangular
        for(int k = i; k < n; k++)
        {
            if(i == k)
                L(i,i) = 1;
            else
            {
                double sum = 0;

                for(int j = 0; j < i; j++)
                    sum += L(k,j) * U(j,i);

                L(k,i) = (data[k][i] - sum) / U(i,i);
            }
        }
    }

    // Forward substitution: L*y = b
    std::vector<double> y = forwardSubstitution(L, b);

    // Backward substitution: U*x = y
    std::vector<double> x = backwardSubstitution(U, y);

    std::ofstream vectorFile("resultvector.txt");

    if(!vectorFile)
        throw std::runtime_error("Cannot create resultvector.txt");

    vectorFile << "# X Y\n";

    for(int i = 0; i < n; i++)
        vectorFile << i+1 << " " << x[i] << std::endl;

    std::cout << "Solution saved in resultvector.txt\n";
}