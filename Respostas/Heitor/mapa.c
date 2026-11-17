#include "mapa.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "jogador.h"
//typedef struct Mapa Mapa;

struct Mapa
{
    int qtdCelulas;
    Celula **celula;
};

Mapa *criaMapa(){
    Mapa *m = (Mapa*) calloc(1, sizeof(struct Mapa));
    return m;
}

void insereCelulaMapa(Mapa *m, void *acao, func_ptr_executa executa, func_ptr_imprime imprime, func_ptr_desaloca desaloca){
    m->celula = realloc(m->celula, (m->qtdCelulas+1)*sizeof(struct Celula*));
    m->celula[m->qtdCelulas] = criaCelula(acao, executa, imprime, desaloca);
    m->qtdCelulas++;
}

int obtemQtdCelulasMapa(Mapa *m){
    return m->qtdCelulas;
}

int obtemPosicaoFimMapa(Mapa *m){
    return m->qtdCelulas + 1;
}

Celula *obtemCelulaMapa(Mapa *m, int posicao){
    if(posicao < 1 || posicao > m->qtdCelulas){
        return NULL;
    }
    return m->celula[posicao - 1];
}

Jogador *obtemOcupanteMapa(Mapa *m, int posicao){
    Celula *c = obtemCelulaMapa(m, posicao);

    if(c && estaOcupadaCelula(c)){
        return obtemOcupanteCelula(c);
    }

    return NULL;
}

void retiraJogadorMapa(Mapa *m, Jogador *j){
    int posicao = obtemPosicaoJogador(j);
    Celula *c = obtemCelulaMapa(m, posicao);

    if(c && obtemOcupanteCelula(c) == j){
        defineOcupanteCelula(c, NULL);
    }
}

void moveJogadorMapa(Mapa *m, Jogador *j, int posicao){
    retiraJogadorMapa(m, j);

    definePosicaoJogador(j, posicao);

    Celula *c = obtemCelulaMapa(m, posicao);

    if(c){
        defineOcupanteCelula(c, j);
    }
}

void recuaJogadorMapa(Mapa *m, Jogador *j, int origem){
    int posicao = origem - 1;

    while(posicao > 0 && obtemOcupanteMapa(m, posicao) != NULL){
        posicao--;
    }

    moveJogadorMapa(m, j, posicao);
}

void imprimeCelulasMapa(Mapa *m){
    for(int i = 0; i < m->qtdCelulas; i++){
        imprimeCelula(m->celula[i], i + 1);
    }
}

void desalocaMapa(Mapa *m){
    for(int i = 0; i < m->qtdCelulas; i++){
        defineOcupanteCelula(m->celula[i], NULL);
        desalocaCelula(m->celula[i]);
    }

    free(m->celula);
    free(m);
}