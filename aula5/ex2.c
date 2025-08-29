#include <stdio.h>
#include <stdlib.h>

struct nodo{
    int chave;
    struct nodo* pai;
    struct nodo* fe;
    struct nodo* fd;
};

// Inserir elemento em Árvore de Busca Binária
void inserir(struct nodo **raiz, int chave){
    
    // alocação dinâmica do novo nodo
    struct nodo *novo = malloc(sizeof(struct nodo));
    novo->chave = chave;
    novo->fe = NULL;
    novo->fd = NULL;

    if (*raiz == NULL) {
        *raiz = novo;
    }
    
    struct nodo *atual = *raiz;
    // struct para alocar o pai do elemento que está sendo analisado atualmente
    struct nodo *pai = NULL;

    // enquanto não chega ao final da árvore
    while (atual != NULL) {
        pai = atual;
        if (chave < atual->chave) { //
            atual = atual->fe;
        } else {
            atual = atual->fd;
        } 
    }

    novo->pai = pai;

    if (novo->chave < pai->chave) {
        pai->fe = novo;
    } else {
        pai->fd = novo;
    }
}

struct nodo *buscar(struct nodo *nodo, int chave) {
    if (nodo == NULL || nodo->chave == chave) {
        return nodo;
    }

    // elimina metade da árvore por iteração (se for completa/ equilibrada)
    if (chave < nodo->chave) {
        return buscar(nodo->fe, chave);
    }

    return buscar(nodo->fd, chave);
}

void em_ordem(struct nodo *nodo) {
    if (nodo != NULL) {
        em_ordem(nodo->fe);
        printf("%d ", nodo->chave);
        em_ordem(nodo->fd);
    }
}

int main() {
    struct nodo *raiz = NULL;
    
    int valor;

    printf("Valor -1 encerra a leitura e insersão.\n");
    printf("Valor a ser inserido: ");
    scanf("%d", &valor);
    printf("\n");

    inserir(&raiz, valor);
    
    while (valor != (-1)) {
        printf("Valor a ser inserido: ");
        scanf("%d", &valor);
        inserir(&raiz, valor);
    }

    em_ordem(raiz);
    
}