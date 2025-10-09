#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "aluno.h"
#include "redblack.h"

// FUNÇÕES ALUNO
struct aluno* getAluno(){
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if(!retorno)
        matarProgramaFaltaMemoria();

    retorno->nome = malloc(sizeof("Elisa Rocha Eleotério"));//sizeof conta o \0
	if(!retorno->nome)
		matarProgramaFaltaMemoria();
        
    retorno->nomeDinf = malloc(sizeof("ere24"));
    if(!retorno->nomeDinf) {
        matarProgramaFaltaMemoria();
    }
    
	strcpy(retorno->nome, "Elisa Rocha Eleotério");
    strcpy(retorno->nomeDinf, "ere24");
    retorno->grr = 20241731;

	return retorno;
}

void imprimirDadosAluno(){
    struct aluno* aluno = getAluno();
    
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    return;
}
