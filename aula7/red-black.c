#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct nodo {
    struct nodo *pai;
    struct nodo *fe;
    struct nodo *fd;
    union {
        uint64_t valor;
        uint8_t is_sentinela; // 0 indica que não é sentinela, 1 indica que é
    };
    uint8_t cor; // preto é 0, vermelho é 1
};

void rotacao_esquerda(struct nodo *raiz, struct nodo *nodo) {
    struct nodo *y = nodo->fe;
    nodo->fd = y->fe;
    if (y->fe->is_sentinela == 1) {
        y->fe->pai = nodo;
    }
    y->pai = nodo->pai;

    if (nodo->pai->is_sentinela == 1) {
        raiz = y;
    } else {
        if (nodo == nodo->pai->fe) {
            nodo->pai->fe = y;
        } else {
            nodo->pai->fd = y;
        }     
    }
    y->fe = nodo;
    nodo->pai = y;
    
    
}

int main() {

    return 0;
}