#ifndef _JOGO_H_
#define _JOGO_H_

#include "jogador.h"
#include "mapa.h"

typedef struct Jogo Jogo;

Jogo *criaJogo();

void leMapa(Mapa *m);

void CadastraJogadorJogo(Jogo *j);

int JaExisteJogador(Jogo *jogo, Jogador *jogador);

void leJogo(Jogo *jogo);

void executaRolagens(Jogo *j, int quantidade);

void executaJogo(Jogo *jogo);

void processaTurno(Jogo *jogo, Jogador *jogador);

void imprimeEstadoJogo(Jogo *jogo);

void imprimeRankingJogo(Jogo *jogo);

void imprimeRelatorioJogo(Jogo *jogo);

void desalocaJogo(Jogo *jogo);

#endif
