#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "kdtree.h"

// struct nodo {
//     int64_t *vetchave;
//     int64_t classe;
//     struct nodo *fe;
//     struct nodo *fd;
//     struct nodo *pai;
// };


struct nodo *criar_raiz() {
    struct nodo *raiz = malloc(sizeof(struct nodo));
    if (!raiz) {
        matarProgramaFaltaMemoria();
    }
    raiz->fd = NULL;
    raiz->fe = NULL;
    raiz->pai = NULL;
    raiz->vetchave = NULL;

    return raiz;
}


// árvore não precisa ser balanceada
void criar_kdtree(struct nodo **raiz, uint64_t n, uint64_t k) {
    if (!raiz) {
        matarProgramaPonteiroNulo();
    }
    
    //Ler todos os nodos
    for (size_t i = 0; i < n; i++) {
        int64_t *vetchave = malloc(k * sizeof(int64_t));
        if (!vetchave) {
            matarProgramaFaltaMemoria();
        }
        // Ler todos os pontos do nodo
        for (size_t j = 0; j < k; i++) {
            scanf("%ld", vetchave[j]);
        }
        // Ler classe
        int64_t classe;
        scanf("%ld", &classe);
        
        // Inserir o vetor de pontos na árvore
        inserir(raiz, vetchave, classe, k);        
    }
}    
struct nodo *buscar_kdtree(struct nodo *raiz, int64_t *vetchave);
int64_t *encontrar_z_vizinhos(struct nodo *raiz, int64_t *vetchave);

// FUNÇÕES DE ERRO
void matarProgramaFaltaMemoria() {
    fprintf(stderr, "Erro por falta de memória\n");
    exit(1);
}

void matarProgramaPonteiroNulo() {
    fprintf(stderr, "Erro por ponteiro nulo\n");
    exit(1);
}

struct nodo *inserir(struct nodo **raiz, int64_t *vetchave, int64_t classe, uint64_t dimesoes) {
    int64_t coord = 0; // Indica qual coordenada do nodo está sendo analisada
    
    // Criar novo nodo e atribuir suas características
    struct nodo *novo = malloc(sizeof(struct nodo));
    if (!novo) {
        matarProgramaFaltaMemoria();
    }
    novo->classe = classe;
    novo->vetchave = vetchave;
    novo->fe = NULL;
    novo->fd = NULL;

    struct nodo *atual = raiz;
    struct nodo *pai = NULL;

    // Definir o pai do novo nodo
    while (atual) {
        pai = atual;
        if (novo->vetchave[coord] < atual->vetchave[coord]) {
            atual = atual->fe;
        } else {
            atual = atual->fd;
        }
        coord = (coord + 1) % dimesoes;
    }
    novo->pai = pai;
    if (!pai) {
        *raiz = novo;
    } else { // Definir qual lado do pai o novo nodo deve ser alocado
        if (novo->vetchave[coord] < pai->vetchave[coord]) {
            pai->fe = novo;
        } else {
            pai->fd = novo;
        }
    }
    return novo;
}