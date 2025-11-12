#include <stdio.h>
#include <stdlib.h>

// FUNÇÕES DE ERRO
void matar_programa_falta_memoria() {
    fprintf(stderr, "Erro por falta de memória\n");
    exit(1);
}
    
void matar_programa_ponteiro_nulo() {
    fprintf(stderr, "Erro por ponteiro nulo\n");
    exit(1);
}