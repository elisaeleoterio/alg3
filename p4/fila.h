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

struct fila_nivel {
    int32_t *nivel; // vetor de ponteiros para os níveis
    uint32_t tamanho;
};

// Aloca dinâmicamente a fila e os nodos e seta o tamanho para 0
struct fila *fila_criar(uint32_t tamanho);
// Adiciona nodo na fila, se houver espaço
void enfileirar(struct fila *fila, struct nodo *nodo, uint32_t tamanho);
// Remove o primeiro item da fila e o retorna
struct nodo *fila_remove(struct fila *fila);
// Libera da memória o ponteiro para a fila
struct fila *fila_libera(struct fila *fila);

// FILA Nível
struct fila_nivel *fila_criar_nivel(uint32_t tamanho);
void enfileirar_nivel(struct fila_nivel *fila_nv, uint32_t nivel, uint32_t tamanho);
int32_t fila_remove_nivel(struct fila_nivel *fila_nv);
struct fila_nivel *fila_libera_nivel(struct fila_nivel *fila_nv);

#endif