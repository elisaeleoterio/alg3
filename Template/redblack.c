#include "redblack.h"

#include <stdlib.h>
#include <string.h>

// Declaração da variável global do SENTINELA
struct nodo *SENTINELA = NULL;
void inicia_sentinela() {
    if (SENTINELA == NULL) {
        SENTINELA = malloc(sizeof(struct nodo));
        if (!SENTINELA) {
            exit(1);
        }
    }

    SENTINELA->chave = -1;
    SENTINELA->cor = 0;
    SENTINELA->fd = SENTINELA;
    SENTINELA->fe = SENTINELA;
    SENTINELA->pai = SENTINELA;
}

struct aluno* getAluno(){
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if(!retorno)
        matarProgramaFaltaMemoria();

    retorno->nome = malloc(sizeof("Elisa Rocha Eleotério"));//sizeof conta o \0
	if(!retorno->nome)
		matarProgramaFaltaMemoria();
        
    retorno->nomeDinf = malloc(sizeof("ere24"));
    if(!retorno->nomeDinf)
        matarProgramaFaltaMemoria();
    
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

struct nodo *cria_nodo(int valor) {
    struct nodo *nodo = malloc(sizeof(struct nodo));
    if (!nodo) {
        printf("Erro ao criar novo nodo");
        exit(1);
    }

    nodo->chave = valor;
    nodo->cor = 0;
    nodo->fd = SENTINELA;
    nodo->fe = SENTINELA;
    nodo->pai = SENTINELA;   
    
    return nodo;
}

// Subárvore nodoB toma o lugar da subárvore nodoA
void transplante(struct nodo *raiz, struct nodo *nodoA, struct nodo *nodoB) {
    if (!raiz || !nodoA || !nodoB) {
        printf("Ponteiros nulos\n");
        exit(1);
    }

    if (nodoA->pai == SENTINELA) {
        raiz = nodoB;
    }
    
    
}

// o nodo x é rotacionado a esquerda
void rotacao_esquerda(struct nodo *raiz, struct nodo *nodo) {

}

// Altera a árvore para manter as características da Red Black após uma inserção
void insere_fix(struct nodo *raiz, struct nodo *nodo) {

}

// Altera a árvore para manter as características da Red Black após uma exclusão
void delete_fix(struct nodo *raiz, struct nodo *nodo) {

}

//retorna SENTINELA se não foi possível inserir
struct nodo* inserir(struct nodo** raiz, int chave) {

}

// retorna o número de nodos excluídos
int excluir(struct nodo** raiz, int chave) {

}

//retorna SENTINELA se não existe
struct nodo* buscar(struct nodo* raiz, int chave) {

}

void imprimirEmOrdem(struct nodo* nodo) {

}

void imprimirEmLargura(struct nodo* raiz) {

}