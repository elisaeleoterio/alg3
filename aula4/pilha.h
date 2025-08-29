#include <stdio.h>
#include <stdlib.h>
#include "buscaBinaria.h"

struct pilha {
    struct nodo **nodo; // vetor de nodos
    int tamanho;
};

struct nodo *pilha_criar(struct pilha *pilha, int valor);
struct nodo *pilha_empilhar(struct pilha *pilha, struct nodo *nodo);
struct nodo *pilha_desempilhar(struct pilha *pilha);
struct nodo *pilha_topo(struct pilha *pilha);

int pilha_tamanho(struct pilha *pilha);
int pilha_imprimir(struct pilha *pilha);