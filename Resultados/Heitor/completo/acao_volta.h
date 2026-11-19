#ifndef _ACAO_VOLTA_H_
#define _ACAO_VOLTA_H_

#include "jogador.h"

typedef struct Volta Volta;

/**
 * @brief Aloca dinamicamente uma ação do tipo VOLTA e guarda quantidade
 * @param qtd quantidade de casas a serem recuadas
 * @return Ponteiro para casa volta criado
 */
Volta *criaVolta(int qtd);

/**
 * @brief Lê da entrada padrão, na mesma linha, a quantidade (a palavra VOTLA
 * já deve ter sido lida) e cria uma volta com criaVolta.
 * @return Ponteiro para casa volta criado
 */
Volta *leVolta();

/**
 * @brief Converte o dado genérico para volta e realiza o deslocamento. 
 * @param dado Ponteiro genérico para o volta
 * @param j Jogador que parou na célula
 * @return retorna a quantidade de casas que o jogador deve regredir
 */
int executaVolta(void *dado, Jogador *j);

/**
 * @brief Converte o dado genérico para volta e imprime, sem quebra de linha:
 * "VOLTA <quantidade>"
 * @param dado Ponteiro genérico para o volta
 */
void imprimeVolta(void *dado);

/**
 * @brief Converte o dado genérico para volta e libera a memória alocada para ele
 * @param dado Ponteiro genérico para o volta
 */
void desalocaVolta(void *dado);

#endif 
