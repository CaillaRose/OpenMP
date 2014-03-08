#Gnuplot script file for plotting data in gdata.dat
set output "Gauss.ps"
set autoscale
unset label
set title "Scale-up using OpenMP for Gaussian Elimination"
set xlabel "Problem Size"
set ylabel "Speed in Microseconds"
plot "gdata.dat" using 1:2 title 'Serial' with lines, "gdata.dat" using 1:3 title '2 Threads' with lines, "gdata.dat" using 1:4 title '4 Threads' with lines, "gdata.dat" using 1:5 title '8 Threads' with lines
