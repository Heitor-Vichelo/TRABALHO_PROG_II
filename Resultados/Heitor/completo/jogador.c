#include "jogador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
#define MAX_TAM_NOME_JOGADOR 51
#define MAX_TAM_COR_JOGADOR 16
typedef struct Jogador Jogador;
*/
char *obtemCorJogador(Jogador *j);

struct Jogador
{
    char nome[MAX_TAM_NOME_JOGADOR];
    char cor[MAX_TAM_COR_JOGADOR];
    int forca;
    int posicao;
    int xp;
    int ouro;
    int jogadas;
    int disputasVencidas;
    int monstrosDerrotados;
};


Jogador *criaJogador(char *nome, char *cor, int forca){
    Jogador *jogador = (Jogador*) calloc(1, sizeof(struct Jogador));
    strcpy(jogador->nome, nome);
    strcpy(jogador->cor, cor);
    jogador->forca = forca;

    return jogador;
}

Jogador *leJogador(){
    char nome[MAX_TAM_NOME_JOGADOR];
    char cor[MAX_TAM_COR_JOGADOR];
    int forca;

    scanf(" %50[^\n]", nome);
    scanf(" %15[^\n]", cor);
    scanf("%d", &forca);

    Jogador *jogador = criaJogador(nome, cor, forca);
    return jogador;
}

void *copiaJogador(void *d){
    Jogador *jogador = (Jogador*) d;
    Jogador *temp = criaJogador(jogador->nome, jogador->cor, jogador->forca);
    temp->disputasVencidas = jogador->disputasVencidas;
    temp->jogadas = jogador->jogadas;
    temp->monstrosDerrotados = jogador->monstrosDerrotados;
    temp->ouro = jogador->ouro;
    temp->posicao = jogador->posicao;
    temp->xp = jogador->xp;

    return (void*) temp;
}

int comparaNomeJogador(void *dado, void *nome){
    Jogador *jogador = (Jogador*) dado;
    char *name = (char*) nome;

    return !strcmp(jogador->nome, name);
}

int comparaOrdJogador(const void *d1, const void *d2){
    Jogador *j1 = *(Jogador**) d1;
    Jogador *j2 = *(Jogador**) d2;

    if(j1->posicao != j2->posicao){
        return j2->posicao - j1->posicao;
    }

    if(j1->forca != j2->forca){
        return j2->forca - j1->forca;
    }

    if(j1->xp != j2->xp){
        return j2->xp - j1->xp;
    }

    return strcmp(j1->nome, j2->nome);
}

int venceDisputaJogador(Jogador *desafiante, Jogador *ocupante){
    if(desafiante->forca > ocupante->forca){
        return 1;
    }

    if(desafiante->forca == ocupante->forca && desafiante->xp > ocupante->xp){
        return 1;
    }

    return 0;
}

char *obtemNomeJogador(Jogador *j){
    return j->nome;
}

char *obtemCorJogador(Jogador *j){
    return j->cor;
}

int obtemPosicaoJogador(Jogador *j){
    return j->posicao;
}

int obtemForcaJogador(Jogador *j){
    return j->forca;
}

int obtemXPJogador(Jogador *j){
    return j->xp;
}

int obtemOuroJogador(Jogador *j){
    return j->ouro;
}

int obtemJogadasJogador(Jogador *j){
    return j->jogadas;
}

int obtemDisputasVencidasJogador(Jogador *j){
    return j->disputasVencidas;
}

int obtemMonstrosDerrotadosJogador(Jogador *j){
    return j->monstrosDerrotados;
}

void definePosicaoJogador(Jogador *j, int posicao){
    j->posicao = posicao;
}

void adicionaForcaJogador(Jogador *j, int forca){
    j->forca += forca;
}

void adicionaXPJogador(Jogador *j, int xp){
    j->xp += xp;
}

void adicionaOuroJogador(Jogador *j, int ouro){
    j->ouro += ouro;
}

void incrementaJogadasJogador(Jogador *j){
    j->jogadas++;
}

void incrementaDisputasVencidasJogador(Jogador *j){
    j->disputasVencidas++;
}

void incrementaMonstrosDerrotadosJogador(Jogador *j){
    j->monstrosDerrotados++;
}

void printEstadoJogador(void *dado){
    //"- <nome>: casa <posicao> | forca <forca> | xp <xp> | ouro <ouro>" seguido de quebra de linha.
    Jogador *j = (Jogador*) dado;
    
    printf
    (
        "- %s: casa %d | forca %d | xp %d | ouro %d\n",
        obtemNomeJogador(j), obtemPosicaoJogador(j), obtemForcaJogador(j), obtemXPJogador(j), obtemOuroJogador(j)
    );

}

/* EXEMPLO DE SAIDA: 
=========== RANKING ===========
1. BRUNO (VERDE) | casa 13 | forca 5 | xp 0
2. ANA (VERMELHO) | casa 5 | forca 7 | xp 0
3. CARLA (AMARELO) | casa 3 | forca 4 | xp 0
===============================
*/
void printRankingJogador(Jogador *j, int colocacao){
    printf
    (
        "%d. %s (%s) | casa %d | forca %d | xp %d\n", 
        colocacao, obtemNomeJogador(j), obtemCorJogador(j), obtemPosicaoJogador(j), obtemForcaJogador(j), obtemXPJogador(j)
    );
}

/* EXEMPLO DE SAIDA
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
void printRelatorioJogador(void *dado){
    Jogador *j = (Jogador*) dado;
    //"- <nome>: jogadas <jogadas> | disputas vencidas <disputas> | forca <forca> | xp <xp> | ouro <ouro>"* seguido de quebra de linha.
    printf
    (
        "- %s: jogadas %d | disputas vencidas %d | forca %d | xp %d | ouro %d\n",
        obtemNomeJogador(j), obtemJogadasJogador(j), obtemDisputasVencidasJogador(j), obtemForcaJogador(j), obtemXPJogador(j), obtemOuroJogador(j)
    );
}

void desalocaJogador(void *dado){
    Jogador *jogador = (Jogador*) dado;
    free(jogador);
}