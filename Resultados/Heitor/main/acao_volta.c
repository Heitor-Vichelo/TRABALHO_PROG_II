#include "acao_volta.h"
#include <stdio.h>
#include <stdlib.h>

struct Volta
{
    int qtd;
};

Volta *criaVolta(int qtd){
    Volta* volta = (Volta*) calloc(1, sizeof(struct Volta));
    volta->qtd = qtd;
    return volta;
}

Volta *leVolta(){
    int qtd = 0;
    scanf("%d", &qtd);
    return criaVolta(qtd);
}

int executaVolta(void *dado, Jogador *j){
    Volta *volta = (Volta*) dado;
    return -volta->qtd;
}

void imprimeVolta(void *dado){
    Volta *volta = (Volta*) dado;
    printf("VOLTA %d", volta->qtd);
}

void desalocaVolta(void *dado){
    Volta *volta = (Volta*) dado;
    free(volta);
}