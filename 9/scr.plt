set xrange [-4.5  : -0.8]
set yrange [-14.5 : -2.5]
set title "zależnosc błędu bezwzględnego rozwiązań od kroku sieci
set terminal png size 1440, 720
set output "plot_errors.png"
set ylabel 'log10(blad)'
set xlabel 'log10(krok)'
set key outside
set key right top
set grid 
plot \
 "out_errors.txt" using 1:2 with lines title "dyskretyzacja trójpunktowa",\
 "out_errors.txt" using 1:3 with lines title "dyskretyzacja Numerowa"

 
set xrange [0.0 : 1.0]
set yrange [0.0 : 1.0]
set terminal png size 1440, 720
set output "plot_function.png"
set title 'Wykres funkcji'
set ylabel 'y'
set xlabel 'x'
set key outside
set key right top
set grid 
plot \
 "out_conventional.txt" using 1:2 with lines              title "Dyskretyzacja konwencjonalna",\
 "out_numerow.txt"      using 1:2 with points pt 13 lc 10 title "Dyskretyzacja Numerowa",\
 "out_numerow.txt"      using 1:3 with points pt 1 lc 20  title "Rozwiazanie analityczne"
