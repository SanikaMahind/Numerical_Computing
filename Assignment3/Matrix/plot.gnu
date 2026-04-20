set title 'Gaussian Elimination Solution'
set xlabel 'Variable Index'
set ylabel 'Value'
set grid
set style data linespoints
plot 'resultvector.txt' using 1:2 with linespoints title 'Solution'
pause -1
