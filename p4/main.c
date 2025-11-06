#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "kdtree.h"

int main() {

    // Ler n (número de pontos) e k (número de dimensões)
    printf("Insira N e K.\n");
    uint64_t n, k;
    scanf("%ld", &n);
    scanf("%ld", &k);

    struct nodo *raiz = criar_raiz();

   criar_kdtree(&raiz, n, k);
        
    // // Ler os pontos 
    // // Construir a árvore
    // // Pedir entradas do usuário
    
    char op;
    
    scanf("%c", &op);
	while(op != 'f'){
		switch (op) {
            case 'b': // Realizar busca dos pontos enviados pelo usuário
            int classe = buscar_kdtree(/* vetor dos pontos */);
				if(classe) {
                    printf("Encontrado. Classe %d.\n", classe);
                } else {
                    printf("Não encontrado.\n");
                }
                break;
                case 'z':
				encontrar_z_vizinhos(/* Número de vizinhos a encontrar e vetor com pontos */);
				puts("\n");
				break;
			case 'l':
				imprimirEmLargura(/* kdtre */);
				break;
			default:
				fprintf(stderr,"Opcao Inválida %d\n", (int)op);
            }
		scanf(" %c", &op);
	}
    return 0;
}