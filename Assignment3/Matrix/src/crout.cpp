#include "../include/crout.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>

void Crout::solve()
{
    int n = rows;

    Matrix L(n,n);
    Matrix U(n,n);

    // Crout decomposition
    for(int j = 0; j < n; j++)
    {
        U(j,j) = 1;

        for(int i = j; i < n; i++)
        {
            double sum = 0;

            for(int k = 0; k < j; k++)
                sum += L(i,k) * U(k,j);

            L(i,j) = data[i][j] - sum;
        }

        for(int i = j+1; i < n; i++)
        {
            double sum = 0;

            for(int k = 0; k < j; k++)
                sum += L(j,k) * U(k,i);

            U(j,i) = (data[j][i] - sum) / L(j,j);
        }
    }

    // Forward substitution  L*y = b
    std::vector<double> y = forwardSubstitution(L, b);

    // Backward substitution U*x = y
    std::vector<double> x = backwardSubstitution(U, y);

    std::ofstream vectorFile("resultvector.txt");

    if(!vectorFile)
        throw std::runtime_error("Cannot create resultvector.txt");

    vectorFile << "# X Y\n";

    for(int i = 0; i < n; i++)
        vectorFile << i+1 << " " << x[i] << std::endl;

    std::cout << "Solution saved in resultvector.txt\n";
}