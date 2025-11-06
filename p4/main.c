#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>


#include "kdtree.h"

int main() {

    // Ler n (número de pontos) e k (número de dimensões)
    printf("Insira N e K.\n");
    uint16_t n, k;
    scanf("%hd", &n);
    scanf("%hd", &k);

    struct nodo *raiz = criar_nodo(-1, NULL);

   criar_kdtree(&raiz, n, k);
    
    char op;
    
    scanf("%c", &op);
	while(op != 'f'){
		switch (op) {
            case 'b': {// Realizar busca dos pontos enviados pelo usuário
                // Ler pontos a buscar
                double *vetchave = ler_pontos(k);
                struct nodo *busca = buscar_kdtree(raiz, vetchave, 0, k);
				if(busca) {
                    printf("Encontrado. Classe %d.\n", busca->classe);
                } else {
                    printf("Não encontrado.\n");
                }
                break;
            }
            case 'z': {
                // Quantidade de vizinhos a encontrar
                uint32_t z;
                scanf("%d", &z);
                double *vetchave = ler_pontos(k);
				encontrar_z_vizinhos(raiz, 0, k, vetchave, NULL);
				break;
            }
			case 'l': {
				printf("imprimir_em_largura(raiz)");
				break;
            }
			default: {
				fprintf(stderr,"Opcao Inválida %d\n", (int)op);
            }
        }
		scanf(" %c", &op);
	}
    return 0;
}