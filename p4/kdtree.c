#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "kdtree.h"

// struct nodo {
    //     int64_t *vetchave;
//     int64_t classe;
//     struct nodo *fe;
//     struct nodo *fd;
//     struct nodo *pai;
// };

// FUNÇÕES EXTRAS
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


// FUNÇÕES OBRIGATÓRIAS
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


struct nodo *buscar_kdtree(struct nodo *raiz, int64_t *vetchave, uint64_t coord, uint64_t dimensoes) {
    if (!vetchave) {
        matarProgramaPonteiroNulo();
    }
    
    if (!raiz || raiz->vetchave == NULL) {
        return raiz;
    }
    
    if (vetchave[coord] < raiz->vetchave[coord]) {
        return buscar(raiz->fe, vetchave, (coord + 1) % dimensoes, dimensoes);
    }
    return buscar(raiz->fd, vetchave, (coord + 1) % dimensoes, dimensoes);
}

int64_t *encontrar_z_vizinhos(struct nodo **raiz, uint64_t coord, uint64_t dimensoes, int64_t *vetchave) {
    if (!raiz) {
        matarProgramaPonteiroNulo();
    }
    
    if (*raiz->fd == NULL && *raiz->fe == NULL) {
        int64_t distancia = sqrt(pow())
    }
    




    função vizinhoMaisProx(r, coord, k, ponto, melhor)
        
    
    se r é folha:
            dist = ‖r - ponto‖2
            se dist < melhor.dist:
                retorne (r, dist)
            senão:
                retorne melhor
        se ponto[coord] < r.vetchave[coord]
            prim = r.fe
            sec = r.fd
        senão
            prim = r.fd
            sec = r.fe
        melhor = vizinhoMaisProx(prim,(coord+1) mod k, k, ponto, melhor)
        se ‖r - ponto‖2 < melhor.dist
            melhor = (r, dist)
        se abs(r.vetchave[coord] - ponto[coord]) < melhor.dist:
            novo = vizinhoMaisProx(sec,(coord+1) mod k, k, ponto, melhor)
            se novo.dist < melhor.dist:
                retorne novo
        retorne melhor
}



// FUNÇÕES DE ERRO
void matarProgramaFaltaMemoria() {
    fprintf(stderr, "Erro por falta de memória\n");
    exit(1);
}
    
void matarProgramaPonteiroNulo() {
    fprintf(stderr, "Erro por ponteiro nulo\n");
    exit(1);
}