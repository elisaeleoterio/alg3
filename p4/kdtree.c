#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "kdtree.h"
#include "fila.h"
#include "max_heap.h"



/* TODO
- Ver como funciona árvore kd balanceada
- Arrumar o z_vizinhos para encontrar todos os z vizinhos (sem repetir)
    - IDEIA: salvar todas as distâncias dos nodos em relação à coordenada, ordenar e retornar os z primeiros
*/

// FUNÇÕES AUXILIARES
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
    if (!(*raiz) || !vetchave) {
        matarProgramaPonteiroNulo();
    }
    
    // Indica qual coordenada do nodo está sendo analisada
    uint16_t coord = 0; 
    
    // Criar novo nodo e atribuir suas características
    struct nodo *novo = criar_nodo(classe, vetchave);

    // Estruturas auxiliares para definir local de inserção
    struct nodo *atual = *raiz;
    struct nodo *pai = NULL;

    // Loop para definir o pai do novo nodo
    // Atual->vetchave[coord] pode ser nulo (raiz)
    while (atual && atual->vetchave) {
        pai = atual;
        if (novo->vetchave[coord] < atual->vetchave[coord]) {
            atual = atual->fe;
        } else {
            atual = atual->fd;
        }
        coord = (coord + 1) % dimesoes;
    }
    novo->pai = pai;

    // Condições para definir qual filho (fe ou fd) o novo nodo é
    if (pai == NULL) {
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
    
    printf("Insira os pontos.\n");
    //Ler todos os nodos
    for (int16_t i = 0; i < num_nodos; i++) {
        double *vetchave = malloc(dimensoes * sizeof(double));
        if (!vetchave) {
            matarProgramaFaltaMemoria();
        }

        // Ler todos os pontos do nodo
        vetchave = ler_pontos(dimensoes);

        // Ler classe
        uint16_t classe;
        scanf("%hd", &classe);
        
        // Inserir o vetor de pontos na árvore
        inserir(raiz, vetchave, classe, dimensoes);
    }
}    

// Encontra o nodo que possui a coordenada parâmetro ou retorna nulo
struct nodo *buscar_kdtree(struct nodo *nodo, double *vetchave, uint16_t coord, uint16_t dimensoes) {
    if (!vetchave) {
        matarProgramaPonteiroNulo();
    }
    
    if (!nodo) {
        return nodo;
    }

    // Verificar se vetchaves são iguais
    int igual = 1;
    for (size_t i = 0; i < dimensoes; i++) {
        if (nodo->vetchave[i] != vetchave[i]) {
            igual = 0;
        }
    }
    
    if (igual) {
        return nodo;
    }
    
    if (vetchave[coord] < nodo->vetchave[coord]) {
        return buscar_kdtree(nodo->fe, vetchave, (coord + 1) % dimensoes, dimensoes);
    }
    return buscar_kdtree(nodo->fd, vetchave, (coord + 1) % dimensoes, dimensoes);
}


// COLOCAR NA MAIN
// // Alocação dinâmica do vetor que armazenará os z vizinhos mais próximos
//     struct vizinhos *vizinhos = malloc(sizeof(struct vizinhos));
//     if (!vizinhos) {
//         matarProgramaFaltaMemoria();
//     }
//     vizinhos->melhores = malloc(z * sizeof(struct vizinho));
//     vizinhos->quantidade = 0;
// Retorna um vetor com os z vizinhos mais próximos
struct vizinhos *encontrar_z_vizinhos(struct nodo *nodo, uint16_t coord, uint16_t dimensoes, 
                                    double *vetchave, struct vizinhos *vizinhos, uint32_t z) {
    if (!nodo || !vetchave || !vizinhos) {
        matarProgramaPonteiroNulo();
    }

    // Alterar lógica de comparação para que compare com o vizinho mais distante
    // Quando achar um vizinho mais próximo, verificar se o vetor está cheio
        // Se estiver tirar o mais distante e subtituir pelo novo e ordenar novamente
        // Se não estiver cheio, adicionar no vetor

    // Verifica se nodo é folha (sem filhos)
    if (nodo->fd == NULL && nodo->fe == NULL) {
        double distancia = distancia_euclidiana(nodo->vetchave, vetchave, dimensoes);
        if (vizinhos->quantidade > 0) {
            if (distancia < vizinhos->melhores[0]->distancia) {
                adiciona_ordena(vizinhos, nodo, distancia, z);
            }
        }
        return vizinhos;
    }

    // Define para qual lado da árvore irá continuar a procura
    struct nodo *prim, *sec;
    if (vetchave[coord] < nodo->vetchave[coord]) {
        prim = nodo->fe;
        sec = nodo->fd;    
    } else {
        prim = nodo->fd;
        sec = nodo->fe;
    }

    vizinhos = encontrar_z_vizinhos(prim, (coord + 1) % dimensoes, dimensoes, vetchave, vizinhos, z);
    double distancia = distancia_euclidiana(nodo->vetchave, vetchave, dimensoes);
    if (vizinhos->quantidade < z) {
        if (distancia < vizinhos->melhores[0]->distancia) {
            adiciona_ordena(vizinhos, nodo, distancia, z);
        }
    }
    
    double dist_plano = nodo->vetchave[coord] - vetchave[coord];
    double pior_dist = -1.0; // valor arbitrário para considerar como a do pior vizinho

    // Atualiza a pior distância caso o vetor esteja cheio
    if (vizinhos->quantidade == z) { // vetor de vizinhos está cheio
        pior_dist = vizinhos->melhores[0]->distancia; 
    }
    

    // Checar o outro lado da árvore quando ela não estiver cheia ou quando a distância do plano é menor que a pior distância
    if (vizinhos->quantidade < z || dist_plano < pior_dist) {
        encontrar_z_vizinhos(sec, (coord + 1) % dimensoes, dimensoes, vetchave, vizinhos, z);
    }
    
    return vizinhos;
}

void adiciona_ordena(struct vizinhos *vizinhos, struct nodo *nodo, double distancia, uint32_t z) {
    if (vizinhos->quantidade == z) { // Substituir o mais distante
        vizinhos->melhores[0]->distancia = distancia;
        vizinhos->melhores[0]->nodo = nodo;
    } else { // adicionar no fim do vetor
        vizinhos->melhores[vizinhos->quantidade]->distancia = distancia;
        vizinhos->melhores[vizinhos->quantidade]->nodo = nodo;
        vizinhos->quantidade++;
    }
    // ordenar
    heapSort(vizinhos->melhores, vizinhos->quantidade); // Usei o heapsort para que o maior esteja sempre no primeiro item do vetor
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
        printf("( ");
        for (int16_t i = 0; i < dimensoes; i++) {
            printf("%.2f ", nodo->vetchave[i]);
        }
        printf(" ) ");
        

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