#include "acao_vazio.h"
#include <stdio.h>

int executaVazio(void *dado, Jogador *j){
    return 0;
}

void imprimeVazio(void *dado){
    printf("VAZIA");
}

void desalocaVazio(void *dado){
    // Nada precisa ser liberado.
}