#Gnuplot script file for plotting data in data.dat
set output "Sieve.ps"
set autoscale
unset label
set title "Scale-up using OpenMP for Sieve of Eratosthenes"
set xlabel "Problem Size"
set ylabel "Speed in Microseconds"
plot "data.dat" using 1:2 title 'Serial' with lines, "data.dat" using 1:3 title '2 Threads' with lines, "data.dat" using 1:4 title '4 Threads' with lines, "data.dat" using 1:5 title '8 Threads' with lines
