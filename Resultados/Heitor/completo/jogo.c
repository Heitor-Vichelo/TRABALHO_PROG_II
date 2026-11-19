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

    scanf(" %[^\n]\n", opcao); // INICIO
    // scanf(" %15s", opcao); // MAPA

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
 
        // O jogador da vez sai da casa antiga antes de qualquer recuo,
        // para que essa casa seja considerada livre.
        retiraJogadorMapa(jogo->mapa, jogador);
 
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

/*
=========== ESTADO ============
[INICIO]
[1] OURO 10
[2] MONSTRO GOBLIN (F:3 XP:10)
[3] AVANCA 2 <- CARLA
[4] VAZIA <- ANA
[5] ITEM ESPADA (P:10 F:+2) <- BRUNO
[6] MONSTRO ORC (F:6 XP:25)
[7] VOLTA 3
[8] OURO 20
[9] VAZIA
[10] MONSTRO DRAGAO (F:9 XP:50)
[11] OURO 5
[12] VAZIA
[FIM]
-------------------------------
- ANA: casa 4 | forca 5 | xp 0 | ouro 10
- BRUNO: casa 5 | forca 5 | xp 0 | ouro 0
- CARLA: casa 3 | forca 4 | xp 0 | ouro 0
- Situacao: EM ANDAMENTO
===============================
*/
void imprimeEstadoJogo(Jogo *jogo) {
    printf("=========== ESTADO ============\n");
 
    printf("[INICIO]");
    int primeiro = 1;
    for (int i = 0; i < jogo->qtdJogadores; i++) {
        if (obtemPosicaoJogador(jogo->jogadores[i]) == 0) {
            printf(primeiro ? " <- %s" : ", %s", obtemNomeJogador(jogo->jogadores[i]));
            primeiro = 0;
        }
    }
    printf("\n");
 
    imprimeCelulasMapa(jogo->mapa);
 
    printf("[FIM]");
    if (jogo->vencedor != NULL) {
        printf(" <- %s", obtemNomeJogador(jogo->vencedor));
    }
    printf("\n");
 
    printf("-------------------------------\n");
 
    for (int i = 0; i < jogo->qtdJogadores; i++) {
        printEstadoJogador(jogo->jogadores[i]);
    }
 
    if (jogo->vencedor == NULL) {
        printf("- Situacao: EM ANDAMENTO\n");
    } else {
        printf("- Situacao: VENCEDOR %s\n", obtemNomeJogador(jogo->vencedor));
    }
 
    printf("===============================\n");
}

/*
=========== RANKING ===========
1. BRUNO (VERDE) | casa 13 | forca 5 | xp 0
2. ANA (VERMELHO) | casa 5 | forca 7 | xp 0
3. CARLA (AMARELO) | casa 3 | forca 4 | xp 0
===============================
*/

void imprimeRankingJogo(Jogo *jogo) {
    //cria uma copia do vetor de jogadores para nao mudar a ordem original do vetor
    Jogador **ranking = calloc(jogo->qtdJogadores, sizeof(Jogador *));
    
    if (!ranking) return;

    for (int i = 0; i < jogo->qtdJogadores; i++) {
        ranking[i] = copiaJogador(jogo->jogadores[i]);
    }

    //ordena o vetor com qsort
    //    vetor  |    quantidade     |  tamanho do ele. |    comparacao  
    qsort(ranking, jogo->qtdJogadores, sizeof(Jogador *), comparaOrdJogador);

    // imprime todas as posicoes do vetor ordenado
    printf("=========== RANKING ===========\n");
    for (int i = 0; i < jogo->qtdJogadores; i++) {
        printRankingJogador(ranking[i], i + 1);
    }
    printf("===============================\n");

    // desaloca o ranking
    for (int i = 0; i < jogo->qtdJogadores; i++) {
        desalocaJogador(ranking[i]);
    }
    free(ranking);
}

/*
========= RELATORIO ===========
- Celulas do mapa: 12
- Jogadores: 3
- Jogadas totais: 23
- Disputas: 9
- Monstros derrotados: 0
- Situacao: VENCEDOR BRUNO
-------------------------------
- ANA: jogadas 8 | disputas vencidas 6 | forca 7 | xp 0 | ouro 0
- BRUNO: jogadas 8 | disputas vencidas 3 | forca 5 | xp 0 | ouro 25
- CARLA: jogadas 7 | disputas vencidas 0 | forca 4 | xp 0 | ouro 0
===============================
*/

void imprimeRelatorioJogo(Jogo *jogo) {
    printf("========= RELATORIO ===========\n");

    printf("- Celulas do mapa: %d\n", obtemQtdCelulasMapa(jogo->mapa));
    printf("- Jogadores: %d\n", jogo->qtdJogadores);
    printf("- Jogadas totais: %d\n", jogo->jogadasTotais);
    printf("- Disputas: %d\n", jogo->disputasTotais);

    int monstrosDerrotados = 0;
    for (int i = 0; i < jogo->qtdJogadores; i++) {
        monstrosDerrotados += obtemMonstrosDerrotadosJogador(jogo->jogadores[i]);
    }

    printf("- Monstros derrotados: %d\n", monstrosDerrotados);

    if (jogo->vencedor == NULL) {
        printf("- Situacao: EM ANDAMENTO\n");
    } else {
        printf("- Situacao: VENCEDOR %s\n", obtemNomeJogador(jogo->vencedor));
    }

    printf("-------------------------------\n");

    for (int i = 0; i < jogo->qtdJogadores; i++) {
        printRelatorioJogador(jogo->jogadores[i]);
    }

    printf("===============================\n");
}

void executaJogo(Jogo *jogo){}