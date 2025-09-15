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

// o nodo x é rotacionado a esquerda
void rotacao_esquerda(struct nodo **raiz, struct nodo *nodo) {
    struct nodo *aux = nodo->fd;
    nodo->fd = aux->fe;
    if (aux->fe != sentinela) {
        aux->fe->pai = nodo;
    }
    aux->pai = nodo->pai;
    if (nodo->pai == sentinela) {
        *raiz = aux;
    } else {
        if (nodo == nodo->pai->fe) {
            nodo->pai->fe = aux;
        } else {
            nodo->pai->fd = aux;
        }
    }
    aux->fe = nodo;
    nodo->pai = aux;
}

// o nodo x é rotacionado a direita
void rotacao_direita(struct nodo **raiz, struct nodo *nodo) {
    struct nodo *aux = nodo->fe;
    nodo->fe = aux->fd;
    if (aux->fd != sentinela) {
        aux->fd->pai = nodo;
    }
    aux->pai = nodo->pai;
    if (nodo->pai == sentinela) {
        *raiz = aux;
    } else {
        if (nodo == nodo->pai->fd) {
            nodo->pai->fd = aux;
        } else {
            nodo->pai->fe = aux;
        }
    }
    aux->fd = nodo;
    nodo->pai = aux;
}

// // Altera a árvore para manter as características da Red Black após uma inserção
void insere_fix(struct nodo **raiz, struct nodo *nodo) {
    // Verifica ponteiros
    if(!*raiz || !nodo) {
        printf("Erro ao criar novo nodo");
        exit(1);
    }

    while (nodo->pai->cor) {
        // O pai do nodo inserido é um filho esquerdo
        if (nodo->pai == nodo->pai->pai->fe) {
            struct nodo *tio = nodo->pai->pai->fd;
            if (tio->cor) {
                nodo->pai->cor = 0;
                tio->cor = 0;
                nodo->pai->pai->cor = 1;
                nodo = nodo->pai->pai;
            } else {
                if (nodo == nodo->pai->fd) {
                    nodo = nodo->pai;
                    rotacao_esquerda(raiz, nodo);
                }
            }
        // O pai do nodo inserido é um filho direito
        } else {
            struct nodo *tio = nodo->pai->pai->fe;
            if (tio->cor) {
                nodo->pai->cor = 0;
                tio->cor = 0;
                nodo->pai->pai->cor = 1;
                nodo = nodo->pai->pai;
            } else {
                if (nodo == nodo->pai->fe) {
                    nodo = nodo->pai;
                    rotacao_direita(raiz, nodo);
                }
            }
        }
    }
    (*raiz)->cor = 0;
}

//retorna SENTINELA se não foi possível inserir
struct nodo* inserir(struct nodo** raiz, int chave) {
    struct nodo *novo_nodo = cria_nodo(chave);
    struct nodo *x = *raiz;
    struct nodo *y = sentinela;

    while (x != sentinela) {
        y = x;
        if (novo_nodo->chave < x->chave) {
            x = x->fe;
        } else {
            x = x->fd;
        }        
    }

    novo_nodo->pai = y;
    if (y == sentinela) {
        *raiz = novo_nodo;
    } else {
        if (novo_nodo->chave < y->chave) {
            y->fe = novo_nodo;
        } else {
            y->fd = novo_nodo;
        }
    }
    //insere_fix(raiz, novo_nodo);

    return NULL;
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

    // TESTE INSERE


}