#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "kdtree.h"

#ifndef UTILS_H_
#define UTILS_H_

struct nodo *criar_nodo(uint16_t classe, double *vetchave);
double *ler_pontos(uint16_t dimensoes);
double distancia_euclidiana(double *prim, double *seg, uint16_t dimensoes);
void imprimir_vizinhos(struct vizinhos *vizinhos, uint16_t dimesoes);
void liberar_arvore(struct nodo *raiz);

#endif