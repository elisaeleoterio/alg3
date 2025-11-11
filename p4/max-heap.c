#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "kdtree.h"
#include "max_heap.h"

// Heap Sort - Organiza o vetor de forma que esteja ordenado no estilo de uma Max-Heap
uint64_t heapSort(struct vizinho **vetor, size_t tam) {
    if (tam <= 0)
        return 0;

    // Transoforma o vetor em um max heap
    makeMaxHeap(vetor, tam);

    // Organiza os elementos em Max Heaps
    for (size_t i = tam - 1; i >= 1; i--) {
        trocar(vetor, 0, i);
        maxHeapfy(vetor, 0, i - 1);
    }
}

// Função para verificar se um vetor é uma max heap
int32_t isMaxHeap(struct vizinho **vetor, size_t tam) {
    // Itera sobre todos os nós não-folha
    for (size_t i = 0; i <= (tam - 2) / 2; i++) {
        // Índice do filho esquerdo
        size_t l = 2 * i + 1; 
        // Índice do filho direito
        size_t r = 2 * i + 2; 

        // Verifica se a distância do nó atual é maior ou igual aos seus filhos
        if (l < tam && vetor[i]->distancia < vetor[l]->distancia) {
            return 0;
        }
        if (r < tam && vetor[i]->distancia < vetor[r]->distancia) {
            return 0;
        }
    }
    return 1;
}

// Contruir uma max_heap (o elemento com a maior distância sempre estará na posição 0 do vetor) 
// Organiza o vetor de forma a se tornar uma Max Heap
// @param tam é a quantidade de elementos do vetor de vizinhos
void makeMaxHeap(struct vizinho **vetor, size_t tam) {
    for (int i = tam/2 - 1; i >= 0; i-- )
        maxHeapfy(vetor, i, tam - 1);
}

// Cria uma Max Heap
void maxHeapfy(struct vizinho **vetor, size_t a, size_t b) {
    size_t l = esquerda(a);
    size_t r = direita(a);
    size_t maior;
    
    if ((l <= b) && (vetor[l]->distancia > vetor[a]->distancia))
        maior = l;
    else
        maior = a;

    if ((r <= b) && (vetor[r]->distancia > vetor[maior]->distancia))
        maior = r;
    
    if (maior != a){
        trocar(vetor, a, maior);
        maxHeapfy(vetor, maior, b);
    }

    
}
// Função para calcular o índice do filho esquerdo de um elemento da heap
size_t esquerda(size_t i) {
    return 2 * i + 1;
}

// Função para calcular o índice do filho direito de um elemento da heap
size_t direita(size_t i) {
    return 2 * i + 2;
}

// Posiçao m do vetor recebe elemento da posição i e vice-versa
void trocar(struct vizinho **vetor, size_t m, size_t i) {
    struct vizinho *aux = vetor[m];
    vetor[m] = vetor[i];
    vetor[i] = aux;
}