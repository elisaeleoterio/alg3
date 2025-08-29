#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct nodo {
    int valor;
    struct nodo *pai;
    struct nodo *fe;
    struct nodo *fd;
};

// Percurso em Largura
void percursoLargura(struct nodo *r, struct lista_t * list) {
    lista_insere (struct lista_t *lst, int item, int pos)

}
enquanto fila não vazia
n = removerCabeça()
imprimir(n)
se n possui filho esquerdo
enfileirar(n.filhoEsquerdo)
se n possui filho direito
enfileirar(n.filhoDireito)
retorne

// Busca em Profundidade
int depth_first_search(struct nodo *no, int valor) {
    if(no == NULL) {
        return NULL;
    }

    if(no->valor == valor) {
        return no;
    }

    struct nodo* retorno;
    retorno = dfs(no->fe, valor);
    if(retorno) {
        return retorno;
    }
    
    retorno = dfs(no->fd, valor);
    
    return retorno;
}