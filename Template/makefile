parametrosCompilacao=-Wall -Wshadow -Wextra -g -std=c99
nomePrograma=trab

all: $(nomePrograma)

$(nomePrograma): main.o redblack.o
	gcc -o $(nomePrograma) main.o redblack.o $(parametrosCompilacao)

main.o: main.c redblack.h
	gcc -c main.c $(parametrosCompilacao)
	
redblack.o: redblack.h redblack.c
	gcc -c redblack.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)

#CC     = gcc
#CFLAGS = -Wall -Wextra -g -std=c99
#LIB    = fprio
#BIN    = testa-fprio

#$(BIN):   $(BIN).o $(LIB).o
#$(BIN).o: $(BIN).c $(LIB).h
#$(LIB).o: $(LIB).c $(LIB).h

#teste: $(BIN)
#	./$(BIN)

#valgrind: $(BIN)
#	valgrind --leak-check=full --track-origins=yes ./$(BIN)

#clean:
#	rm -f *.o *~ $(BIN)
