#Ficheros entrada
#Fichero salida

fich0 = "PSun.txt"
fich    = "Hamiltoniano.txt"


#set terminal tikz
#salida =  'histo.tex' 
salida =  'Test.pdf'
#set term pdf enhanced size 10,6 color font "Arial,14"

#fit f(x) fich using 1:2:3:4 xyerror via a, b
#fit f(x) fich via a, b
#g(x) = c + d*x + e*x**2 + h*x**3
#fit g(x) fichero3 using 1:2:4 yerror via c, d, e, h

# ----------------- Representación del fichero de puntos experimentales -----------------------------------------------------------
#set style lines 1 lt rgb "purple" 
#plot fich [-0.1:0.05][0:1000000] title "Error" w xyerror lc rgb "red" ps 0.4 pt 7
#plot [][] fich title "" with linespoints linestyle 1 lw 1
#Por si queremos hacerlo 3D
#splot fich title "Error" w xyerror lc rgb "red" ps 1 pt 13
#Representacion puntos

set lmargin 10
set bmargin 4

#set title "Accretion Rate vs Mass of Donor, 100 Myrs Evolution "
#set title "Accretion Rate vs Mass of Accretor, 100 Myrs Evolution "
#set title "Accretion Rate vs Radius of Accretor, 100 Myrs Evolution "
set title "Conservación Hamiltoniano"
#set title "Accretion Rate vs Radius of Donor, 100 Myrs Evolution "
#set title "Accretion Rate vs Semimajor Axis, 100 Myrs Evolution "



#set xlabel "Accrate (Msun/Yrs)"

set ylabel " "#offset 2 rotate by 90
#set ylabel "Mass of Accretor (Msun)" offset -2 rotate by 90
#set ylabel "Radius of Accretor(Rsun)" offset 2 rotate by 90
set xlabel "" #offset 1 rotate by 90
#set ylabel "Semimajor Axis(Rsun)" offset -2 rotate by 90

#set ylabel "Mass of BH/NS(Msun)" #offset 7
#set grid x y z
#set zlabel "Phase of Donor" rotate by 90
#set zlabel "Semimajor Axis (Rsun)" rotate by 90
#set  zlabel rotate 90
#set lmargin 8
set ztics 1 nomirror #para no tener números

#plot[:1.5e-07][-0.000001:0.00012] fich title "z = 0.002" w xyerror lc rgb "blue" ps 0.2 pt 7
#plot[0:3.5e-07][0:0.0013] ficha title "z = 0.02" w xyerror lc rgb "red" ps 0.2 pt 7

#plot[-5e-09:4e-07][] fich2 title "z = 0.002" w xyerror lc rgb "blue" ps 0.2 pt 7
#plot[-5e-09:4e-07][0:0.00025] fich title "z = 0.002" w xyerror lc rgb "blue" ps 0.2 pt 7
plot[][] fich title "Hamiltoniano" w xyerror lc rgb "black" ps 0.1 pt 7
#replot fich2 title "Energia2" w xyerror lc rgb "yellow" ps 0.2 pt 7
#replot fich3 title "Sol Doble de Masa" w xyerror lc rgb "green" ps 0.2 pt 7
#replot fich4 title "Sol Triple de Masa" w xyerror lc rgb "red" ps 0.2 pt 7
#replot fich5 title "Jupiter Doble de Masa" w xyerror lc rgb "black" ps 0.2 pt 7
#replot fich6 title "Tierra 5 de Au" w xyerror lc rgb "brown" ps 0.2 pt 7




#plot[-5e-09:4e-07][] fich title "z = 0.002" w xyerror lc rgb "blue" ps 0.2 pt 7
#replot fich2 title "z = 0.02" w xyerror lc rgb "red" ps 0.2 pt 7
#replot fichas title "z = 0.01" w xyerror lc rgb "green" ps 0.2 pt 7
#replot fich title "" w xyerror lc rgb "blue" ps 0.2 pt 7
#stats fich
#f(x) = 814.4230769*x
#g(x) = 788.4615385*x 
#replot 814.4230769*x  title "Eddrate Z = 0.02"
#eplot 788.4615385*x  title "Eddrate Z = 0.002"
set term pdf enhanced size 12,12 color font "Arial,20"

#Funcion de ajuste2
set style lines 1 lt rgb "black" 

#replot f(x) title "Ajuste Lineal" with lines linestyle 1 dt 1 lw 2 # línea continua sin puntos (dt 1) y anchura 3 (lw 3) 
#set style lines 1 lt rgb "green"
#replot g(x) [5:20][]title "Valor Experimental Promedio" with lines linestyle 2 dt 1 lw 2 # línea continua sin puntos (dt 1) y anchura 3 (lw 3) 
#replot f(x) title "V/T; T < 18" with lines linestyle 1 dt 2 lw 3 # línea a trazos sin puntos (dt 2) y anchura 3 (lw 3)
# replot f(x) title "Ajuste Lineal" with lines linestyle 1 dt 3 lw 2 # línea 'punteada' sin puntos (dt 3) y anchura 2 (lw 2)  
# replot g(x) title "Ajuste Lineal" with linespoints linestyle 1 lw 1 # línea continua con puntos (linespoints) y anchura 1 (lw 1)

## ----------------- Leyenda ---------------------------------------------------------------------------
# Donde poner la Leyenda
set key top
set key right

set output salida
replot