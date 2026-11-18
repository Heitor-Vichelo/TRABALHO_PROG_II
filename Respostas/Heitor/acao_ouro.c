#include "acao_ouro.h"
#include <stdio.h>
#include <stdlib.h>

struct Ouro
{
    int qtd;
};

Ouro *criaOuro(int qtd){
    Ouro *ouro = (Ouro*) calloc(1, sizeof(struct Ouro));
    ouro->qtd = qtd;
    return ouro;
}

Ouro *leOuro(){
    int qtd = 0;
    scanf("%d", &qtd);
    return criaOuro(qtd);
}

int executaOuro(void *dado, Jogador *j){
    Ouro* ouro = (Ouro*) dado;
    adicionaOuroJogador(j, ouro->qtd);
    return 0;
}

void imprimeOuro(void *dado){
    Ouro* ouro = (Ouro*) dado;
    printf("OURO %d", ouro->qtd);
}

void desalocaOuro(void *dado){
    Ouro* ouro = (Ouro*) dado;
    free(ouro);
}