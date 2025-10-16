parametrosCompilacao=-Wall -Wshadow -Wextra -g -std=c99
nomePrograma=antesprova_20241731
OBJ = main.o redblack.o
 
all: $(nomePrograma)

$(nomePrograma): $(OBJ)
	gcc -o $(nomePrograma) $(parametrosCompilacao) $(OBJ)

main.o: main.c redblack.h
	gcc -c main.c $(parametrosCompilacao)
	
redblack.o: redblack.h redblack.c
	gcc -c redblack.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)