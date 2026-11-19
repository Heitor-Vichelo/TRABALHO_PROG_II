#ifndef _ACAO_VAZIO_H_
#define _ACAO_VAZIO_H_

#include "jogador.h"

/* executa vazio retorna zero para o jogador nao andar nenhuma casa */
int executaVazio(void *dado, Jogador *j);

/**
 * @brief apenas imprima a palavra vazio, sem quebra de linha:
 * "VAZIA". Ex: "VAZIA"
 * @param dado Ponteiro com valor NULL
 */
void imprimeVazio(void *dado);

// faz nada feito apenas para a para a celula vazio ter uma funcao desaloca
void desalocaVazio(void *dado);

#endif