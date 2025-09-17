#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TAM 10
struct nodo {
    union {
        char *operacao;
        float valor;
    };
    struct nodo *pai;
    struct nodo *fe;
    struct nodo *fd;
};

void le_e_insere();

void le_e_insere(struct nodo *raiz) {
    char exp[MAX_TAM];
    fgets(exp, MAX_TAM, stdin);
    
    // pega o primeiro elemento da expressão
    const char *delim = ' '; // delimitadores do fim de um elemento (espaço ou virgula)
    char *token = strtok(exp, delim);

    struct nodo *aux = raiz;
    // verifica se é o fim da expressão
    while (token != NULL) {
        if((token == "+") || (token == "-") || (token == "*") || (token == "/")) {
            printf("Operação: %s\n", token);
            aux->operacao = token;
            struct nodo *temp = aux;
            if(aux->fe == NULL) {
                aux = aux->fe;
            } else {
                aux = aux->fd;
            }
            aux->pai = temp;
        } else {
            double nov_tok = atof(token);
            printf("Valor: %f\n", nov_tok);
            aux->valor = nov_tok;

            if(aux->pai->fe != NULL && aux->pai->fd != NULL) {
                aux = aux->pai->pai;
            } else {
                aux = aux->fd;
            }
        }
        token = strtok(NULL, delim);
    }
}

int main() {
    struct nodo *raiz = malloc(sizeof(struct nodo));
    raiz->pai = NULL;

    le_e_insere(raiz);

}
