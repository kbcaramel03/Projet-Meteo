exe: fonctions.o main.o
	gcc -Wall fonctions.o main.o -o meteo

fonctions.o: fonctions.c fonctions.h
	gcc -c fonctions.c  -o fonctions.o

main.o: main.c fonctions.h
	gcc -Wall -c main.c -o main.o

clean:
	rm -f *.o
