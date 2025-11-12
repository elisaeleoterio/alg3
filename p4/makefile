CFLAGS = -Wall -Wshadow -Wextra -g -std=c99
LDLIBS = -lm # usado para linkar a biblioteca math.h
nomePrograma=prova4_20241731
OBJ = main.o kdtree.o fila.o max_heap.o utils.o erro.o
 
all: $(nomePrograma)

$(nomePrograma): $(OBJ)
	gcc -o $(nomePrograma) $(CFLAGS) $^ $(LDLIBS)

main.o: main.c kdtree.h utils.h erro.h
kdtree.o: kdtree.c kdtree.h
fila.o: fila.c fila.h
max_heap.o: max_heap.c max_heap.h
utils.o: utils.c utils.h
erro.o: erro.c erro.h

clean:
	rm -f *.o *.gch $(nomePrograma)