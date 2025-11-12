#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "erro.h"
#include "kdtree.h"
#include "utils.h"
#include "fila.h"
#include "max_heap.h"

/* TODO
- Ver como funciona árvore kd balanceada
- Liberar memórias alocadas
- Padronizar nomes
- Organizar arquivos
*/

struct nodo *inserir(struct nodo **raiz, double *vetchave, uint16_t classe, uint16_t dimesoes) {
    if (!vetchave) {
        matar_programa_ponteiro_nulo();
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
        // coord deve ser a mesma do último teste do while
        coord = (coord - 1 + dimesoes) % dimesoes;
        if (novo->vetchave[coord] < pai->vetchave[coord]) {
            pai->fe = novo;
        } else {
            pai->fd = novo;
        }
    }
    return novo;
}

void criar_kdtree(struct nodo **raiz, uint16_t num_nodos, uint16_t dimensoes) {
    if (!raiz) {
        matar_programa_ponteiro_nulo();
    }
    
    // Ler todos os nodos
    printf("Insira os pontos.\n");
    for (int16_t i = 0; i < num_nodos; i++) {
        double *vetchave = malloc(dimensoes * sizeof(double));
        if (!vetchave) {
            matar_programa_falta_memoria();
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

struct nodo *buscar_kdtree(struct nodo *nodo, double *vetchave, 
                            uint16_t coord, uint16_t dimensoes) {
    if (!vetchave) {
        matar_programa_ponteiro_nulo();
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
    
    // Verifica para qual lado a busca deve continuar
    if (vetchave[coord] < nodo->vetchave[coord]) {
        return buscar_kdtree(nodo->fe, vetchave, (coord + 1) % dimensoes, dimensoes);
    }
    return buscar_kdtree(nodo->fd, vetchave, (coord + 1) % dimensoes, dimensoes);
}

// Adiciona nodo ao vetor e o ordena de forma que a maior distância fique no primeiro elemento
void adiciona_ordena(struct vizinhos *vizinhos, struct nodo *nodo, double distancia, uint32_t z) {
    if (!vizinhos || !nodo) {
        matar_programa_ponteiro_nulo();
    }
    
    // Se o vetor não está cheio, vai adicionando nodos sem realizar verificações
    if (vizinhos->quantidade < z) {
        vizinhos->melhores[vizinhos->quantidade].distancia = distancia;
        vizinhos->melhores[vizinhos->quantidade].nodo = nodo;
        vizinhos->quantidade++;
    } else {// Se o vetor está com z elementos
        if (distancia < vizinhos->melhores[0].distancia) {
            // adicionar no fim do vetor, substituindo o mais distante
            vizinhos->melhores[0].distancia = distancia;
            vizinhos->melhores[0].nodo = nodo;
        }
    }
    // ordenar
    heap_sort(vizinhos->melhores, vizinhos->quantidade); // Usei o heapsort para que o maior esteja sempre no primeiro item do vetor
}

void encontrar_z_vizinhos(struct nodo *nodo, uint16_t coord, uint16_t dimensoes, 
                        double *vetchave, struct vizinhos *vizinhos, uint32_t z) {
    if (!nodo) {
        return;
    }
        
    if(!vetchave || !vizinhos) {
        matar_programa_ponteiro_nulo();
    }

    // Verifica se nodo é folha (sem filhos)
    if (nodo->fd == NULL && nodo->fe == NULL) {
        double distancia = distancia_euclidiana(nodo->vetchave, vetchave, dimensoes);   
        adiciona_ordena(vizinhos, nodo, distancia, z);
        return;
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

    encontrar_z_vizinhos(prim, (coord + 1) % dimensoes, dimensoes, vetchave, vizinhos, z);
    double distancia = distancia_euclidiana(nodo->vetchave, vetchave, dimensoes);
    adiciona_ordena(vizinhos, nodo, distancia, z);
    
    double dist_plano = fabs(nodo->vetchave[coord] - vetchave[coord]);
    double pior_dist = -1.0; // valor arbitrário para considerar como a do pior vizinho

    // Atualiza a pior distância caso o vetor esteja cheio
    if (vizinhos->quantidade == z) {
        pior_dist = vizinhos->melhores[0].distancia; 
    }
    
    // Checar o outro lado da árvore quando ela não estiver cheia ou quando a distância do plano é menor que a pior distância
    if (vizinhos->quantidade < z || dist_plano < pior_dist) {
        encontrar_z_vizinhos(sec, (coord + 1) % dimensoes, dimensoes, vetchave, vizinhos, z);
    }
    
    return;
}

void imprimir_em_largura(struct nodo *raiz, uint16_t num_nodos, uint16_t dimensoes) {
    if(!raiz) {
        matar_programa_ponteiro_nulo();
    }
    
    uint32_t tamanho = num_nodos;
    uint32_t qtd_niveis = num_nodos;

    struct fila *fila = fila_criar(tamanho);
    struct fila_nivel *fila_niv = fila_criar_nivel(qtd_niveis);

    uint16_t nivel = 0;

    enfileirar_nivel(fila_niv, nivel, qtd_niveis);
    enfileirar(fila, raiz, tamanho);

    while(fila->tamanho > 0) {
        struct nodo *nodo = fila_remove(fila);
        uint32_t nivel_nv = fila_remove_nivel(fila_niv);

        // Quebra de linha ao mudar de nível, exceto antes do primeiro nível
        if (nivel_nv != nivel && nivel_nv > 0) {
            printf("\n");
        }
        // Imprime o nível para cada nível novo
        if (nivel_nv != nivel || nivel_nv == 0) {
            printf("[%d]", nivel_nv);
        }
        nivel = nivel_nv;

        printf("( ");
        for (int16_t i = 0; i < dimensoes; i++) {
            printf("%.2f ", nodo->vetchave[i]);
        }
        printf(" ) ");
        
        if(nodo->fe != NULL) {
            enfileirar(fila, nodo->fe, tamanho);
            enfileirar_nivel(fila_niv, nivel + 1, qtd_niveis);
        }

        if(nodo->fd != NULL) {
            enfileirar(fila, nodo->fd, tamanho);
            enfileirar_nivel(fila_niv, nivel + 1, qtd_niveis);
        }
    }

    printf("\n");
    fila = fila_libera(fila);
    fila_niv = fila_libera_nivel(fila_niv);
}