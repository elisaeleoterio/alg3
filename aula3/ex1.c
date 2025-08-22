#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TAM 100
struct nodo {
    union {
        char *operacao;
        float valor;
    };
    int tipo; // 1 indica operação, 0 indica valor
    struct nodo *pai;
    struct nodo *fe;
    struct nodo *fd;
};

void imprimir_nodo(struct nodo *nodo) {
    if(nodo == NULL) {
        printf("Ponteiro nulo\n");
        return;
    }

    // Imprimir informação de acordo com o tipo do elemento armazenado
    if(nodo->tipo == 1) {
        printf("%s ", nodo->operacao);
        return;
    }

    if (nodo->tipo == 0) {
        printf("%.2f ", nodo->valor);
        return;
    }
}

void imprime_pre_ordem(struct nodo *nodo) {
    if (nodo != NULL){
        imprimir_nodo(nodo);
        imprime_pre_ordem(nodo->fe);
        imprime_pre_ordem(nodo->fd);
    }
}

void imprime_em_ordem(struct nodo *nodo) {
    if(nodo != NULL) {
        printf("(");
        imprime_em_ordem(nodo->fe);
        imprimir_nodo(nodo);
        imprime_em_ordem(nodo->fd);
        printf(")");
    }
}

void imprime_pos_ordem(struct nodo *nodo) {
    if (nodo != NULL) {
        imprime_pos_ordem(nodo->fe);
        imprime_pos_ordem(nodo->fd);
        imprimir_nodo(nodo);
    }
}

struct nodo *libera(struct nodo *nodo) {
    if (nodo == NULL) {
        printf("Ponteiro nulo\n");
        return NULL;
    }

    if (nodo->tipo == 1 && nodo->operacao != NULL) {
        // liberar char*
        free(nodo->operacao);
    }

    free(nodo);
    return NULL;
}

void libera_pos_ordem(struct nodo *nodo) {
    if(nodo != NULL) {
        libera_pos_ordem(nodo->fe);
        libera_pos_ordem(nodo->fd);
        libera(nodo);
    }
}


void insere(struct nodo *raiz, char *exp) {
    
    exp[strcspn(exp, "\n")] = '\0';

    printf("Expressão: %s\n", exp);
    // separar string em tokens
    const char *delim = " "; // delimitadores do fim de um elemento espaço
    char *token = strtok(exp, delim);

    struct nodo *aux = raiz;
    
    // verifica se é o fim da expressão
    while (token != NULL) {
        if(*token == '+' || *token == '-' || *token == '*' || *token == '/') {
            printf("Operação: %s\n", token);
            aux->tipo = 1;
            aux->operacao = malloc(strlen(token) + 1);
            strcpy(aux->operacao, token);

            if(aux->fe == NULL) {
                aux->fe = malloc(sizeof(struct nodo));
                aux->fe->pai = aux;
                aux->fe->fe = NULL;
                aux->fe->fd = NULL;
                aux = aux->fe;
            } else if (aux->fd == NULL) {
                    aux->fd = malloc(sizeof(struct nodo));
                    aux->fd->pai = aux;
                    aux->fd->fe = NULL;
                    aux->fd->fd = NULL;
                    aux = aux->fd;
            }
        } else {
            // define o tipo do elemento
            aux->tipo = 0;

            // transforma o token em float
            double nov_tok = atof(token);
            
            // salva o elemento no nodo
            aux->valor = nov_tok;

            printf("Valor: %f\n", nov_tok);

            // Navegar para próxima posição
            struct nodo *atual = aux;
            while(atual->pai != NULL) {
                struct nodo *pai = atual->pai;
                
                // Se sou filho esquerdo e pai não tem filho direito
                if(pai->fe == atual && pai->fd == NULL) {
                    pai->fd = malloc(sizeof(struct nodo));
                    pai->fd->pai = pai;
                    pai->fd->fe = NULL;
                    pai->fd->fd = NULL;
                    aux = pai->fd;
                    break;
                }
                // Se sou filho direito ou pai já tem ambos filhos, subir mais
                atual = pai;
            }
        }
        token = strtok(NULL, delim);
    }
}

double calcula(struct nodo *nodo) {
    // elemento é um operador
    if (nodo->tipo == 1) {
        if (*nodo->operacao == '+') {
            return (calcula(nodo->fe) + calcula(nodo->fd));
        } 
        if (*nodo->operacao == '-') {
            return (calcula(nodo->fe) - calcula(nodo->fd));
        }
        if (*nodo->operacao == '/') {
            return (calcula(nodo->fe) / calcula(nodo->fd));
        } 
        if (*nodo->operacao == '*') {
            return (calcula(nodo->fe) * calcula(nodo->fd));
        }
    }
    // elemento é um float
    if (nodo->tipo == 0) {
        return nodo->valor;
    }
    
}

int main() {
    struct nodo *raiz = malloc(sizeof(struct nodo));
    raiz->pai = NULL;
    raiz->fd = NULL;
    raiz->fe = NULL;

    char exp[MAX_TAM];
    fgets(exp, MAX_TAM, stdin);
 
    insere(raiz, exp);

    printf("\n\n");
    printf("PRÉ-ORDEM: \n");
    imprime_pre_ordem(raiz);
    printf("\n\n");

    printf("EM-ORDEM: \n");
    imprime_em_ordem(raiz);
    printf("\n\n");

    printf("POS-ORDEM: \n");
    imprime_pos_ordem(raiz);
    printf("\n\n");

    printf("CÁLCULO: \n");
    double result = calcula(raiz);
    printf("%.2f", result);
    printf("\n\n");


    printf("LIBERA: \n");
    libera_pos_ordem(raiz);



}
