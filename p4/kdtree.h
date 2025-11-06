#include <stdint.h>

#ifndef KDTREE_H_
#define KDTREE_H_

struct nodo {
    int64_t *vetchave;
    int64_t classe;
    struct nodo *fe;
    struct nodo *fd;
    struct nodo *pai;
};


// Protótipo das funções obrigatórias
struct nodo *criar_kdtree(struct nodo **raiz, uint64_t n, uint64_t k); // árvore não precisa ser balanceada
struct nodo *buscar_kdtree(struct nodo *raiz, int64_t *vetchave);
int64_t *encontrar_z_vizinhos(struct nodo *raiz, int64_t *vetchave);

// Prtótipos de funções de erro
// FUNÇÕES DE ERRO
void matarProgramaFaltaMemoria();
void matarProgramaPonteiroNulo();

#endif
