#include "redblack.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>


// FUNÇÕES DE ERRO
void matarProgramaFaltaMemoria() {
    fprintf(stderr, "Erro por falta de memória\n");
    exit(1);
}

void matarProgramaPonteiroNulo() {
    fprintf(stderr, "Erro por ponteiro nulo\n");
    exit(1);
}

// FUNÇÕES ALUNO
struct aluno* getAluno(){
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if(!retorno)
        matarProgramaFaltaMemoria();

    retorno->nome = malloc(sizeof("Elisa Rocha Eleotério"));//sizeof conta o \0
	if(!retorno->nome)
		matarProgramaFaltaMemoria();
        
    retorno->nomeDinf = malloc(sizeof("ere24"));
    if(!retorno->nomeDinf) {
        matarProgramaFaltaMemoria();
    }
    
	strcpy(retorno->nome, "Elisa Rocha Eleotério");
    strcpy(retorno->nomeDinf, "ere24");
    retorno->grr = 20241731;

	return retorno;
}

void imprimirDadosAluno(){
    struct aluno* aluno = getAluno();
    
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    return;
}

//FUNÇÕES RED BLACK

void iniciaSentinela() {
    if (sentinela == NULL) {
        sentinela = malloc(sizeof(struct nodo));
        if (!sentinela) {
            matarProgramaFaltaMemoria();
        }
    }

    sentinela->chave = -1;
    sentinela->cor = 0;
    sentinela->fd = sentinela;
    sentinela->fe = sentinela;
    sentinela->pai = sentinela;
}

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

// Subárvore nodoB toma o lugar da subárvore nodoA
void transplante(struct nodo *raiz, struct nodo *nodoA, struct nodo *nodoB) {
    if (!raiz || !nodoA || !nodoB) {
        matarProgramaPonteiroNulo();
    }

    if (nodoA->pai == sentinela) {
        raiz = nodoB;
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
    
    // Verifica se o filho do nodo é sentinela
    if (nodo->fd == sentinela) {
        printf("Nodo é sentinela\n");
        exit(1);
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
    
    // Verifica se o filho do nodo é sentinela
    if (nodo->fe == sentinela) {
        printf("Nodo é sentinela\n");
        exit(1);
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
    // Verifica ponteiros
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
    // Verificação dos ponteiros
    if (!raiz || !nodo) {
        matarProgramaPonteiroNulo();
    }
    
    while (nodo != *raiz && !nodo->cor) {
        struct nodo *aux;
        // O nodo é um filho esquerdo
        if (nodo == nodo->pai->fe) {
            aux = nodo->pai->fd;
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
        // Nodo é um filho direito
        if (nodo == nodo->pai->fd) {
            aux = nodo->pai->fe;
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
int excluir(struct nodo** raiz, int chave) {
    // Verificação de ponteiros
    if (!*raiz) {
        matarProgramaPonteiroNulo();
    }

    struct nodo *remover = buscar(*raiz, chave);
    int removidos = 0;

    // equanto houver um nodo com essa chave (a busca não retorna o sentinela)
    while (remover->cor != -1) {
        struct nodo *aux = remover;
    
        int corOg = aux->cor;
        struct nodo *temp;
    
        if (remover->fe == sentinela) {
            temp = remover->fd;
            transplante(*raiz, remover, remover->fd);
        } else {
            if (remover->fd == sentinela) {
                temp = remover->fe;
                transplante(*raiz, remover, remover->fe);
            } else {
                aux = minimo(remover->fd);
                corOg = aux->cor;
                temp = aux->fd;
                if (aux != remover->fd) {
                    transplante(*raiz, aux, aux->fd);
                    aux->fd = remover->fd;
                    aux->fd->pai = aux;
                } else {
                    temp->pai = aux;
                }
                transplante(*raiz, remover, aux);
                aux->fe = remover->fe;
                aux->fe->pai = aux;
                aux->cor = remover->cor;
            }
        }
        if (!corOg) {
            deleteFix(raiz, temp);
        }
    }
    removidos++;
    remover = buscar(*raiz, chave);

    return removidos;
}

// //retorna SENTINELA se não existe
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

// Preciso imprimir a sentinela??
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

// FUNÇÕES FILA
struct fila {
    struct nodo **nodos; // vetor de ponteiros para os nodos
    uint32_t tamanho;
};

// Aloca dinâmicamente a fila e os nodos e seta o tamanho para 0
struct fila *filaCriar(uint32_t tamanho) {
    struct fila *fila = malloc(sizeof(struct fila));
    if(!fila) {
        matarProgramaPonteiroNulo();
    }

    fila->nodos = malloc(tamanho * sizeof(struct nodo*));
    if(!fila->nodos) {
        free(fila);
        matarProgramaFaltaMemoria();
    }

    fila->tamanho = 0;
    return fila;
}

// Adiciona o nodo no final da fila
void enfileirar(struct fila *fila, struct nodo *nodo, uint32_t tamanho) {
    if(!fila || !nodo) {
        matarProgramaPonteiroNulo();
    }

    if(fila->tamanho == tamanho) {
        printf("Capacidade da fila atingido\n");
        return;
    }

    fila->nodos[fila->tamanho] = nodo;
    fila->tamanho++;
}

// Remove o primeiro item da fila e o retorna
struct nodo *filaRemove(struct fila *fila) {
    if(!fila) {
        matarProgramaPonteiroNulo();
    }

    if(!fila->tamanho) {
        printf("Fila vazia.\n");
        return NULL;
    }

    struct nodo *retirado = fila->nodos[0];

    for(size_t i = 1; i < fila->tamanho; i++) {
        fila->nodos[i - 1] = fila->nodos[i];
    }

    fila->tamanho--;
    return retirado;
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
