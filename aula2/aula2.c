#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 50
#define TAM_DICT 20

// Struct de árvore binária
struct nodo{
    struct pessoa *pessoa;
    struct nodo* f1;
    struct nodo* f2;
};

struct pessoa {
    char nome[MAX_CHAR];
    uint16_t idade;
    uint64_t cpf;
};