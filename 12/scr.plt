#Rozwiazanie
set xrange [-1 : 1]
#set yrange [-0.2 : 1.05]
set terminal png size 1440, 720
set output "plot.png"
set ylabel 'y'
set xlabel 'x'
set key outside
set key right top
set grid 
plot \
 "out.txt" using 1:2 with lines lc rgb '#5555FF' title "Funkcja",\
 "out.txt" using 1:4 with points pt 3 lc rgb '#00CC00' title "węzły równoodlegle",\
 "out.txt" using 1:3 with points pt 1 lc rgb '#FF0000' title "węzły Czybyszewa",\
