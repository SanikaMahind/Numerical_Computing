#include "../include/LinearSystem.hpp"
#include <fstream>
#include <iostream>

LinearSystem::LinearSystem() : Matrix() {}

LinearSystem::LinearSystem(int n) : Matrix(n,n), augmented(n,n+1)
{
    b.resize(n);
}

void LinearSystem::loadSystem(const std::string &filename)
{
    std::ifstream fin(filename);

    if(!fin)
        throw std::runtime_error("Cannot open file");

    fin >> rows >> cols;

    data.resize(rows, std::vector<double>(cols));
    b.resize(rows);

    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            fin >> data[i][j];

    for(int i=0;i<rows;i++)
        fin >> b[i];

    // build augmented matrix
    augmented = Matrix(rows, cols+1);

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
            augmented(i,j) = data[i][j];

        augmented(i,cols) = b[i];
    }

    fin.close();
}

void LinearSystem::printAugmented() const
{
    std::cout << "Augmented Matrix:\n";

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols+1;j++)
            std::cout << augmented(i,j) << " ";

        std::cout << std::endl;
    }
}