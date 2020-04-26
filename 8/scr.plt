set xlabel 'log10(h)'
set ylabel 'log10(blad bezwzgledny)'
set title "zaleznosc bledu bezwzglednego przyblizen roznicowych od kroku sieci (double)
set terminal png size 1440, 720
set key outside
set key right top
set output "plot_d.png"
plot \
"out_d.txt" using 1:2 with lines title "x=0 progresywna dwupunktowa",\
"out_d.txt" using 1:3 with lines title "x=0 progresywna trzypunktowa",\
"out_d.txt" using 1:4 with lines title "x=pi/4 progresywna dwupunktowa",\
"out_d.txt" using 1:5 with lines title "x=pi/4 centralna dwupunktowa",\
"out_d.txt" using 1:6 with lines title "x=pi/4 wsteczna dwupunktowa",\
"out_d.txt" using 1:7 with lines title "x=pi/2 wsteczna dwupunktowa",\
"out_d.txt" using 1:8 with lines title "x=pi/2 wsteczna trzypunktowa"

set xlabel 'log10(h)'
set ylabel 'log10(blad bezwzgledny)'
set title "zaleznosc bledu bezwzglednego przyblizen roznicowych od kroku sieci (float)
set terminal png size 1440, 720
set key outside
set key right top
set output "plot_f.png"
plot \
"out_f.txt" using 1:2 with lines title "x=0 progresywna dwupunktowa",\
"out_f.txt" using 1:3 with lines title "x=0 progresywna trzypunktowa",\
"out_f.txt" using 1:4 with lines title "x=pi/4 progresywna dwupunktowa",\
"out_f.txt" using 1:5 with lines title "x=pi/4 centralna dwupunktowa",\
"out_f.txt" using 1:6 with lines title "x=pi/4 wsteczna dwupunktowa",\
"out_f.txt" using 1:7 with lines title "x=pi/2 wsteczna dwupunktowa",\
"out_f.txt" using 1:8 with lines title "x=pi/2 wsteczna trzypunktowa"

set xlabel 'log10(h)'
set ylabel 'log10(blad bezwzgledny)'
set title "zaleznosc bledu bezwzglednego przyblizen roznicowych od kroku sieci (double, float)
set terminal png size 1440, 720
set key outside
set key right top
set output "plot_f_d.png"
plot \
"out_d.txt" using 1:2 with lines title "double x=0 progresywna dwupunktowa",\
"out_d.txt" using 1:3 with lines title "double x=0 progresywna trzypunktowa",\
"out_d.txt" using 1:4 with lines title "double x=pi/4 progresywna dwupunktowa",\
"out_d.txt" using 1:5 with lines title "double x=pi/4 centralna dwupunktowa",\
"out_d.txt" using 1:6 with lines title "double x=pi/4 wsteczna dwupunktowa",\
"out_d.txt" using 1:7 with lines title "double x=pi/2 wsteczna dwupunktowa",\
"out_d.txt" using 1:8 with lines title "double x=pi/2 wsteczna trzypunktowa",\
"out_f.txt" using 2:2 with lines title "float x=0 progresywna dwupunktowa",\
"out_f.txt" using 2:3 with lines title "float x=0 progresywna trzypunktowa",\
"out_f.txt" using 2:4 with lines title "float x=pi/4 progresywna dwupunktowa",\
"out_f.txt" using 2:5 with lines title "float x=pi/4 centralna dwupunktowa",\
"out_f.txt" using 2:6 with lines title "float x=pi/4 wsteczna dwupunktowa",\
"out_f.txt" using 2:7 with lines title "float x=pi/2 wsteczna dwupunktowa",\
"out_f.txt" using 2:8 with lines title "float x=pi/2 wsteczna trzypunktowa"
