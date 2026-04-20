#include "interpolation.hpp"   
#include <fstream>             
#include <stdexcept>         

using namespace std;

// Constructor → initialize value to 0
Interpolation::Interpolation() : value(0) {}

// Function to load data from input file
void Interpolation::loadData(const string &filename)
{
    ifstream fin(filename);  

    // Check if file opened successfully
    if (!fin)
        throw runtime_error("Cannot open file: " + filename);

    int n;
    fin >> n;         // Read number of data points

    // Resize vectors according to n
    x.resize(n);    // x values
    fx.resize(n);   // f(x) values

    // Read x values from file
    for (int i = 0; i < n; i++)
        fin >> x[i];

    // Read corresponding f(x) values
    for (int i = 0; i < n; i++)
        fin >> fx[i];

    // Read the value at which interpolation is required
    fin >> value;

    fin.close();   
}