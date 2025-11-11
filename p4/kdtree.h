#include <stdint.h>
#include <math.h>


#ifndef KDTREE_H_
#define KDTREE_H_

struct nodo { 
    double *vetchave; // Vetor com as coordenadas do ponto
    uint16_t classe; // Categoria ou rótulo do nodo
    struct nodo *fe;
    struct nodo *fd;
    struct nodo *pai;
};

// Estrutura para realizar a comparação de distancias
struct vizinho {
    double distancia;
    struct nodo *nodo;
};

struct vizinhos {
    uint16_t quantidade;
    struct vizinho **melhores;
};

// Protótipos de funções opcionais
struct nodo *criar_nodo(uint16_t classe, double *vetchave);
double *ler_pontos(uint16_t dimensoes);
double distancia_euclidiana(double *prim, double *seg, uint16_t dimensoes);
struct nodo *inserir(struct nodo **raiz, double *vetchave, uint16_t classe, uint16_t dimesoes);

// Protótipo das funções obrigatórias

// árvore não balanceada
void criar_kdtree(struct nodo **raiz, uint16_t num_nodos, uint16_t dimensoes); 
// Encontra o nodo com as coordenadas ou nulo
struct nodo *buscar_kdtree(struct nodo *raiz, double *vetchave, uint16_t coord, uint16_t dimensoes);
// Encontra o vizinho mais próximo da coordenada passada
struct vizinho *encontrar_z_vizinhos(struct nodo *raiz, uint16_t coord, uint16_t dimensoes, double 
                                    *vetchave, struct vizinho *melhor);
void imprimir_em_largura(struct nodo *raiz, uint16_t num_nodos, uint16_t dimensoes);

// Prtótipos de funções de erro
// FUNÇÕES DE ERRO
void matarProgramaFaltaMemoria();
void matarProgramaPonteiroNulo();

#endif
