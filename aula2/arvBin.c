#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 50
struct pessoa
{
    char nome[MAX_CHAR];
    uint16_t idade;
    uint64_t cpf;
};


struct nodo
{
    struct pessoa *pessoa;
    struct nodo *f1;
    struct nodo *f2;
};

// Declarações das funções (protótipos)
void inicializar(struct nodo* raiz);
struct pessoa* buscar(uint64_t chave, struct nodo* raiz);
uint16_t inserir(struct pessoa* pessoa, struct nodo *raiz);
struct pessoa* remover(uint64_t chave, struct nodo *raiz);
void* destruir_pessoa(struct pessoa *pessoa);
void* destruir_arvore(struct nodo *raiz);
struct nodo* criar_nodo(void);
void imprimir_arvore(struct nodo *raiz);
void imprimir_pessoa(struct pessoa *pessoa);
struct pessoa* criar_pessoa(void);

// Funções da Atividade
void inicializar(struct nodo* raiz){
    raiz->f1 = NULL;
    raiz->f2 = NULL;
    raiz->pessoa = NULL;
}

// inserir de maneira cronológica
uint16_t inserir(struct pessoa* pessoa, struct nodo* raiz) {
    if (pessoa == NULL || raiz == NULL) {
        printf("Ponteiro nulo.\n");
        return -1;
    }

    while (posi < dict->numItens && dict->pessoas[posi]->cpf < pessoa->cpf) {
        posi++;
    }
    
    dict->pessoas[posi] = pessoa;
    dict->numItens ++;

    return posi;
}

struct pessoa* remover(uint64_t chave, struct dicionario_pessoa* dict) {
    if (dict == NULL) {
        printf("Ponteiro nulo.\n");
        return NULL;
    }
    
    // Verifica se há itens no dicionário
    if (dict->numItens <= 0) {
        printf("Dicionário vazio.\n");
        return NULL;
    }

    // procura posição do item a ser removido
    size_t posi = 0;
    while (posi < dict->numItens && dict->pessoas[posi]->cpf != chave) {
        posi++;
    }

    if (posi >= dict->numItens) {
        printf("Elemento não encontrado.\n");
        return NULL;
    }
    
    struct pessoa* aux = dict->pessoas[posi];

    // Remove o elemento do vetor
    for (size_t i = posi; i < dict->numItens - 1; i++) {
        dict->pessoas[i] = dict->pessoas[i + 1];
    }

    dict->numItens--;
    
    return aux;
}

void *destruir_pessoa(struct pessoa *pessoa) {
    if (pessoa == NULL) {
        printf("Ponteiro nulo.\n");
        return NULL;
    }
    free(pessoa);
}

void *destruir_dicionario(struct dicionario_pessoa *dict) {
    if (dict == NULL) {
        printf("Ponteiro nulo.\n");
        return NULL;
    }

    for (size_t i = 0; i < dict->numItens; i++) {
        destruir_pessoa(dict->pessoas[i]);
        dict->pessoas[i] = NULL;
    }
    free(dict);
}

struct dicionario_pessoa *criar_dicionario() {
    struct dicionario_pessoa *dict = malloc(sizeof(struct dicionario_pessoa));
    if (dict == NULL) {
        printf("Erro ao alocar dicionário.\n");
        return NULL;
    }
    inicializar(dict);
    return dict;
}

void imprimir_dicionario(struct dicionario_pessoa *dict) {
    if (dict == NULL) {
        printf("Ponteiro nulo.\n");
        return;
    }

    if (dict->numItens <= 0) {
        printf("Dicionário vazio.\n");
        return;
    }

    printf("Quantidade de Itens no Dicionário: %zu\n", dict->numItens);

    for (size_t i = 0; i < dict->numItens; i++) {
        printf("Pessoa [%zu]:\n", i);
        imprimir_pessoa(dict->pessoas[i]);
        printf("\n");
    }
}

void imprimir_pessoa(struct pessoa *pessoa) {
    if (pessoa == NULL) {
        printf("Ponteiro nulo.\n");
        return;
    }

    printf("Nome: %s\n", pessoa->nome);
    printf("Idade: %hu\n", pessoa->idade);
    printf("CPF: %lu\n", pessoa->cpf);
}

struct pessoa *criar_pessoa(){
    struct pessoa *nova_pessoa = malloc(sizeof(struct pessoa));

    printf("Insira seu nome: ");
    getchar();
    fgets(nova_pessoa->nome, MAX_CHAR, stdin);
    // Remove o \n do final da string se existir
    nova_pessoa->nome[strcspn(nova_pessoa->nome, "\n")] = '\0';
    
    printf("Insira sua idade: ");
    scanf("%hu", &nova_pessoa->idade);

    printf("Insira seu CPF: ");
    scanf("%lu", &nova_pessoa->cpf);

    printf("\n");

    return nova_pessoa;
}

int main() {
    // criar dicionário
    struct dicionario_pessoa *dict = criar_dicionario();

    // selecionar a operação da ser realizada
    int i;
    printf("OPERAÇÕES: \n");
    printf("0 - TERMINAR programa;\n");
    printf("1 - INSERIR pessoa no dicionário;\n");
    printf("2 - BUSCAR pessoa no dicionário;\n");
    printf("3 - REMOVER pessoa no dicionário;\n");
    printf("4 - IMPRIMIR dicionário.\n");

    printf("Selecione a Operação: ");
    scanf("%d", &i);
    printf("\n");

    while (i) {
        switch (i) {
        case INSERIR:
            struct pessoa *p1 = criar_pessoa();
            uint16_t pos = inserir(p1, dict);
            if (pos < 0) {
                printf("Erro na inserção.\n");
            }

            printf("Pessoa inserida na posição %hu.\n", pos);
            break;
        case BUSCAR:
            uint64_t chave;
            printf("Chave: ");
            scanf("%lu", &chave);
            printf("\n");

            struct pessoa *p2 = buscar(chave, dict);
            if (p2 == NULL) {
                printf("Erro ao buscar pessoa.\n");
                break;
            }
            
            printf("Pessoa Encontrada.\n");
            imprimir_pessoa(p2);
            printf("\n");
            break;
            
        case REMOVER:
            uint64_t chave1;
            printf("Chave: ");
            scanf("%lu", &chave1);
            printf("\n");

            struct pessoa *pessoa = remover(chave1, dict);
            if (pessoa == NULL) {
                printf("Erro ao remover pessoa.\n");
                break;
            }
            
            printf("Pessoa Removida: \n");
            imprimir_pessoa(pessoa);
            printf("\n");

            destruir_pessoa(pessoa);

            break;
        case IMPRIMIR: 
            imprimir_dicionario(dict);
            printf("\n");
            break;
        default:
            printf("Opção inválida.\n");
            break;
        }
        printf("\n");
        printf("OPERAÇÕES: \n");
        printf("0 - TERMINAR programa;\n");
        printf("1 - INSERIR pessoa no dicionário;\n");
        printf("2 - BUSCAR pessoa no dicionário;\n");
        printf("3 - REMOVER pessoa no dicionário;\n");
        printf("4 - IMPRIMIR dicionário.\n");

        printf("Selecione a Operação: ");
        scanf("%d", &i);
        printf("\n");
    }

    destruir_dicionario(dict);
    return 0;
}
