#include "redblack.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>



void matarProgramaFaltaMemoria() {
    printf("Erro por falta de memória\n");
    exit(1);
}

struct aluno* getAluno(){
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if(!retorno)
        matarProgramaFaltaMemoria();

    retorno->nome = malloc(sizeof("Elisa Rocha Eleotério"));//sizeof conta o \0
	if(!retorno->nome)
		matarProgramaFaltaMemoria();
        
    retorno->nomeDinf = malloc(sizeof("ere24"));
    if(!retorno->nomeDinf) {
        matarProgramaFaltaMemoria();
    }
    
	strcpy(retorno->nome, "Elisa Rocha Eleotério");
    strcpy(retorno->nomeDinf, "ere24");
    retorno->grr = 20241731;

	return retorno;
}

void imprimirDadosAluno(){
    struct aluno* aluno = getAluno();
    
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    return;
}



//FUNÇÕES RED BLACK

// Subárvore nodoB toma o lugar da subárvore nodoA
void transplante(struct nodo *raiz, struct nodo *nodoA, struct nodo *nodoB) {
    if (!raiz || !nodoA || !nodoB) {
        printf("Ponteiros nulos\n");
        exit(1);
    }

    if (nodoA->pai == sentinela) {
        raiz = nodoB;
    } else {
        if (nodoA == nodoA->pai->fe) {
            nodoA->pai->fe = nodoB;
        } else {
           nodoA->pai->fd = nodoB;
        }      
    }
    nodoB->pai = nodoA->pai;
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

// Altera a árvore para manter as características da Red Black após uma exclusão
void delete_fix(struct nodo *raiz, struct nodo *nodo) {

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

// retorna o número de nodos excluídos
int excluir(struct nodo** raiz, int chave) {
    // Verificação de ponteiros

    struct nodo *aux = 
}

// //retorna SENTINELA se não existe
// struct nodo* buscar(struct nodo* raiz, int chave) {

// }

// void imprimirEmOrdem(struct nodo* nodo) {

// }

// void imprimirEmLargura(struct nodo* raiz) {

// }