#ifndef REDBLACK_H_
#define REDBLACK_H_

struct nodo {
    
    int chave;
    struct nodo *pai;
    struct nodo *fd;
    struct nodo *fe;
    int cor; // 0 nodo preto, 1 nodo vermelho
};

struct aluno{
    char* nome;//nome completo
    char* nomeDinf;//nome de usuário nas servidoras do dinf
    unsigned int grr;
};

struct aluno* getAluno();

void imprimirDadosAluno();

//retorna SENTINELA se não foi possível inserir
struct nodo* inserir(struct nodo** raiz, int chave);

// retorna o número de nodos excluídos
int excluir(struct nodo** raiz, int chave);

//retorna SENTINELA se não existe
struct nodo* buscar(struct nodo* raiz, int chave);

void imprimirEmOrdem(struct nodo* nodo);

void imprimirEmLargura(struct nodo* raiz);

#endif//REDBLACK_H