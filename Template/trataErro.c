#include "redblack.h"
#include "trataErro.h"

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
