set title 'Gaussian Elimination Solution'
set xlabel 'Index'
set ylabel 'Value'
set grid
plot 'resultvector.txt' using 1:2 with linespoints
pause -1
