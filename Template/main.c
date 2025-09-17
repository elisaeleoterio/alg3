#include <stdio.h>
#include <stdlib.h>

#include "redblack.h"

// Declaração da variável global do SENTINELA
struct nodo *sentinela = NULL;

void inicia_sentinela() {
	if (sentinela == NULL) {
		sentinela = malloc(sizeof(struct nodo));
		if (!sentinela) {
			printf("Erro ao incializar sentinela\n");
			exit(1);
		}
	}

	sentinela->chave = -1;
	sentinela->cor = 0;
	sentinela->fd = sentinela;
	sentinela->fe = sentinela;
	sentinela->pai = sentinela;
}


int main(){

	imprimirDadosAluno();

	struct nodo* raiz = sentinela;

	char op;
	int val;

	printf("Insira a operação a ser realizada: ");
	scanf("%c", &op);
	while(op != 'f'){
		switch (op) {
			case 'i':
				scanf("%d", &val);
				if(!inserir(&raiz, val))
					fprintf(stderr,"Falha ao inserir.\n");
					break;
			case 'r':
			scanf("%d", &val);
			if(!excluir(&raiz, val))
			fprintf(stderr,"Falha ao remover %d.\n", val);
				break;
			case 'e':
				imprimirEmOrdem(raiz);
				puts("\n");
				break;
			case 'l':
				imprimirEmLargura(raiz, true);
				break;
				case 'b':
				scanf("%d", &val);
				struct nodo* valB = buscar(raiz, val);
				if(valB != &sentinela)
					printf("Encontrado %d\n", valB->chave);
				else
				printf("Nao encontrado %d.\n", val);
				break;
			default:
				fprintf(stderr,"Opcao Invalida %d", (int)op);
		}
		scanf(" %c", &op);
	}

	return 0;
}