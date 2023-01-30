
app: main.o dep.o 
	gcc main.o dep.o -o app

main: main.c dep.o
	gcc -c main.c dep.o

dep: dep.h dep.c
	gcc -c dep.h dep.c


cleandep:
	rm dep.o
cleanmain:
	rm main.o
cleanapp:
	rm app
cleanall:
	rm dep.o main.o app