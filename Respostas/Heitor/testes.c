#include "jogo.h"
#include "jogador.h"
#include "dado.h"

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