#include <stdint.h>
#include <math.h>


#ifndef KDTREE_H_
#define KDTREE_H_

struct nodo { 
    float *vetchave; // Vetor com as coordenadas do ponto
    uint16_t classe; // Categoria ou rótulo do nodo
    struct nodo *fe;
    struct nodo *fd;
    struct nodo *pai;
};

// Estrutura para realizar a comparação de distancias
struct vizinho {
    float distancia;
    struct nodo *nodo;
};

struct vizinhos {
    uint16_t quantidade;
    struct vizinho *melhores;
};

struct nodo *inserir(struct nodo **raiz, float *vetchave, uint16_t classe, uint16_t dimesoes);

// Protótipo das funções obrigatórias

// árvore não balanceada
void criar_kdtree(struct nodo **raiz, uint16_t num_nodos, uint16_t dimensoes); 
// Encontra o nodo com as coordenadas ou nulo
struct nodo *buscar_kdtree(struct nodo *raiz, float *vetchave, uint16_t coord, uint16_t dimensoes);
// Altera o vetor passado como parâmetro para entregar os z vizinhos mais próximos
void encontrar_z_vizinhos(struct nodo *raiz, uint16_t coord, uint16_t dimensoes, 
                            float *vetchave, struct vizinhos *vizinhos, uint32_t z);
// Imprime a árvore seguindo a ordem dos níveis
void imprimir_em_largura(struct nodo *raiz, uint16_t num_nodos, uint16_t dimensoes);

#endif
