#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "kdtree.h"
#include "erro.h"
#include "utils.h"

// FUNÇÕES AUXILIARES
struct nodo *criar_nodo(uint16_t classe, float *vetchave) {
    
    struct nodo *nodo = malloc(sizeof(struct nodo));
    if (!nodo) {
        matar_programa_ponteiro_nulo();
    }
    nodo->fd = NULL;
    nodo->fe = NULL;
    nodo->pai = NULL;
    nodo->vetchave = vetchave;
    nodo->classe = classe;

    return nodo;
}

float *ler_pontos(uint16_t dimensoes) {
    // Aloca um vetor de dimensoes elementos de tamanho double
    float *vetchave = malloc(dimensoes * sizeof(float));
    for (size_t i = 0; i < dimensoes; i++) {
        scanf("%f", &vetchave[i]);
    }
    return vetchave;
}

float distancia_euclidiana(float *prim, float *seg, uint16_t dimensoes) {
    float distancia = 0;
    for (size_t i = 0; i < dimensoes; i++) {
        distancia = distancia + pow((prim[i] - seg[i]), 2);
    }
    distancia = sqrt(distancia);
    return distancia;
}

void imprimir_vizinhos(struct vizinhos *vizinhos, uint16_t dimesoes) {
    if (!vizinhos) {
        matar_programa_ponteiro_nulo();
    }

    printf("Vizinhos mais próximos:\n");
    // Passar por cada vizinhos
    for (uint16_t i = 0; i < vizinhos->quantidade; i++) {
        // Imprimir coordenadas
        for (uint16_t j = 0; j < dimesoes; j++) {
            printf("%.2f", vizinhos->melhores[i].nodo->vetchave[j]);
            if (j < dimesoes - 1) {
                printf(", ");
            }
        }
        // Imprimir a classe
        printf(" (classe: %hd), ", vizinhos->melhores[i].nodo->classe);
        // Imprimir distância
        printf("dist = %.2f", vizinhos->melhores[i].distancia);
        if (i < vizinhos->quantidade - 1) {
            printf("\n");
        }
        
    }
    printf(".\n");
}

void liberar_arvore(struct nodo *raiz) {
    if (!raiz) {
        return;
    }
    liberar_arvore(raiz->fe);
    liberar_arvore(raiz->fd);
    free(raiz->vetchave);
    free(raiz);
}
