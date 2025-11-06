parametrosCompilacao=-Wall -Wshadow -Wextra -g -std=c99
nomePrograma=prova4_20241731
OBJ = main.o kdtree.o
 
all: $(nomePrograma)

$(nomePrograma): $(OBJ)
	gcc -o $(nomePrograma) $(parametrosCompilacao) $(OBJ) -lm

main.o: main.c kdtree.h
	gcc -c main.c $(parametrosCompilacao)
	
kdtree.o: kdtree.h kdtree.c
	gcc -c kdtree.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)