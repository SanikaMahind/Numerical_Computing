#include "../include/iterative.hpp"
#include <stdexcept>


// Constructor
// Initializes iteration limit and tolerance

IterativeMethod::IterativeMethod(int maxIter, double tol)
    : LinearSystem(), maxIterations(maxIter), tolerance(tol)
{}


// checkAndFixDominance()
// Checks if matrix is diagonally dominant
// If not → tries to rearrange rows to achive dominance 

void IterativeMethod::checkAndFixDominance()
{
    std::cout << "\n----- Diagonal Dominance Check -----\n";

    // If already dominant → no need to change
    if (isDiagonallyDominant())
    {
        std::cout << "Matrix is already Diagonally Dominant. Proceeding...\n";
        return;
    }

    std::cout << "Matrix is NOT Diagonally Dominant.\n";
    std::cout << "Attempting to rearrange rows...\n";

    int n = rows;

    // -------------------------------------------------------
    // Try to rearrange rows to make diagonal dominant
    // -------------------------------------------------------
    for (int i = 0; i < n; i++)
    {
        int bestRow = i;
        double bestVal = std::abs(data[i][i]);

        // Find row with maximum absolute value in column i
        for (int r = i + 1; r < n; r++)
        {
            if (std::abs(data[r][i]) > bestVal)
            {
                bestVal = std::abs(data[r][i]);
                bestRow = r;
            }
        }

        // Swap rows in A and b
        if (bestRow != i)
        {
            std::swap(data[i], data[bestRow]);   // swap matrix rows
            std::swap(b[i], b[bestRow]);         // swap RHS values
        }
    }

    // -------------------------------------------------------
    // Rebuild augmented matrix after swapping
    // -------------------------------------------------------
    augmented = Matrix(rows, cols + 1);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            augmented(i, j) = data[i][j];

        augmented(i, cols) = b[i];
    }

    // Check again
    if (isDiagonallyDominant())
    {
        std::cout << "SUCCESS: Rows rearranged. Matrix is now Diagonally Dominant.\n";
        std::cout << "\nRearranged Augmented Matrix [A|b]:\n";
        printAugmented();
    }
    else
    {
        std::cout << "WARNING: Could not achieve full Diagonal Dominance.\n";
        std::cout << "Iterative method may not converge.\n";
    }
}

// -----------------------------------------------------------
// printIterationHeader()
// Prints iteration table header
// -----------------------------------------------------------
void IterativeMethod::printIterationHeader() const
{
    std::cout << std::setw(6) << "Iter" << "  |";

    for (int i = 0; i < cols; i++)
        std::cout << std::setw(14) << ("x[" + std::to_string(i + 1) + "]");

    std::cout << "\n" << std::string(8 + cols * 14, '-') << "\n";
}

// -----------------------------------------------------------
// saveSolutionToFile()
// Saves solution to "resultvector.txt"
// -----------------------------------------------------------
void IterativeMethod::saveSolutionToFile(const std::vector<double> &solution) const
{
    std::ofstream f("resultvector.txt");

    if (!f)
        throw std::runtime_error("Cannot create resultvector.txt");

    f << "# Index  Value\n";

    for (int i = 0; i < (int)solution.size(); i++)
        f << i + 1 << "  "
          << std::fixed << std::setprecision(6)
          << solution[i] << "\n";

    f.close();
}


// Save augmented matrix [A|b] to resultmatrix.txt
void IterativeMethod::saveMatrixToFile() const
{
    std::ofstream matrixFile("resultmatrix.txt");
    if (!matrixFile)
        throw std::runtime_error("Cannot create resultmatrix.txt");

    matrixFile << "Augmented Matrix [A|b] (after possible diagonal dominance adjustment):\n";

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            matrixFile << std::setw(12) << std::fixed << std::setprecision(6) << data[i][j];

        matrixFile << " | " << std::setw(12) << std::fixed << std::setprecision(6) << b[i] << "\n";
    }

    matrixFile.close();
}


