#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "kdtree.h"
#include "fila.h"



/* TODO
- Ver como funciona árvore kd balanceada
- Arrumar o z_vizinhos para encontrar todos os z vizinhos (sem repetir)
    - IDEIA: salvar todas as distâncias dos nodos em relação à coordenada, ordenar e retornar os z primeiros
*/

// FUNÇÕES EXTRAS
struct nodo *criar_nodo(uint16_t classe, double *vetchave) {
    struct nodo *nodo = malloc(sizeof(struct nodo));
    if (!nodo) {
        matarProgramaFaltaMemoria();
    }
    nodo->fd = NULL;
    nodo->fe = NULL;
    nodo->pai = NULL;
    nodo->vetchave = vetchave;
    nodo->classe = classe;

    return nodo;
}

double *ler_pontos(uint16_t dimensoes) {
    double *vetchave = malloc(dimensoes * sizeof(double));
    printf("Escreva as coordenadas.\n");
    for (size_t i = 0; i < dimensoes; i++) {
        scanf("%lf", &vetchave[i]);
    }
    return vetchave;
}

double distancia_euclidiana(double *prim, double *seg, uint16_t dimensoes) {
    double distancia = 0;
    for (size_t i = 0; i < dimensoes; i++) {
        distancia = distancia + pow((prim[i] - seg[i]), 2);
    }
    distancia = sqrt(distancia);
    return distancia;
}

struct nodo *inserir(struct nodo **raiz, double *vetchave, uint16_t classe, uint16_t dimesoes) {
    // Indica qual coordenada do nodo está sendo analisada
    uint16_t coord = 0; 
    
    // Criar novo nodo e atribuir suas características
    struct nodo *novo = criar_nodo(classe, vetchave);
    printf("Criou o nodo\n");
    printf("Nodo vetchave[0]: %f\n", novo->vetchave[0]);

    // Estruturas auxiliares para definir local de inserção
    struct nodo *atual = *raiz;
    struct nodo *pai = NULL;

    // Loop para definir o pai do novo nodo
    while (atual->vetchave) {
        printf("Entrou no while\n");
        pai = atual;
        printf("Antes do if\n");
        // Atual->vetchave[coord] pode ser nulo (raiz)
        
        if (novo->vetchave[coord] < atual->vetchave[coord]) {
            printf("Entrou no if\n");
            atual = atual->fe;
        } else {
            printf("Entrou no else\n");
            atual = atual->fd;
        }
        coord = (coord + 1) % dimesoes;
        printf("Coord: %d\n", coord);
    }
    novo->pai = pai;

    // Condições para definir qual filho (fe ou fd) o novo nodo é
    if (pai->vetchave == NULL) {
        printf("Entrou no if da raiz.\n");
        *raiz = novo;
    } else { 
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
void criar_kdtree(struct nodo **raiz, uint16_t num_nodos, uint16_t dimensoes) {
    if (!raiz) {
        matarProgramaPonteiroNulo();
    }
    
    //Ler todos os nodos
    printf("Insira os pontos.\n");
    for (int16_t i = 0; i < num_nodos; i++) {
        double *vetchave = malloc(dimensoes * sizeof(double));
        if (!vetchave) {
            matarProgramaFaltaMemoria();
        }

        // Ler todos os pontos do nodo
        vetchave = ler_pontos(dimensoes);

        // Ler classe
        uint16_t classe;
        printf("Classe: ");
        scanf("%hd", &classe);
        
        // Inserir o vetor de pontos na árvore
        printf("Antes do inserir\n");
        inserir(raiz, vetchave, classe, dimensoes);
        printf("Ponto %d lido.\n", i);      
    }
}    

// Encontra o nodo que possui a coordenada parâmetro ou retorna nulo
struct nodo *buscar_kdtree(struct nodo *nodo, double *vetchave, uint16_t coord, uint16_t dimensoes) {
    if (!vetchave) {
        matarProgramaPonteiroNulo();
    }
    
    if (!nodo || nodo->vetchave == NULL) {
        return nodo;
    }
    
    if (vetchave[coord] < nodo->vetchave[coord]) {
        return buscar_kdtree(nodo->fe, vetchave, (coord + 1) % dimensoes, dimensoes);
    }
    return buscar_kdtree(nodo->fd, vetchave, (coord + 1) % dimensoes, dimensoes);
}

// Retorna um vetor com os z vizinhos mais próximos
struct vizinho *encontrar_z_vizinhos(struct nodo *nodo, uint16_t coord, uint16_t dimensoes, 
                                    double *vetchave, struct vizinho *melhor) {
    if (!nodo) {
        matarProgramaPonteiroNulo();
    }
    
    // Verifica se nodo é folha (sem filhos)
    if (nodo->fd == NULL && nodo->fe == NULL) {
        double distancia = distancia_euclidiana(nodo->vetchave, vetchave, dimensoes);

        if (distancia < melhor->distancia) {
            struct vizinho *ret = malloc(sizeof(struct vizinho));
            if (!ret) {
                matarProgramaFaltaMemoria();
            }
            ret->distancia = distancia;
            ret->nodo = nodo;
            return ret;
        } else {
            return melhor;
        }
    }

    struct nodo *prim, *sec;
    if (vetchave[coord] < nodo->vetchave[coord]) {
        prim = nodo->fe;
        sec = nodo->fd;    
    } else {
        prim = nodo->fd;
        sec = nodo->fe;
    }

    melhor = encontrar_z_vizinhos(prim, (coord + 1) % dimensoes, dimensoes, vetchave, melhor);
    double distancia = distancia_euclidiana(nodo->vetchave, vetchave, dimensoes);
    if (distancia < melhor->distancia) {
        melhor->distancia = distancia;
        melhor->nodo = nodo;
    }
    if (fabs(nodo->vetchave[coord] - vetchave[coord]) < melhor->distancia) {
        struct vizinho *novo = encontrar_z_vizinhos(sec, (coord + 1) % dimensoes, dimensoes, vetchave, melhor);
        if (novo->distancia < melhor->distancia) {
            return novo;
        }
    }
    return melhor;
}

void imprimir_em_largura(struct nodo *raiz, uint16_t num_nodos, uint16_t dimensoes) {
    if(!raiz) {
        matarProgramaPonteiroNulo();
    }
    
    uint32_t tamanho = num_nodos;

    struct fila *fila = fila_criar(tamanho);

    enfileirar(fila, raiz, tamanho);
    while(fila->tamanho > 0) {
        struct nodo *nodo = fila_remove(fila);
        for (int16_t i = 0; i < dimensoes; i++) {
            printf("%f", nodo->vetchave[i]);
            if (i < dimensoes - 1) {
                printf(" ");
            } 
        }
        

        if(nodo->fe != NULL) {
            enfileirar(fila, nodo->fe, tamanho);
        }

        if(nodo->fd != NULL) {
            enfileirar(fila, nodo->fd, tamanho);
        }
    }

    printf("\n");
    fila = fila_libera(fila);
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