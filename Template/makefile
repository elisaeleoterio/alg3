parametrosCompilacao=-Wall -Wshadow -Wextra -g -std=c99
nomePrograma=antesprova_20241731
OBJ = main.o redblack.o fila.o trataErro.o aluno.o
 
all: $(nomePrograma)

$(nomePrograma): $(OBJ)
	gcc $(nomePrograma) -o $(parametrosCompilacao) $(OBJ)

main.o: main.c redblack.h
	gcc -c main.c $(parametrosCompilacao)
	
redblack.o: redblack.h redblack.c
	gcc -c redblack.c $(parametrosCompilacao)

fila.o: fila.c fila.h

trataErro.o = trataErro.c trataErro.h

aluno.o = aluno.c aluno.h

clean:
	rm -f *.o *.gch $(nomePrograma)