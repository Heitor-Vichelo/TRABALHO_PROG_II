#ifndef _ACAO_AVANCO_H_
#define _ACAO_AVANCO_H_

#include "jogador.h"

typedef struct Avanco Avanco;

/**
 * @brief Aloca dinamicamente uma ação do tipo AVANCO e guarda quantidade
 * @param qtd quantidade de casas a serem avancadas
 * @return Ponteiro para casa avanco criado
 */
Avanco *criaAvanco(int qtd);

/**
 * @brief Lê da entrada padrão, na mesma linha, a quantidade (a palavra AVANCO
 * já deve ter sido lida) e cria um AVANCO com criaAvanco.
 * @return Ponteiro para casa avanco criado
 */
Avanco *leAvanco();

/**
 * @brief Converte o dado genérico para avanco e realiza o deslocamento. 
 * @param dado Ponteiro genérico para o avanco
 * @param j Jogador que parou na célula
 * @return retorna a quantidade de casas que o jogador deve prosseguir
 */
int executaAvanco(void *dado, Jogador *j);

/**
 * @brief Converte o dado genérico para avanco e imprime, sem quebra de linha:
 * "AVANCA <quantidade>"
 * @param dado Ponteiro genérico para o avanco
 */
void imprimeAvanco(void *dado);

/**
 * @brief Converte o dado genérico para avanco e libera a memória alocada para ele
 * @param dado Ponteiro genérico para o avanco
 */
void desalocaAvanco(void *dado);

#endif // _ACAO_AVANCO_H_
