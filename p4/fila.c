#include <stdio.h>
#include <stdlib.h>

#include "kdtree.h"
#include "fila.h"

// Aloca dinâmicamente a fila e os nodos e seta o tamanho para 0
struct fila *fila_criar(uint32_t tamanho) {
    struct fila *fila = malloc(sizeof(struct fila));
    if(!fila) {
        matarProgramaPonteiroNulo();
    }

    fila->nodos = malloc(tamanho * sizeof(struct nodo*));
    if(!fila->nodos) {
        free(fila);
        matarProgramaFaltaMemoria();
    }

    fila->tamanho = 0;
    return fila;
}

// Adiciona o nodo no final da fila
void enfileirar(struct fila *fila, struct nodo *nodo, uint32_t tamanho) {
    if(!fila || !nodo) {
        matarProgramaPonteiroNulo();
    }

    if(fila->tamanho == tamanho) {
        printf("Capacidade da fila atingido\n");
        return;
    }

    fila->nodos[fila->tamanho] = nodo;
    fila->tamanho++;
}

struct nodo *fila_remove(struct fila *fila) {
    if(!fila) {
        matarProgramaPonteiroNulo();
    }

    if(!fila->tamanho) {
        printf("Fila vazia.\n");
        return NULL;
    }

    struct nodo *retirado = fila->nodos[0];

    for(size_t i = 1; i < fila->tamanho; i++) {
        fila->nodos[i - 1] = fila->nodos[i];
    }

    fila->tamanho--;
    return retirado;
}

struct fila *fila_libera(struct fila *fila) {
    if (!fila) {
        return fila;
    }

    free(fila->nodos);
    free(fila);

    return NULL; 
}