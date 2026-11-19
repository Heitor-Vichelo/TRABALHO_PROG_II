#include "acao_avanco.h"
#include <stdio.h>
#include <stdlib.h>

struct Avanco
{
    int qtd;
};

Avanco *criaAvanco(int qtd){
    Avanco* avanco = (Avanco*) calloc(1, sizeof(struct Avanco));
    avanco->qtd = qtd;
    return avanco;
}

Avanco *leAvanco(){
    int qtd = 0;
    scanf("%d", &qtd);
    return criaAvanco(qtd);
}

int executaAvanco(void *dado, Jogador *j){
    Avanco *avanco = (Avanco*) dado;
    return avanco->qtd;
}

void imprimeAvanco(void *dado){
    Avanco *avanco = (Avanco*) dado;
    printf("AVANCA %d", avanco->qtd);
}

void desalocaAvanco(void *dado){
    Avanco *avanco = (Avanco*) dado;
    free(avanco);
}