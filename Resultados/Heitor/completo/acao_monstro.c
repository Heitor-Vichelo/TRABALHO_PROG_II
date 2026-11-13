#include "acao_monstro.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "celula.h"

//typedef struct Monstro Monstro;

#define MAX_NOME_MONSTRO 21

struct Monstro
{
    char nome[MAX_NOME_MONSTRO];
    int forca;
    int xp;
    /* data */
};


Monstro *criaMonstro(char *nome, int forca, int xp){
    Monstro *m = calloc(1, sizeof(struct Monstro));
    strcpy(m->nome, nome);
    m->forca = forca;
    m->xp = xp;

    return m;
}

// EXEMPLO DE ENTRADA
// MONSTRO GOBLIN 3 10 (casa 2: nome, força e xp do monstro)
Monstro *leMonstro(){
    char nome[MAX_NOME_MONSTRO];
    int forca, xp;
    scanf(" %s %d %d\n", nome, &forca, &xp);
    Monstro *m = criaMonstro(nome, forca, xp);
    
    return m;
}

int executaMonstro(void *dado, Jogador *j){
    Monstro *m = (Monstro*) dado;
    if(obtemForcaJogador(j) >= m->forca){
        adicionaXPJogador(j, m->xp);
        incrementaMonstrosDerrotadosJogador(j);
        return 0;
    }
    return RECUO_CELULA;
}

// EXEMPLO DE SAIDA
// MONSTRO <nome> (F:<forca> XP:<xp>)". Ex: "MONSTRO GOBLIN (F:3 XP:10)
void imprimeMonstro(void *dado){
    Monstro *m = (Monstro*) dado;
    printf("MONSTRO %s (F:%d XP:%d)", m->nome, m->forca, m->xp);
}

void desalocaMonstro(void *dado){
    Monstro *m = (Monstro*) dado;
    free(m);
}