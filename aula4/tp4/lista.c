#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include ""

// Implementação com lista encadeada dupla não-circular

// Definição de Structs

struct item_t
{
  struct nodo *valor ;			// valor do item
  struct item_t *ant ;		// item anterior
  struct item_t *prox ;	// próximo item
};


struct lista_t 
{
    struct item_t *prim ;	// primeiro item
    struct item_t *ult ;		// último item
    int tamanho ;		// número de itens da lista
};

// Cria uma lista vazia.
struct lista_t *lista_cria () {
    
    struct lista_t *lst;

    // Alocação dinâmica de memória
    lst = malloc(sizeof(struct lista_t));
    if (lst == NULL)
        return NULL;

    // Atribuindo valores nulos
    lst->prim = NULL;
    lst->ult = NULL;
    lst->tamanho = 0;

    return lst;
}

// Remove todos os itens da lista e libera a memória.
struct lista_t *lista_destroi (struct lista_t *lst) {
    
    if (lst == NULL)
        return NULL;
    
    struct item_t *temp;
    struct item_t *aux = lst->prim;

    while (aux != NULL) {
        temp = aux->prox;
        free(aux);
        aux = temp;
    }

    free(lst);
    lst = NULL;

    return NULL;
}

// Nas operações insere/retira/consulta/procura, a lista inicia na
// posição 0 (primeiro item) e termina na posição TAM-1 (último item).

//Operações com a lista:

// Insere o item na lista na posição indicada, sendo 0 a posição incial;
int lista_insere (struct lista_t *lst, struct nodo *item, int pos) {
    if (lst == NULL)
        return -1;

    struct item_t *nov_elem = malloc(sizeof(struct item_t));
    if (nov_elem == NULL)
        return -1;
    nov_elem->valor = item;
    
    // Quando quer colocar na primeira posição
    if (pos == 0){
        nov_elem->ant = NULL;
        nov_elem->prox = lst->prim;

        // Se tiver outros itens na lista
        if (lst->prim != NULL)
            lst->prim->ant = nov_elem;

        lst->prim = nov_elem;

        // se for uma lista só com esse elemento, o primeiro também será o último
        if (lst->ult == NULL)
            lst->ult = nov_elem;

    // Quando a posição está além dos limites do vetor
    } else if (pos < 0 || pos >= lst->tamanho) {
        // Colocar no final da lista
        nov_elem->prox = NULL;
        nov_elem->ant = lst->ult;

        if (lst->ult != NULL)
            lst->ult->prox = nov_elem;

        lst->ult = nov_elem;

        // Para quando essa inserção é para o único elemento da lista
        if (lst->prim == NULL)
            lst->prim = nov_elem;

    } else {
        struct item_t *atual;
        atual = lst->prim;

        // Percorrer a lista até achar a posição
        for (int i = 0; i < pos; i++) {
            atual = atual->prox;
        }
        nov_elem->prox = atual; 
        nov_elem->ant = atual->ant;
        if (atual->ant != NULL)
            atual->ant->prox = nov_elem;
        atual->ant = nov_elem;
    }
    (lst->tamanho)++;
    return lst->tamanho;
}

// Retira o item da lista da posição indicada.
int lista_retira (struct lista_t *lst, int *item, int pos) {
    // Quando não tem nenhum nenhum elemento ainda, logo, nada para retirar
    if (lst == NULL || item == NULL || lst->tamanho == 0)
        return -1;

    struct item_t *atual;
    // Quer retirar o elemento da primeira posição
    if (pos == 0) {
        atual = lst->prim;
        *item = atual->valor;
        lst->prim = atual->prox;

        // Caso a lista não tenha apenas um item
        if (lst->prim != NULL)
            lst->prim->ant = NULL;
        // Caso a lista tenha apenas um único elemento
        else 
            lst->ult = NULL;

    // Quando a posição está além dos limites do vetor
    } else if (pos < 0 || pos >= lst->tamanho) {
        // remover no final da lista
        atual = lst->ult;
        *item = atual->valor;
        lst->ult = atual->ant;

        // Caso a lista não tenha apenas um item
        if (lst->ult != NULL)
            lst->ult->prox = NULL;
        else
            lst->prim = NULL;

    // Remover elemento de outras posições
    } else {
        atual = lst->prim;
        // Percorrer a lista até achar a posição
        for (int i = 0; i < pos; i++) {
            atual = atual->prox;
        }
        *item = atual->valor;

        if (atual->ant != NULL)
            atual->ant->prox = atual->prox;

        if (atual->prox != NULL)
            atual->prox->ant = atual->ant;
    }       

    // Liberação do ponteiro
    free(atual);
    (lst->tamanho)--;
    
    return lst->tamanho;
}

// Informa o valor do item na posição indicada, sem retirá-lo.
int lista_consulta (struct lista_t *lst, int *item, int pos) {
    // Quando não há elementos para consulta
    if (lst == NULL || lst->tamanho == 0)
        return -1;

    // Quando a posição está além dos limites do vetor
    if (pos < 0 || pos >= lst->tamanho){
        if (lst->ult != NULL) {
            *item = lst->ult->valor;
            return -1;
        } else
            return -1;
    } else if (pos == 0) {
        // Quer consultar o primeiro valor
        *item = lst->prim->valor;
    } else {
        struct item_t *atual;
        atual = lst->prim;
        // Percorrer a lista até achar a posição que quer consultar
        for (int i= 0; i < pos; i++) {
            atual = atual->prox;
        }
        *item = atual->valor;
    }

    return lst->tamanho;
}

// Informa a posição da 1ª ocorrência do valor indicado na lista.
int lista_procura (struct lista_t *lst, int valor) {
    if (lst == NULL || lst->prim == NULL)
        return -1;

    struct item_t *atual;
    atual = lst->prim;
    // Percorre pela lista até achar o valor
    for (int i = 0; i < lst->tamanho; i++) {
        if (atual->valor == valor)
            return i;
        atual = atual->prox;
    }
    return -1;
}

// Informa o tamanho da lista (o número de itens presentes nela).
int lista_tamanho (struct lista_t *lst) {
    if (lst == NULL)
        return -1;
    return lst->tamanho;
}

// Imprime o conteúdo da lista do inicio ao fim
void lista_imprime (struct lista_t *lst) {
    if (lst == NULL || lst->tamanho == 0)
        return;
    struct item_t *atual;
    atual = lst->prim;
    for (int i = 0; i < (lst->tamanho) - 1; i++) {
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf("%d", lst->ult->valor);
}