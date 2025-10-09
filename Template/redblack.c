#include "trataErro.c"
#include "redblack.h"
#include "fila.c"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>


/*
PERGUNTAS:
1. Preciso imprimir o sentinela ao imprimir em Largura?
2. O sentinela->pai pode apontar para qualquer lugar ou deve ser para outro sentinela?
3. Ao excluir, preciso retornar um inteiro que é a quantidade de nodos excluidos, mas 
não posso adicionar nodos com valores repetidos, então sempre retorno 0 ou 1, certo?
*/

//implementação das FUNÇÕES RED BLACK

// Aloca dinâmicamente um nodo e o retorna
struct nodo *criaNodo(int valor) {
    struct nodo *nodo = malloc(sizeof(struct nodo));
    if (!nodo) {
        matarProgramaFaltaMemoria();
    }

    nodo->chave = valor;
    nodo->cor = 1;
    nodo->fd = sentinela;
    nodo->fe = sentinela;
    nodo->pai = sentinela;   
    
    return nodo;
}

// Subárvore nodoB toma o lugar da subárvore nodoA (nodoA continua a apontar para nodoA->pai)
void transplante(struct nodo **raiz, struct nodo *nodoA, struct nodo *nodoB) {
    if (!raiz || !nodoA || !nodoB) {
        matarProgramaPonteiroNulo();
    }

    if (nodoA->pai == sentinela) {
        *(raiz) = nodoB;
    } else {
        if (nodoA == nodoA->pai->fe) {
            nodoA->pai->fe = nodoB;
        } else {
           nodoA->pai->fd = nodoB;
        }      
    }
    nodoB->pai = nodoA->pai;
}

// o nodo x é rotacionado a esquerda
void rotacaoEsquerda(struct nodo **raiz, struct nodo *nodo) {
    if (!raiz || !nodo) {
        matarProgramaPonteiroNulo();
    }
    
    struct nodo *aux = nodo->fd;
    nodo->fd = aux->fe;

    if (aux->fe != sentinela) {
        aux->fe->pai = nodo;
    }
    aux->pai = nodo->pai;
    if (nodo->pai == sentinela) {
        *raiz = aux;
    } else {
        if (nodo == nodo->pai->fe) {
            nodo->pai->fe = aux;
        } else {
            nodo->pai->fd = aux;
        }
    }
    aux->fe = nodo;
    nodo->pai = aux;
}

// o nodo x é rotacionado a direita
void rotacaoDireita(struct nodo **raiz, struct nodo *nodo) {
    // Verificação de ponteiros
    if (!raiz || !nodo) {
        matarProgramaPonteiroNulo();
    }

    struct nodo *aux = nodo->fe;
    nodo->fe = aux->fd;
    if (aux->fd != sentinela) {
        aux->fd->pai = nodo;
    }

    aux->pai = nodo->pai;
    // Nodo é a raiz da árvore
    if (nodo->pai == sentinela) {
        *raiz = aux;
    } else {
        
        if (nodo == nodo->pai->fd) {
            nodo->pai->fd = aux;
        } else {
            nodo->pai->fe = aux;
        }
    }

    aux->fd = nodo;
    nodo->pai = aux;
}

// // Altera a árvore para manter as características da Red Black após uma inserção
void insereFix(struct nodo **raiz, struct nodo *nodo) {
    if(!*raiz || !nodo) {
        matarProgramaPonteiroNulo();
    }

    while (nodo->pai->cor) {
        // O pai do nodo inserido é um filho esquerdo
        if (nodo->pai == nodo->pai->pai->fe) {
            struct nodo *tio = nodo->pai->pai->fd; 
            if (tio->cor) {
                nodo->pai->cor = 0;
                tio->cor = 0;
                nodo->pai->pai->cor = 1;
                nodo = nodo->pai->pai;
            } else {
                if (nodo == nodo->pai->fd) {
                    nodo = nodo->pai;
                    rotacaoEsquerda(raiz, nodo);
                }
                nodo->pai->cor = 0;
                nodo->pai->pai->cor = 1;
                rotacaoDireita(raiz, nodo->pai->pai);
            }
        // O pai do nodo inserido é um filho direito
        } else {
            struct nodo *tio = nodo->pai->pai->fe;
            if (tio->cor) {
                nodo->pai->cor = 0;
                tio->cor = 0;
                nodo->pai->pai->cor = 1;
                nodo = nodo->pai->pai;
            } else {
                if (nodo == nodo->pai->fe) {
                    nodo = nodo->pai;
                    rotacaoDireita(raiz, nodo);
                }
                nodo->pai->cor = 0;
                nodo->pai->pai->cor = 1;
                rotacaoEsquerda(raiz, nodo->pai->pai);
            }
        }
    }
    (*raiz)->cor = 0;
}

// Altera a árvore para manter as características da Red Black após uma exclusão
void deleteFix(struct nodo **raiz, struct nodo *nodo) {
    if (!raiz || !nodo) {
        matarProgramaPonteiroNulo();
    }
    
    while (nodo != *raiz && !nodo->cor) {
        struct nodo *aux;
        // O nodo é um filho esquerdo
        if (nodo == nodo->pai->fe) {
            aux = nodo->pai->fd;
            if (aux != sentinela) {
                
                if (aux->cor) {
                    aux->cor = 0;
                    nodo->pai->cor = 1;
                    rotacaoEsquerda(raiz, nodo->pai);
                    aux = nodo->pai;
                }
    
                if (!aux->fe->cor && !aux->fd->cor) {
                    aux->cor = 1;
                    nodo = nodo->pai;
                }   else {
                    if (!aux->fd->cor) {
                        aux->fe->cor = 0;
                        aux->cor = 1;
                        rotacaoDireita(raiz, aux);
                        aux = nodo->pai->fd;
                    }
    
                    aux->cor = nodo->pai->cor;
                    nodo->pai->cor = 0;
                    aux->fd->cor = 0;
                    rotacaoEsquerda(raiz, aux->pai);
                    nodo = *raiz;
                }     
            }
        }
        // Nodo é um filho direito
        else if (nodo == nodo->pai->fd) {
            aux = nodo->pai->fe;
            if (aux != sentinela) {
                
                if (aux->cor) {
                    aux->cor = 0;
                    nodo->pai->cor = 1;
                    rotacaoDireita(raiz, nodo->pai);
                    aux = nodo->pai;
                }
    
                if (!aux->fe->cor && !aux->fd->cor) {
                    aux->cor = 1;
                    nodo = nodo->pai;
                }   else {
                    if (!aux->fe->cor) {
                        aux->fd->cor = 0;
                        aux->cor = 1;
                        rotacaoEsquerda(raiz, aux);
                        aux = nodo->pai->fe;
                    }
    
                    aux->cor = nodo->pai->cor;
                    nodo->pai->cor = 0;
                    aux->fe->cor = 0;
                    rotacaoDireita(raiz, aux->pai);
                    nodo = *raiz;
                }
            }
        }
    }
    nodo->cor = 0;
}

//retorna SENTINELA se não foi possível inserir
struct nodo* inserir(struct nodo **raiz, int chave) {
    if(!*raiz) {
        matarProgramaPonteiroNulo();
    }

    // Não pode inserir uma chave duplicada
    if(buscar(*raiz, chave) != sentinela) {
        printf("Chave repetida.\n");
        return sentinela;
    }
    
    struct nodo *novo_nodo = criaNodo(chave);
    struct nodo *x = *raiz;
    struct nodo *y = sentinela;

    while (x != sentinela) {
        y = x;
        if (novo_nodo->chave < x->chave) {
            x = x->fe;
        } else {
            x = x->fd;
        }        
    }

    novo_nodo->pai = y;
    if (y == sentinela) {
        *raiz = novo_nodo;
    } else {
        if (novo_nodo->chave < y->chave) {
            y->fe = novo_nodo;
        } else {
            y->fd = novo_nodo;
        }
    }
    insereFix(raiz, novo_nodo);
    return novo_nodo;
}


struct nodo *minimo(struct nodo *raiz) {
    if (!raiz) {
        matarProgramaPonteiroNulo();
    }
    
    struct nodo *min = raiz;
    while(min->fe != sentinela) {
        min = min->fe;
    }

    return min;
}

// retorna o número de nodos excluídos
int excluir(struct nodo **raiz, int chave) {
    // Verificação de ponteiros
    if (!*raiz) {
        matarProgramaPonteiroNulo();
    }

    struct nodo *remover = buscar(*raiz, chave);
    int removidos = 0;

    // equanto houver um nodo com essa chave (a busca não retorna o sentinela)
    while (remover != sentinela) {
        struct nodo *aux = remover;
    
        int corOg = aux->cor;
        struct nodo *temp;
    
        if (remover->fe == sentinela) {
            temp = remover->fd;
            transplante(raiz, remover, remover->fd);
        } else {
            if (remover->fd == sentinela) {
                temp = remover->fe;
                transplante(raiz, remover, remover->fe);
            } else {
                aux = minimo(remover->fd);
                corOg = aux->cor;
                temp = aux->fd;
                if (aux != remover->fd) {
                    transplante(raiz, aux, aux->fd);
                    aux->fd = remover->fd;
                    aux->fd->pai = aux;
                } else {
                    temp->pai = aux;
                }
                transplante(raiz, remover, aux);
                aux->fe = remover->fe;
                aux->fe->pai = aux;
                aux->cor = remover->cor;
            }
        }
        if (!corOg) {
            deleteFix(raiz, temp);
        }
        free(remover);
        removidos++;
        remover = buscar(*raiz, chave);
    }

    return removidos;
}

//retorna SENTINELA se não existe
struct nodo* buscar(struct nodo* nodo, int chave) {
    if (!nodo) {
        matarProgramaPonteiroNulo();
    }
    
    if (nodo == sentinela || nodo->chave == chave) {
        return nodo;
    }

    if (chave < nodo->chave) {
        return buscar(nodo->fe, chave);
    }

    return buscar(nodo->fd, chave);
}

void imprimirEmOrdem(struct nodo* nodo) {
    if (nodo != sentinela) {
        imprimirEmOrdem(nodo->fe);
        printf("Chave: %d.\n", nodo->chave);
        imprimirEmOrdem(nodo->fd);
    }
}

uint32_t contarElementos(struct nodo *raiz) {
    if(raiz == sentinela) {
        return 0;
    }

    return 1 + contarElementos(raiz->fe) + contarElementos(raiz->fd);
}


void imprimirEmLargura(struct nodo* raiz) {
    if(!raiz) {
        matarProgramaPonteiroNulo();
    }
    
    uint32_t tamanho = contarElementos(raiz);
    printf("Tamanho: %d\n", tamanho);

    struct fila *fila = filaCriar(tamanho);

    enfileirar(fila, raiz, tamanho);
    while(fila->tamanho > 0) {
        struct nodo *nodo = filaRemove(fila);
        printf("Chave: %d.\n", nodo->chave);
        if (nodo->cor) {
            printf("Cor: vermelho\n.");
        } else {
            printf("Cor: preto.\n");
        }
        
        if(nodo->fe != sentinela) {
            enfileirar(fila, nodo->fe, tamanho);
        }

        if(nodo->fd != sentinela) {
            enfileirar(fila, nodo->fd, tamanho);
        }
    }
}
