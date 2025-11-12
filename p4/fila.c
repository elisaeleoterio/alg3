#include <stdio.h>
#include <stdlib.h>

#include "erro.h"
#include "kdtree.h"
#include "fila.h"

struct fila *fila_criar(uint32_t tamanho) {
    struct fila *fila = malloc(sizeof(struct fila));
    if(!fila) {
        matar_programa_ponteiro_nulo();
    }

    fila->nodos = malloc(tamanho * sizeof(struct nodo*));
    if(!fila->nodos) {
        free(fila);
        matar_programa_falta_memoria();
    }

    fila->tamanho = 0;
    return fila;
}

// Adiciona o nodo no final da fila
void enfileirar(struct fila *fila, struct nodo *nodo, uint32_t tamanho) {
    if(!fila || !nodo) {
        matar_programa_ponteiro_nulo();
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
        matar_programa_ponteiro_nulo();
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

// Implementação para imprimir em lergura corretamente
struct fila_nivel *fila_criar_nivel(uint32_t tamanho) {
    struct fila_nivel *fila_nv = malloc(sizeof(struct fila_nivel));
    if(!fila_nv) {
        matar_programa_ponteiro_nulo();
    }

    fila_nv->nivel = malloc(tamanho * sizeof(uint64_t));
    if(!fila_nv->nivel) {
        free(fila_nv);
        matar_programa_falta_memoria();
    }

    fila_nv->tamanho = 0;
    return fila_nv;
}

// Adiciona o nodo no final da fila
void enfileirar_nivel(struct fila_nivel *fila_nv, uint32_t nivel, uint32_t tamanho) {
    if(!fila_nv) {
        matar_programa_ponteiro_nulo();
    }

    if(fila_nv->tamanho == tamanho) {
        printf("Capacidade da fila nível atingido\n");
        return;
    }

    fila_nv->nivel[fila_nv->tamanho] = nivel;
    fila_nv->tamanho++;
}

// Remove o primeiro item da fila e o retorna
int32_t fila_remove_nivel(struct fila_nivel *fila_nv) {
    if(!fila_nv) {
        matar_programa_ponteiro_nulo();
    }

    if(!fila_nv->tamanho) {
        printf("Fila nivel vazia.\n");
        return -1;
    }

    int32_t retirado = fila_nv->nivel[0];

    for(size_t i = 1; i < fila_nv->tamanho; i++) {
        fila_nv->nivel[i - 1] = fila_nv->nivel[i];
    }

    fila_nv->tamanho--;
    return retirado;
}

struct fila_nivel *fila_libera_nivel(struct fila_nivel *fila_nv) {
    if (!fila_nv) {
        return fila_nv;
    }

    free(fila_nv->nivel);
    free(fila_nv);

    return NULL; 
}
