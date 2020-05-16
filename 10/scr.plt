set xrange [-20 : 2]
set yrange [-20 : 4]
set title 'Wykres zależności maksymalnych błędów bezwzględnych od kroku sieci'
set terminal png size 1440, 720
set output "plot_errors.png"
set ylabel 'log10(|blad|)'
set xlabel 'log10(dt)'
set grid
set key outside
set key right top
plot \
  'errors.txt' using 1:2 with lines title "Metoda Posrednia Eulera",\
  'errors.txt' using 1:3 with lines title "Metoda Bezposrednia Eulera - stabilna",\
  'errors.txt' using 1:4 with lines title "Metoda Trapezow"


set xrange [-0.1 : 3.5]
set yrange [0 : 1.20]
set title 'Wykres Metoda Posrednia Eulera'
set terminal png size 1440, 720
set output "posrednia_eulera.png"
set ylabel 'y'
set xlabel 't'
set grid
set key outside
set key right top
plot \
  'out.txt' using 1:2 with lines title "Rozwiazanie Analityczne",\
  'out.txt' using 1:3 with points pt 1 lc 8 title "Metoda Posrednia Eulera"


set xrange [-0.1 : 3.5]
set yrange [0 : 1.20]
set title 'Metoda Bezposrednia Eulera'
set terminal png size 1440, 720
set output "bezposrednia_eulera.png"
set ylabel 'y'
set xlabel 't'
set grid
set key outside
set key right top
plot \
  'out.txt' using 1:2 with lines title "Rozwiazanie Analityczne",\
  'out.txt' using 1:4 with points pt 1 lc 8 title "Metoda Bezposrednia Eulera - stabilna"


set xrange [-0.1 : 5]
set yrange [-75 : 75]
set title 'Metoda Bezposrednia Eulera - niestabilna'
set terminal png size 1440, 720
set output "bezposrednia_eulera_niestabilna.png"
set ylabel 'y'
set xlabel 't'
set grid
set key outside
set key right top
plot \
  'out.txt' using 1:2 with lines title "Rozwiazanie Analityczne",\
  'out_unstable.txt' using 1:2 with points pt 1 lc 8 title "Metoda Bezposrednia Eulera - niestabilna",


set xrange [-0.1 : 3.5]
set yrange [0 : 1.20]
set title 'Wykres Metoda Trapezow'
set terminal png size 1440, 720
set output "trapezow.png"
set ylabel 'y'
set xlabel 't'
set grid
set key outside
set key right top
plot \
  'out.txt' using 1:2 with lines title "Rozwiazanie Analityczne",\
  'out.txt' using 1:5 with points pt 1 lc 8 title "Metoda Trapezow"