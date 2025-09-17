#include <stdio.h>
#include <stdlib.h>

#define MAX_TAM 10

int main() {
    char exp[MAX_TAM];
    fgets(exp, MAX_TAM, stdin);
    printf("%s", exp);

    double exp1 = atof(exp);
    printf("%f", exp1);
}