#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int valor;
    struct nodo *pai;
    struct nodo *fe;
    struct nodo *fd;
};

void imprimir_nodo(struct nodo *nodo);

// Impressão da Árvore em Pré-Ordem
void imprime_pre_ordem(struct nodo *nodo);

// Impressão da Árvore em Ordem
void imprime_em_ordem(struct nodo *nodo);


// Impressão da Árvore em Pós-Ordem
void imprime_pos_ordem(struct nodo *nodo);

// Busca em Profundidade - busca-se os ramos mais profundos, da esqurda para a direita
struct nodo *dfs(struct nodo *no, int valor);

struct nodo *dfs_iterativo(struct nodo *nodo, int valor);