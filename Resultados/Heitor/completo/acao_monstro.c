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
};

Monstro *criaMonstro(char *nome, int forca, int xp){
    Monstro *m = calloc(1, sizeof(struct Monstro));
    if(!m) return NULL;

    strcpy(m->nome, nome);
    m->forca = forca;
    m->xp = xp;

    return m;
}

Monstro *leMonstro(){
    char nome[MAX_NOME_MONSTRO];
    int forca, xp;
    scanf(" %s %d %d\n", nome, &forca, &xp);
    
    return criaMonstro(nome, forca, xp);
}

int executaMonstro(void *dado, Jogador *j){
    if(!dado || !j) return 0;

    Monstro *m = (Monstro*) dado;
    if(obtemForcaJogador(j) >= m->forca){
        adicionaXPJogador(j, m->xp);
        incrementaMonstrosDerrotadosJogador(j);
        return 0;
    }

    return RECUO_CELULA;
}

void imprimeMonstro(void *dado){
    if(!dado) return;

    Monstro *m = (Monstro*) dado;
    printf("MONSTRO %s (F:%d XP:%d)", m->nome, m->forca, m->xp);
}

void desalocaMonstro(void *dado){
    if(!dado) return;

    Monstro *m = (Monstro*) dado;
    free(m);
}