#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "buscaBinaria.h"


struct pilha *pilha_criar(struct pilha *pilha, struct nodo **nodo) {
    if(pilha == NULL || nodo == NULL) {
        printf("ponteiros nulos");
        return NULL;
    }

    pilha->nodo = nodo;
    pilha->tamanho = 0;

    return pilha;
}


/* Adiciona um elemento na pilha
● Pela política LIFO, o elemento é adicionado no topo da pilha
● Retorna -1 caso a pilha seja um ponteiro vazio
● Retorna -2 se a pilha estiver cheia
*/
int pilha_empilhar(struct pilha *pilha, struct nodo *nodo) {
    if (pilha == NULL) {
        printf("ponteiro nulo");
        return -1;
    }
    
}
struct nodo *pilha_desempilhar(struct pilha *pilha);
struct nodo *pilha_topo(struct pilha *pilha);

int pilha_tamanho(struct pilha *pilha);
int pilha_imprimir(struct pilha *pilha);