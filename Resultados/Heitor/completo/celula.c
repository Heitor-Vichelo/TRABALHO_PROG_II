#include "celula.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//typedef struct Celula Celula;
//typedef int (*func_ptr_executa)(void *acao, Jogador *j);
//typedef void (*func_ptr_imprime)(void *acao);
//typedef void (*func_ptr_desaloca)(void *acao);

struct Celula
{
    void *ocupante;
    void *acao;
    func_ptr_executa executa;
    func_ptr_desaloca desaloca;
    func_ptr_imprime imprime;
};

Celula *criaCelula(void *acao, func_ptr_executa executa, func_ptr_imprime imprime, func_ptr_desaloca desaloca){
    Celula *c = (Celula*) calloc(1, sizeof(struct Celula));
    c->acao = acao;
    c->executa = executa;
    c->imprime = imprime;
    c->desaloca = desaloca;

    return c;
}

int executaAcaoCelula(Celula *c, Jogador *j){
    return c->executa(c->acao, j);
}

void *obtemAcaoCelula(Celula *c){
    return c->acao;
}

Jogador *obtemOcupanteCelula(Celula *c){
    return c->ocupante;
}

void defineOcupanteCelula(Celula *c, Jogador *j){
    c->ocupante = j;
}

int estaOcupadaCelula(Celula *c){
    if(!c->ocupante) return 0;
    return 1;
}

// [2] MONSTRO GOBLIN (F:3 XP:10) <- CARLA
void imprimeCelula(Celula *c, int posicao){
    c->imprime(c->acao);
    if(estaOcupadaCelula(c)){
        Jogador *j = (Jogador*) c->ocupante;
        printf("<- %s\n", obtemNomeJogador(j));
    } else {
        printf("\n");
    }
    
}

void desalocaCelula(Celula *c){
    if(estaOcupadaCelula(c)){
        Jogador *j = (Jogador*) c->ocupante;
        desalocaJogador(j);
    }
    c->desaloca(c->acao);
    free(c);
}