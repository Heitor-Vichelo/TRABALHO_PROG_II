#include "acao_item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
#define MAX_TAM_NOME_ITEM 21

typedef struct Item Item;
*/

struct Item
{
    char nome[MAX_TAM_NOME_ITEM];
    int preco;
    int bonus;
};


Item *criaItem(char *nome, int preco, int bonus){
    Item *i = (Item*) calloc(1, sizeof(struct Item));
    strcpy(i->nome, nome);
    i->preco = preco;
    i->bonus = bonus;

    return i;
}

Item *leItem(){
    char nome[MAX_TAM_NOME_ITEM];
    int preco;
    int bonus;
    scanf(" %20s %d %d", nome, &preco, &bonus);
    return criaItem(nome, preco, bonus);
}

int executaItem(void *dado, Jogador *j){
    Item *i = (Item*) dado;

    if(obtemOuroJogador(j) >= i->preco){
        adicionaOuroJogador(j, -i->preco);
        adicionaForcaJogador(j, i->bonus);
    }

    return 0;
}

//ITEM ESPADA (P:10 F:+2)
void imprimeItem(void *dado){
    Item *i = (Item*) dado;
    printf("ITEM %s (P:%d F:+%d)", i->nome, i->preco, i->bonus);
}

void desalocaItem(void *dado){
    Item *i = (Item*) dado;
    free(i);
}