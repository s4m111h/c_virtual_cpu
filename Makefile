
app: main.o dep.o 
	rm app && gcc main.o dep.o -o app

main: main.c dep.o
	rm main.o && gcc -c main.c dep.o

dep: dep.h dep.c
	rm dep.o && gcc -c dep.h dep.c
