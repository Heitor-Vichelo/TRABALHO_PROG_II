#include "acao_volta.h"
#include <stdio.h>
#include <stdlib.h>

struct Volta
{
    int qtd;
};

Volta *criaVolta(int qtd){
    Volta* volta = (Volta*) calloc(1, sizeof(struct Volta));
    if(!volta) return NULL;

    volta->qtd = qtd;
    return volta;
}

Volta *leVolta(){
    int qtd = 0;
    scanf("%d", &qtd);
    return criaVolta(qtd);
}

int executaVolta(void *dado, Jogador *j){
    if(!dado || !j) return 0;

    Volta *volta = (Volta*) dado;
    return -volta->qtd;
}

void imprimeVolta(void *dado){
    if(!dado) return;

    Volta *volta = (Volta*) dado;
    printf("VOLTA %d", volta->qtd);
}

void desalocaVolta(void *dado){
    if(!dado) return;

    Volta *volta = (Volta*) dado;
    free(volta);
}