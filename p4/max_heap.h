#include <stdint.h>
#include <math.h>

#ifndef MAXHEAP_H_
#define MAXHEAP_H_

// Heap Sort - Organiza o vetor de forma que esteja ordenado no estilo de uma Max-Heap
void heap_sort(struct vizinho *vetor, size_t tam);
// Função para verificar se um vetor é uma max heap
int32_t is_max_heap(struct vizinho *vetor, size_t tam);


#endif