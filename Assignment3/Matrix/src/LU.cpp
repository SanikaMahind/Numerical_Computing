#include "../include/LU.hpp"
#include <vector>


// Forward Substitution
// Solves Ly = b for y, where L is a lower triangular matrix

std::vector<double> LU::forwardSubstitution(const Matrix &L,
                                            const std::vector<double> &b)
{
    int n = L.getRows();                     // Get the number of rows in matrix L
    std::vector<double> y(n);                // Create a vector y to store solution, size n

    for(int i = 0; i < n; i++)              // Loop over each row
    {
        y[i] = b[i];                       // Start with the RHS value for row i
 
        for(int j = 0; j < i; j++)         // Loop over previous columns (j < i)
            y[i] -= L(i,j) * y[j];         // Subtract the sum of L(i,j)*y[j]

        y[i] /= L(i,i);                    // Divide by the diagonal element to isolate y[i]
    }

    return y;                              // Return the solved vector y
}


// Backward Substitution
// Solves Ux = y for x, where U is an upper triangular matrix

std::vector<double> LU::backwardSubstitution(const Matrix &U,
                                             const std::vector<double> &y)
{
    int n = U.getRows();                 // Get the number of rows in matrix U
    std::vector<double> x(n);            // Create a vector x to store solution, size n

    for(int i = n-1; i >= 0; i--)        // Loop from last row to first (bottom-up)
    {
        x[i] = y[i];                     // Start with the value from RHS vector y

        for(int j = i+1; j < n; j++)     // Loop over columns to the right of diagonal (j > i)
            x[i] -= U(i,j) * x[j];       // Subtract U(i,j) * x[j] (already solved)

        x[i] /= U(i,i);                  // Divide by diagonal element to isolate x[i]
    }

    return x;                             // Return the solved vector x
}