set terminal jpeg
set title "Comparison Plot of Gaussian Curve"
set xlabel "Index"
set ylabel "Value"
plot "interpolated.dat" lt 8 title "interpolated",  "undersampled.dat" lt 7 title "undersampled"