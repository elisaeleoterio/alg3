#include <stdio.h>
#include <stdlib.h>

#include "redblack.h"

// Declaração da variável global do SENTINELA
struct nodo *sentinela = NULL;

void inicia_sentinela() {
    if (sentinela == NULL) {
        sentinela = malloc(sizeof(struct nodo));
        if (!sentinela) {
            printf("Erro ao incializar sentinela\n");
            exit(1);
        }
    }

    sentinela->chave = -1;
    sentinela->cor = 0;
    sentinela->fd = sentinela;
    sentinela->fe = sentinela;
    sentinela->pai = sentinela;
}

struct nodo *cria_nodo(int valor) {
    struct nodo *nodo = malloc(sizeof(struct nodo));
    if (!nodo) {
        printf("Erro ao criar novo nodo");
        exit(1);
    }

    nodo->chave = valor;
    nodo->cor = 0;
    nodo->fd = sentinela;
    nodo->fe = sentinela;
    nodo->pai = sentinela;   
    
    return nodo;
}

int main() {

    // TESTE SENTINELA
    inicia_sentinela();

    printf("SENTINELA\n");
    printf("%d", sentinela->chave);

    // TESTE CRIA NODO
    int chave;
    printf("insira chave: ");
    scanf("%d", &chave);

    struct nodo *novo_nodo = cria_nodo(chave);
    printf("Chave do nodo: %d\n", novo_nodo->chave);
}