#include "jogo.h"
#include "jogador.h"
#include "acao_vazio.h"
#include "acao_avanco.h"
#include "acao_volta.h"
#include "acao_item.h"
#include "acao_monstro.h"
#include "acao_ouro.h"
#include "dado.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_OPCAO_JOGO 20
#define POSICAO_INICIAL 0

struct Jogo {
    Mapa *mapa;
    Jogador **jogadores;
    Jogador *vencedor;
    int qtdJogadores;
    int jogadorAtual;
    int jogadasTotais;
    int disputasTotais;
};

Jogo *criaJogo(){
    Jogo *j = (Jogo*) calloc(1, sizeof(struct Jogo));
    j->mapa = criaMapa();
    return j;
}

void leMapa(Mapa *m) {
    char opcao[TAM_OPCAO_JOGO];

    scanf(" %15s", opcao); // INICIO
    scanf(" %15s", opcao); // MAPA

    while (scanf(" %15s", opcao) == 1) {
        if (!strcmp(opcao, "OURO")) 
        {
            insereCelulaMapa(m, leOuro(), executaOuro, imprimeOuro, desalocaOuro);
        } 
        else if (!strcmp(opcao, "MONSTRO")) 
        {
            insereCelulaMapa(m, leMonstro(),executaMonstro, imprimeMonstro, desalocaMonstro);
        } 
        else if (!strcmp(opcao, "AVANCA")) 
        {
            insereCelulaMapa(m, leAvanco(), executaAvanco, imprimeAvanco, desalocaAvanco);
        }
        else if (!strcmp(opcao, "VOLTA")) 
        {
            insereCelulaMapa(m, leVolta(), executaVolta, imprimeVolta, desalocaVolta);
        } 
        else if (!strcmp(opcao, "VAZIA")) 
        {
            insereCelulaMapa(m, NULL, executaVazio, imprimeVazio, desalocaVazio);
        }
        else if (!strcmp(opcao, "ITEM")) 
        {
            insereCelulaMapa(m, leItem(), executaItem, imprimeItem, desalocaItem);
        } 
        else if (!strcmp(opcao, "FIM")) 
        {
            scanf(" %15s", opcao); // MAPA
            break;
        }
    }
}

void leJogo(Jogo *j) {
    char opcao[TAM_OPCAO_JOGO];

    leMapa(j->mapa);

    while (scanf(" %19s", opcao) == 1) {
        if (!strcmp(opcao, "J")) {
            CadastraJogadorJogo(j);
        } else if (!strcmp(opcao, "ROLAGEM")) {
            int qtd;
            scanf("%d", &qtd);
            executaRolagens(j, qtd);
        } else if (!strcmp(opcao, "E")) {
            scanf(" %19s", opcao);

            if (!strcmp(opcao, "ESTADO")) {
                imprimeEstadoJogo(j);
            } else if (!strcmp(opcao, "RANKING")) {
                imprimeRankingJogo(j);
            } else if (!strcmp(opcao, "RELATORIO")) {
                imprimeRelatorioJogo(j);
            }
        } else if (!strcmp(opcao, "F")) {
            break;
        }
    }
}

void CadastraJogadorJogo(Jogo *j) {
    Jogador *novo = leJogador();

    if (JaExisteJogador(j, novo)) {
        desalocaJogador(novo);
        return;
    }

    Jogador **temp = realloc(j->jogadores,(j->qtdJogadores + 1) * sizeof(Jogador *));

    if (temp == NULL) {
        desalocaJogador(novo);
        return;
    }

    j->jogadores = temp;
    j->jogadores[j->qtdJogadores] = novo;
    j->qtdJogadores++;
}

int JaExisteJogador(Jogo *jogo, Jogador *jogador) {
    for (int i = 0; i < jogo->qtdJogadores; i++) {
        if (comparaNomeJogador(
                jogo->jogadores[i],
                obtemNomeJogador(jogador))) {
            return 1;
        }
    }

    return 0;
}

void desalocaJogo(Jogo *j) {
    for (int i = 0; i < j->qtdJogadores; i++) {
        desalocaJogador(j->jogadores[i]);
    }

    free(j->jogadores);
    desalocaMapa(j->mapa);
    free(j);
}

void processaTurno(Jogo *jogo, Jogador *jogador) {
    incrementaJogadasJogador(jogador);
    jogo->jogadasTotais++;

    int novaPosicao = obtemPosicaoJogador(jogador) + RolaDado();

    // Termina a jogada se o jogador perder uma disputa.
    if (!deslocaJogador(jogo, jogador, novaPosicao)) {
        return;
    }

    // O jogador venceu ou alcançou o fim.
    if (jogo->vencedor != NULL) {
        return;
    }

    Celula *celula = obtemCelulaMapa( jogo->mapa, obtemPosicaoJogador(jogador));

    if (celula == NULL) return;

    int deslocamento = executaAcaoCelula(celula, jogador);

    if (deslocamento == RECUO_CELULA) {
        recuaJogadorMapa(jogo->mapa, jogador, obtemPosicaoJogador(jogador));
        return;
    }

    if (deslocamento != 0) {
        novaPosicao = obtemPosicaoJogador(jogador) + deslocamento;

        // A nova célula não executa sua ação.
        deslocaJogador(jogo, jogador, novaPosicao);
    }
}

int deslocaJogador(Jogo *jogo, Jogador *jogador, int destino) {
    int fim = obtemPosicaoFimMapa(jogo->mapa);

    if (destino <= 0) {
        moveJogadorMapa(jogo->mapa, jogador, 0);
        return 1;
    }

    if (destino >= fim) {
        moveJogadorMapa(jogo->mapa, jogador, fim);
        jogo->vencedor = jogador;
        return 1;
    }

    Jogador *ocupante = obtemOcupanteMapa(jogo->mapa, destino);

    if (ocupante != NULL && ocupante != jogador) {
        jogo->disputasTotais++;

        if (venceDisputaJogador(jogador, ocupante)) {
            incrementaDisputasVencidasJogador(jogador);
            recuaJogadorMapa(jogo->mapa, ocupante, destino);
        } else {
            incrementaDisputasVencidasJogador(ocupante);
            recuaJogadorMapa(jogo->mapa, jogador, destino);
            return 0;
        }
    }

    moveJogadorMapa(jogo->mapa, jogador, destino);
    return 1;
}

void executaRolagens(Jogo *jogo, int quantidade) {
    for (int i = 0; i < quantidade && jogo->vencedor == NULL; i++) {

        Jogador *jogador = jogo->jogadores[jogo->jogadorAtual];

        processaTurno(jogo, jogador);

        if (jogo->vencedor == NULL) {
            jogo->jogadorAtual = (jogo->jogadorAtual + 1) % jogo->qtdJogadores;
        }
    }
}