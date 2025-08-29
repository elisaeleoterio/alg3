#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <sys/queue.h>

struct nodo {
    int valor;
    struct nodo *pai;
    struct nodo *fe;
    struct nodo *fd;
};

void imprimir_nodo(struct nodo *nodo) {
    if(nodo == NULL) {
        printf("Ponteiro nulo\n");
        return;
    }
    printf("%.2f ", nodo->valor);
}

// Impressão da Árvore em Pré-Ordem
void imprime_pre_ordem(struct nodo *nodo) {
    if (nodo != NULL){
        imprimir_nodo(nodo);
        imprime_pre_ordem(nodo->fe);
        imprime_pre_ordem(nodo->fd);
    }
}

// Impressão da Árvore em Ordem
void imprime_em_ordem(struct nodo *nodo) {
    if(nodo != NULL) {
        printf("(");
        imprime_em_ordem(nodo->fe);
        imprimir_nodo(nodo);
        imprime_em_ordem(nodo->fd);
        printf(")");
    }
}


// Impressão da Árvore em Pós-Ordem
void imprime_pos_ordem(struct nodo *nodo) {
    if (nodo != NULL) {
        imprime_pos_ordem(nodo->fe);
        imprime_pos_ordem(nodo->fd);
        imprimir_nodo(nodo);
    }
}

// Busca em Profundidade - busca-se os ramos mais profundos, da esqurda para a direita
struct nodo *dfs(struct nodo *no, int valor) {
    if(no == NULL) {
        return NULL;
    }

    // Verifica se é o valor procurado
    if(no->valor == valor) {
        return no;
    }

    // Procura em um lado da árvore
    struct nodo* retorno;
    retorno = dfs(no->fe, valor);
    if(retorno) {
        return retorno;
    }

    // Procura do outro lado da árvore
    retorno = dfs(no->fd, valor);
    
    return retorno;
}

// DFS Iterativo necessita de pilha para ser implementado
/* struct nodo *dfs_iterativo(struct nodo *nodo, int valor); 
empilhar(r)
enquanto pilha não vazia
n = desempilhar()
se n.valor == v
retorne n
se n possui filho direito
empilhar(n.filhoDireito)
se n possui filho esquerdo
empilhar(n.filhoEsquerdo)
retorne não
*/

// Percurso em largura - Necessita de fila
void bfs(struct nodo *raiz) {
    enfileirar(raiz);
    while (fila_tamanho(fila) > 0) {
        struct nodo *nodo = fila_remover(fila);
        imprimir_nodo(nodo);
        if (nodo->fe != NULL) {
            fila_insere(nodo->fe);
        }
        if (nodo->fd != NULL) {
            fila_insere(nodo->fe);
        }
    }
}