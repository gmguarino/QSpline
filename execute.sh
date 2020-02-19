gcc -o interp interp.c QSpline.c -lm
./interp
gnuplot plotter.plot > out.jpeg
rm interp undersampled.dat interpolated.dat