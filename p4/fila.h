#include <stdio.h>
#include <stdlib.h>

#include "kdtree.h"

#ifndef FILA_H_
#define FILA_H_

// Estrutura FILA
struct fila {
    struct nodo **nodos; // vetor de ponteiros para os nodos
    uint32_t tamanho;
};

// Retorna o ponteiro para a fila alocada dinâmicamente
struct fila *fila_criar(uint32_t tamanho);
// Adiciona nodo na fila, se houver espaço
void enfileirar(struct fila *fila, struct nodo *nodo, uint32_t tamanho);
// Remove o primeiro item da fila e o retorna
struct nodo *fila_remove(struct fila *fila);
// Libera da memória o ponteiro para a fila
struct fila *fila_libera(struct fila *fila);

#endif