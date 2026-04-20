#include "../include/gerschgorin.hpp"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <stdexcept>

// Constructor with size
Gerschgorin::Gerschgorin(int n) : EigenValue(n) {}

// -----------------------------------------------------------------------
// analyze() — main entry point
// Computes all Gerschgorin discs, prints progress to terminal,
// saves full results to "gerschgorin_result.txt"
// -----------------------------------------------------------------------
void Gerschgorin::analyze()
{
    if (rows != cols)
        throw std::logic_error("Gerschgorin theorem requires a square matrix");

    printProgress("\n----- Gerschgorin Circle Theorem -----");
    printProgress("Computing discs for " + std::to_string(rows) + "x"
                  + std::to_string(cols) + " matrix...");

    // Step 1: compute all discs
    computeDiscs();

    printProgress("Discs computed.");
    printProgress("Overall eigenvalue lower bound : " +
                  std::to_string(overallLower));
    printProgress("Overall eigenvalue upper bound : " +
                  std::to_string(overallUpper));
    printProgress("Spectral radius estimate       : " +
                  std::to_string(spectralRadius));

    // Step 2: build result string and save to file
    std::string content = buildResultString();
    saveResultsToFile("gerschgorin_result.txt",
                      "Gerschgorin Circle Theorem", content);

    printProgress("\nResults saved --> gerschgorin_result.txt");
}

// -----------------------------------------------------------------------
// computeDiscs() — fills the discs vector and computes overall bounds
// -----------------------------------------------------------------------
void Gerschgorin::computeDiscs()
{
    int n = rows;
    discs.clear();
    discs.reserve(n);

    overallLower   =  std::numeric_limits<double>::max();
    overallUpper   = -std::numeric_limits<double>::max();
    spectralRadius =  0.0;

    for (int i = 0; i < n; i++)
    {
        GerschgorinDisc d;
        d.row    = i + 1;
        d.center = data[i][i];

        // Radius = sum of absolute values of off-diagonal elements in row i
        d.radius = 0.0;
        for (int j = 0; j < n; j++)
            if (j != i)
                d.radius += std::fabs(data[i][j]);

        d.lower = d.center - d.radius;
        d.upper = d.center + d.radius;

        // Update overall bounds
        overallLower = std::min(overallLower, d.lower);
        overallUpper = std::max(overallUpper, d.upper);

        // Spectral radius estimate: max(|center| + radius)
        spectralRadius = std::max(spectralRadius,
                                  std::fabs(d.center) + d.radius);

        discs.push_back(d);
    }
}

// -----------------------------------------------------------------------
// buildResultString() — formats the full output as a string
// -----------------------------------------------------------------------
std::string Gerschgorin::buildResultString() const
{
    std::ostringstream oss;

    // ---- Theory explanation ----
    oss << "Gerschgorin Circle Theorem:\n";
    oss << "  For each row i, define disc D_i:\n";
    oss << "    Center c_i = A[i][i]  (diagonal element)\n";
    oss << "    Radius r_i = SUM |A[i][j]| for j != i\n";
    oss << "  Every eigenvalue of A lies in at least one disc D_i.\n";
    oss << "  Eigenvalue of row i is in range [c_i - r_i, c_i + r_i]\n\n";

    // ---- Table of discs ----
    int w = 14;
    oss << std::string(70, '-') << "\n";
    oss << std::setw(6)  << "Row"
        << std::setw(w)  << "Center (c_i)"
        << std::setw(w)  << "Radius (r_i)"
        << std::setw(w)  << "Lower Bound"
        << std::setw(w)  << "Upper Bound"
        << "\n";
    oss << std::string(70, '-') << "\n";

    for (const auto &d : discs)
    {
        oss << std::setw(6)  << d.row
            << std::setw(w)  << std::fixed << std::setprecision(6) << d.center
            << std::setw(w)  << std::fixed << std::setprecision(6) << d.radius
            << std::setw(w)  << std::fixed << std::setprecision(6) << d.lower
            << std::setw(w)  << std::fixed << std::setprecision(6) << d.upper
            << "\n";
    }
    oss << std::string(70, '-') << "\n\n";

    // ---- Summary ----
    oss << "Summary:\n";
    oss << "  Number of discs      : " << discs.size()          << "\n";
    oss << "  Overall lower bound  : " << std::fixed << std::setprecision(6)
        << overallLower   << "\n";
    oss << "  Overall upper bound  : " << std::fixed << std::setprecision(6)
        << overallUpper   << "\n";
    oss << "  Eigenvalue range     : ["
        << std::fixed << std::setprecision(6) << overallLower
        << " , "
        << std::fixed << std::setprecision(6) << overallUpper << "]\n";
    oss << "  Spectral radius est. : " << std::fixed << std::setprecision(6)
        << spectralRadius << "\n\n";

    // ---- Dominant disc info ----
    auto maxDisc = std::max_element(discs.begin(), discs.end(),
        [](const GerschgorinDisc &a, const GerschgorinDisc &b){
            return a.radius < b.radius;
        });
    auto minDisc = std::min_element(discs.begin(), discs.end(),
        [](const GerschgorinDisc &a, const GerschgorinDisc &b){
            return a.radius < b.radius;
        });

    oss << "Largest disc  : Row " << maxDisc->row
        << "  center=" << std::fixed << std::setprecision(4) << maxDisc->center
        << "  radius=" << std::fixed << std::setprecision(4) << maxDisc->radius
        << "\n";
    oss << "Smallest disc : Row " << minDisc->row
        << "  center=" << std::fixed << std::setprecision(4) << minDisc->center
        << "  radius=" << std::fixed << std::setprecision(4) << minDisc->radius
        << "\n\n";

    // ---- Interpretation ----
    oss << "Interpretation:\n";
    oss << "  All eigenvalues of this " << rows << "x" << cols
        << " matrix lie in the union\n";
    oss << "  of the " << discs.size() << " Gerschgorin discs listed above.\n";
    oss << "  The guaranteed eigenvalue range is ["
        << std::fixed << std::setprecision(4) << overallLower
        << " , "
        << std::fixed << std::setprecision(4) << overallUpper << "].\n";

    return oss.str();
}
