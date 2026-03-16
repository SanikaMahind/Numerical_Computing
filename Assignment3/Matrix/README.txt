Build and run instructions

Compile:
    g++ -O2 -std=c++17 main.cpp src/matrix.cpp -o matrix_app

Usage examples:

Addition:
    ./matrix_app add A.txt B.txt out.txt

Subtraction:
    ./matrix_app sub A.txt B.txt out.txt

Gaussian elimination (LHS and RHS provided separately):
    ./matrix_app gauss LHS.txt RHS.txt sol_matrix.txt sol_vector.txt

Input file format (first line rows cols, then entries row-major):
Example A.txt for 2x2 matrix:
2 2
1 2
3 4

Example RHS for 2x1 vector:
2 1
5
6

Outputs:
- Augmented matrix saved to augmented_matrix.txt
- Solution matrix (n x 1) saved to sol_matrix.txt
- Solution vector in format x1 = ... saved to sol_vector.txt
- Also plot.png generated using gnuplot (if installed) and plot_data.txt used as data file
