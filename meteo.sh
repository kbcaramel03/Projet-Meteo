#!/bin/bash

#prends les secondes et les milli seconde du lancement du programme
debut=$(date +%s)
debutn=$(date +%N)

#execute le make, pour être sur que le .c soit compilé
make
make clean

#vérifie si la commande est help, sinon lance le .c avec les arguments
if  [ "$1" = "--help" ]
then  
    echo "pour executer le programme, entrez les arguments à la suite de l'appelle du programme.sh Les arguements valides sont:"
    
    ./meteo --help 
    echo "il est important de mettre des arguments dans cet ordre Meteo.sh [argument du type de graph] -i <nom du fichier> -o <nom de sorti du fichier> [le reste des argumentq]
    
    -Les différentes localisations sont:
    -F France
    -G Guyane
    -S Saint Pierre et Miquelon
    -A Antilles
    -O Ocean Indien
    -Q Antartique"
    exit 1
else
    ./meteo $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10} ${11} ${12} ${13} ${14} ${15} ${16} ${17} ${18}
fi

#verifie que les arguments existent et fait le gnuplot associé
while getopts 't:p:whmi:o:a:g:d:FGSAOQd:' ARG; do
    case "$ARG" in
        t) #température
            if [ "$OPTARG" = 1 ] #mode 1
            then
            x=(1)
            echo 'set terminal png
            set datafile separator ";"
            set output "temp_mode1.png"
            set title "La température en fonction de la station"
            set sample 50
            set style data points
            set xlabel "identifiant"
            set ylabel "température"' >> gnutest
            echo "plot '"$6"' using 1:5:3:4 with yerrorbar" >> gnutest #met les instructions dans gnutest, puis les execute dans gnuplot et enfin supprime gnutest

        elif [ "$OPTARG" = 2 ] #mode 2
        then
            x=(2)
            echo 'set terminal png
            set output "temp_mode2.png"
            set datafile separator ";" 
            set xdata time 
            set timefmt "%Y%m%d%H"
            set format x "%d\J-%H\h"
            set title "La température en fonction du temps"
            set sample 50
            set style data points
            set xlabel "date"
            set ylabel "température"' >> gnutest
            echo "plot  '"$6"' using 1:2 smooth unique with line" >> gnutest
        fi
            ;;
        p) #pression
            x=(1)
            if [ "$OPTARG" = 1 ] #mode 1
            then
                echo 'set terminal png
                set datafile separator ";"
                set output "press_mode1.png"
                set title "La pression en fonction de la station"
                set sample 50
                set style data points
                set xlabel "identifiant"
                set ylabel "pression"' >> gnutest
                echo "plot '"$6"' using 1:5:3:4 with yerrorbar" >> gnutest
            elif [ "$OPTARG" = 2 ] #mode 2
            then
                x=(2)
                echo 'set terminal png
                set output "press_mode2.png"
                set datafile separator ";" 
                set xdata time 
                set timefmt "%Y%m%d%H"
                set format x "%d\J-%H\h"
                set title "La pression en fonction du temps"
                set sample 50
                set style data points
                set xlabel "date"
                set ylabel "pression"' >> gnutest
                echo "plot  '"$6"' using 1:2 smooth unique with line" >> gnutest
            fi
            ;;
        w) #vent
            x=(3)
            echo 'set terminal png
            set datafile separator ";"
            set output "wind.png"
            set title "Le sens du vent"
            set style data points
            set angles degrees
            set xlabel "longitude"
            set ylabel "latitude"' >> gnutest
            echo "plot '"$5"' using 5:6:"'(($4*1.5)*cos($3)):(($4*1.5)*sin($3))'" with vector" >> gnutest
            ;;
        h) #hauteur
            x=(4)
            echo 'set terminal png
            set output "hauteur.png"
            set datafile separator ";"
            set title "La hauteur des stations"
            set style data lines
            set xlabel "Latitude"
            set ylabel "Longitude"
            set zlabel "Hauteur"
            set border 4095 front lt black linewidth 1.000 dashtype solid
            set dgrid3d 30,30,10
            set pm3d
            set palette rgb 21,22,23
            splot "'$5'" using 4:5:3' >> gnutest
            ;;
        m) #humidité
            x=(4)
            echo 'set terminal png
            set output "humidité.png"
            set datafile separator ";"
            set title "Humidité des stations"
            set style data lines
            set xlabel "Latitude"
            set ylabel "Longitude"
            set zlabel "Humidité"
            set border 4095 front lt black linewidth 1.000 dashtype solid
            set dgrid3d 30,30,10
            set pm3d
            set palette rgb 23,28,3
            splot "'$5'" using 4:5:3' >> gnutest
            ;;
        i) 
            ;;
        o)
            ;;
        F) #France
            LAST=`tail -n1 gnutest`
            sed -i "/$LAST/d" gnutest
            if [ $x -eq 1 ]
            then
                echo 'plot "'$6'" using 1:(($6<52 && $6>41 && $7<10 && $7>-5)?$5:1/0):(($6<52 && $6>41 && $7<10 && $7>-5)?$3:1/0):(($6<52 && $6>41 && $7<10 && $7>-5)?$4:1/0) with yerrorbar'>> gnutest
            elif [ $x -eq 2 ]
            then
                echo 'plot "'$6'" using 1:(($3<52 && $3>41 && $4<10 && $4>-5)?$2:1/0) with line'>> gnutest
            elif [ $x -eq 3 ]
            then
                echo 'plot "'$5'" using 5:6:(($5<52 && $5>41 && $6<10 && $6>-5)?(($4*1.5)*cos($3)):1/0):(($5<52 && $5>41 && $6<10 && $6>-5)?(($4*1.5)*sin($3)):1/0) with vector'>> gnutest
                echo 'ça marche pas :('
            elif [ $x -eq 4 ]
            then
                echo 'splot "'$5'" using 4:5:(($4<52 && $4>41 && $5<10 && $5>-5)?$3:1/0)' >> gnutest
            fi
            ;;
        G) #Guyanne
            LAST=`tail -n1 gnutest`
            sed -i "/$LAST/d" gnutest
            if [ $x -eq 1 ]
            then
                echo 'plot "'$6'" using 1:(($6<6 && $6>2 && $7<-51 && $7>-55)?$5:1/0):(($6<6 && $6>2 && $7<-51 && $7>-55)?$3:1/0):(($6<6 && $6>2 && $7<-51 && $7>-55)?$4:1/0) with yerrorbar'>> gnutest
            elif [ $x -eq 2 ]
            then
                echo 'plot "'$6'" using 1:(($3<6 && $3>2 && $4<-51 && $4>-55)?$2:1/0) with line'>> gnutest
            elif [ $x -eq 3 ]
            then
                echo 'plot "'$5'" using 5:6:(($5<6 && $5>2 && $6<-51 && $6>-55)?(($4*1.5)*cos($3)):1/0):(($5<6 && $5>2 && $6<-51 && $6>-55)?(($4*1.5)*sin($3)):1/0) with vector'>> gnutest
                echo 'ça marche pas :('
            elif [ $x -eq 4 ]
            then
                echo 'splot "'$5'" using 4:5:(($4<6 && $4>2 && $5<-51 && $5>-55)?$3:1/0)' >> gnutest
            fi
            ;;
        S) #SAINT PIERRE ET MIQUELON
            LAST=`tail -n1 gnutest`
            sed -i "/$LAST/d" gnutest
            if [ $x -eq 1 ]
            then
                echo 'plot "'$6'" using 1:(($6<47.1 && $6>46.7 && $7<-56.1 && $7>-56.5)?$5:1/0):(($6<47.1 && $6>46.7 && $7<-56.1 && $7>-56.5)?$3:1/0):(($6<47.1 && $6>46.7 && $7<-56.1 && $7>-56.5)?$4:1/0) with yerrorbar'>> gnutest
            elif [ $x -eq 2 ]
            then
                echo 'plot "'$6'" using 1:(($3<47.1 && $3>46.7 && $4<-56.1 && $4>-56.5)?$2:1/0) with line'>> gnutest
            elif [ $x -eq 3 ]
            then
                echo 'plot "'$5'" using 5:6:(($5<47.1 && $5>46.7 && $6<-56.1 && $6>-56.5)?(($4*1.5)*cos($3)):1/0):(($5<47.1 && $5>46.7 && $6<-56.1 && $6>-56.5)?(($4*1.5)*sin($3)):1/0) with vector'>> gnutest
                echo 'ça marche pas :('
            elif [ $x -eq 4 ]
            then
                echo 'splot "'$5'" using 4:5:(($4<47.1 && $4>46.7 && $5<-56.1 && $5>-56.5)?$3:1/0)' >> gnutest
            fi
            ;;
        A) #ANTILLES
            LAST=`tail -n1 gnutest`
            sed -i "/$LAST/d" gnutest
            if [ $x -eq 1 ]
            then
                echo 'plot "'$6'" using 1:(($6<19.4 && $6>12.4 && $7<-58 && $7>-66)?$5:1/0):(($6<19.4 && $6>12.4 && $7<-58 && $7>-66)?$3:1/0):(($6<19.4 && $6>12.4 && $7<-58 && $7>-66)?$4:1/0) with yerrorbar'>> gnutest
            elif [ $x -eq 2 ]
            then
                echo 'plot "'$6'" using 1:(($3<19.4 && $3>12.4 && $4<-58 && $4>-66)?$2:1/0) with line'>> gnutest
            elif [ $x -eq 3 ]
            then
                echo 'plot "'$5'" using 5:6:(($5<19.4 && $5>12.4 && $6<-58 && $6>-66)?(($4*1.5)*cos($3)):1/0):(($5<52 && $5>12.4 && $6<-58 && $6>-66)?(($4*1.5)*sin($3)):1/0) with vector'>> gnutest
                echo 'ça marche pas :('
            elif [ $x -eq 4 ]
            then
                echo 'splot "'$5'" using 4:5:(($4<19.4 && $4>12.4 && $5<-58 && $5>-66)?$3:1/0)' >> gnutest
            fi
            ;;
        O) #OCEAN INDIEN
            LAST=`tail -n1 gnutest`
            sed -i "/$LAST/d" gnutest
            if [ $x -eq 1 ]
            then
                echo 'plot "'$6'" using 1:(($6<-10.8 && $6>-26.4 && $7<60.7 && $7>41.3)?$5:1/0):(($6<-10.8 && $6>-26.4 && $7<60.7 && $7>41.3)?$3:1/0):(($6<-10.8 && $6>-26.4 && $7<60.7 && $7>41.3)?$4:1/0) with yerrorbar'>> gnutest
            elif [ $x -eq 2 ]
            then
                echo 'plot "'$6'" using 1:(($3<-10.8 && $3>-26.4 && $4<60.7 && $4>41.3)?$2:1/0) with line'>> gnutest
            elif [ $x -eq 3 ]
            then
                echo 'plot "'$5'" using 5:6:(($5<-10.8 && $5>-26.4 && $6<60.7 && $6>41.3)?(($4*1.5)*cos($3)):1/0):(($5<-10.8 && $5>-26.4 && $6<60.7 && $6>41.3)?(($4*1.5)*sin($3)):1/0) with vector'>> gnutest
                echo 'ça marche pas :('
            elif [ $x -eq 4 ]
            then
                echo 'splot "'$5'" using 4:5:(($4<-10.8 && $4>-26.4 && $5<60.7 && $5>41.3)?$3:1/0)' >> gnutest
            fi
            ;;
        Q) #ANTARTIQUE
            LAST=`tail -n1 gnutest`
            sed -i "/$LAST/d" gnutest
            if [ $x -eq 1 ]
            then
                echo 'plot "'$6'" using 1:(($7<-58)?$5:1/0):(($7<-58)?$3:1/0):(($7<-58)?$4:1/0) with yerrorbar'>> gnutest
            elif [ $x -eq 2 ]
            then
                echo 'plot "'$6'" using 1:(($4<-58)?$2:1/0) with line'>> gnutest
            elif [ $x -eq 3 ]
            then
                echo 'plot "'$5'" using 5:6:(($6<-58)?(($4*1.5)*cos($3)):1/0):(($6<-58)?(($4*1.5)*sin($3)):1/0) with vector'>> gnutest
                echo 'ça marche pas :('
            elif [ $x -eq 4 ]
            then
                echo 'splot "'$5'" using 4:5:(($5<-58)' >> gnutest
            fi
            ;;
        a)
            ;;
        g)
            ;;
        d)
            ;;
        ?)
            ;;
    esac
done
gnuplot --persist gnutest
rm gnutest

#prends les secondes et les milli secondes à la fin du programme
fin=$(date +%s)
finn=$(date +%N)

duree=$(( $fin - $debut ))
dureen=$(( ($finn*10) - $debutn))

#affiche la durée du programme
echo "$duree.$dureen secondes"