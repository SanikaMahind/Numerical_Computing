#include "lagrange.hpp"   
#include <iostream>       
#include <fstream>        

using namespace std;

// Solve function implementing Lagrange Interpolation
void Lagrange::solve()
{
    int n = x.size();   // Number of data points

    // Open output file
    ofstream fout("lagrange_result.txt");

    // Check if file opened properly
    if (!fout)
        throw runtime_error("Cannot open output file");

    double result = 0;   // Final interpolated value

    fout << "----- Lagrange Interpolation -----\n\n";

    // Loop for each basis polynomial L_i
    for (int i = 0; i < n; i++)
    {
        double Li = 1;   // Initialize L_i = 1

        fout << "L" << i << " = ";

        // Compute product for L_i
        for (int j = 0; j < n; j++)
        {
            if (i != j)   // Skip when i == j
            {
                // Print formula part
                fout << "(x - " << x[j] << ")/(" 
                     << x[i] << " - " << x[j] << ") ";

                // Compute L_i(value)
                Li *= (value - x[j]) / (x[i] - x[j]);
            }
        }

        fout << "\n";

        // Add contribution of this term to final result
        result += Li * fx[i];
    }

    // Print final interpolated value
    fout << "\nP(" << value << ") = " << result << "\n";

    fout.close();   // Close file

    // Message on terminal
    cout << "\nLagrange Interpolation Result saved to lagrange_result.txt\n";
}