#include "redblack.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

// FUNÇÕES de implementação da Estrutura FILA
struct fila {
    struct nodo **nodos; // vetor de ponteiros para os nodos
    uint32_t tamanho;
};

// Aloca dinâmicamente a fila e os nodos e seta o tamanho para 0
struct fila *filaCriar(uint32_t tamanho);

// Adiciona o nodo no final da fila
void enfileirar(struct fila *fila, struct nodo *nodo, uint32_t tamanho);

// Remove o primeiro item da fila e o retorna
struct nodo *filaRemove(struct fila *fila);

struct fila *filaLibera(struct fila *fila);