#include "redblack.h"

#include <stdlib.h>
#include <string.h>

struct aluno* getAluno(){
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if(!retorno)
        matarProgramaFaltaMemoria();

    retorno->nome = malloc(sizeof("SEU_NOME"));//sizeof conta o \0
	if(!retorno->nome)
		matarProgramaFaltaMemoria();
        
    retorno->nomeDinf = malloc(sizeof("NOME_NAS_SERVIDORAS_DINF"));
    if(!retorno->nomeDinf)
        matarProgramaFaltaMemoria();
    
	strcpy(retorno->nome, "SEU_NOME");
    strcpy(retorno->nomeDinf, "NOME_NAS_SERVIDORAS_DINF");
    retorno->grr = 1234;

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

// subárvore nodoB toma o lugar da subárvore nodoA
void transplante(struct nodo *raiz, struct nodo *nodoA, struct nodo *nodoB) {

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