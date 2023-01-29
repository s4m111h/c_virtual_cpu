
app: main.o dep.o 
	gcc main.o dep.o -o app && echo "\n" && ./app && echo "\n"

main: main.c dep.h 
	gcc -c main.c dep.h

dep: dep.c dep.h 
	gcc -c dep.c dep.h

clean:
	rm *.o app