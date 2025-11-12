#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "utils.h"
#include "erro.h"
#include "kdtree.h"

int main() {

    // Ler n (número de pontos) e k (número de dimensões)
    printf("Insira N e K.\n");
    uint16_t n, k;
    scanf("%hd", &n);
    scanf("%hd", &k);

    struct nodo *raiz = NULL;

   criar_kdtree(&raiz, n, k);
//    imprimir_em_largura(raiz, n, k);
   printf("Árvore Construída.\n");
      
    char op;    
    scanf(" %c", &op);
	while(op != 'f') {
		switch (op) {
            case 'b': { // Realizar busca dos pontos enviados pelo usuário
                // Ler pontos a buscar
                double *vetchave = ler_pontos(k);
                struct nodo *busca = buscar_kdtree(raiz, vetchave, 0, k);
				if(busca) {
                    printf("Encontrado. Classe %d.\n", busca->classe);
                } else {
                    printf("Não encontrado.\n");
                }
                // Liberar vetchave e busca
                break;
            }
            case 'z': {
                // Quantidade de vizinhos a encontrar
                uint32_t z;
                scanf("%d", &z);
                double *vetchave = ler_pontos(k);
                // Alocação dinâmica do vetor que armazenará os z vizinhos mais próximos
                struct vizinhos *vizinhos = malloc(sizeof(struct vizinhos));
                if (!vizinhos) {
                    matar_programa_falta_memoria();
                }
                vizinhos->melhores = malloc(z * sizeof(struct vizinho));
                if (!vizinhos->melhores) {
                    free(vizinhos);
                    matar_programa_falta_memoria();
                }
                // Setar todos os melhores para distância INFINITY
                for (size_t i = 0; i < z; i++) {
                    vizinhos->melhores[i].distancia = INFINITY;
                    vizinhos->melhores[i].nodo = NULL;
                }
                vizinhos->quantidade = 0;
				encontrar_z_vizinhos(raiz, 0, k, vetchave, vizinhos, z);
                imprimir_vizinhos(vizinhos, k);
                free(vetchave);
                free(vizinhos->melhores);
                free(vizinhos);
                // Liberar vetchave e vizinhos
				break;
            }
			case 'l': {
                imprimir_em_largura(raiz, n, k);			
                break;
            }
			default: {
				fprintf(stderr,"Opcao Inválida %d\n", (int)op);
            }
        }
        printf("\n");
		scanf(" %c", &op);
	}

    liberar_arvore(raiz);
    
    return 0;
}