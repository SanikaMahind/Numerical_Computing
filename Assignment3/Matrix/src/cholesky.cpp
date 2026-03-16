#include "../include/cholesky.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <fstream>

void Cholesky::solve()
{
    int n = rows;

    Matrix L(n,n);

    // Cholesky decomposition
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            double sum = 0;

            for(int k = 0; k < j; k++)
                sum += L(i,k) * L(j,k);

            if(i == j)
            {
                double value = data[i][i] - sum;

                if(value <= 0)
                    throw std::runtime_error("Matrix not positive definite");

                L(i,j) = sqrt(value);
            }
            else
            {
                L(i,j) = (data[i][j] - sum) / L(j,j);
            }
        }
    }

    // Solve L*y = b
    std::vector<double> y = forwardSubstitution(L, b);

    // Compute transpose of L
    Matrix LT = L.transpose();

    // Solve L^T * x = y
    std::vector<double> x = backwardSubstitution(LT, y);

    std::ofstream vectorFile("resultvector.txt");

    if(!vectorFile)
        throw std::runtime_error("Cannot create resultvector.txt");

    vectorFile << "# X Y\n";

    for(int i = 0; i < n; i++)
        vectorFile << i+1 << " " << x[i] << std::endl;

    std::cout << "Solution saved in resultvector.txt\n";
}