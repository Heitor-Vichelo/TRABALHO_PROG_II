#ifndef _ACAO_ITEM_H_
#define _ACAO_ITEM_H_

#include "jogador.h"

#define MAX_TAM_NOME_ITEM 21

typedef struct Item Item;

/**
 * @brief Aloca dinamicamente uma ação do tipo ITEM e guarda nela o nome (copiado), o preco  e o bonus
 * @param nome Nome do item
 * @param preco Preco do item
 * @param bonus forca ganha por comprar o item
 * @return Ponteiro para o item criado
 */
Item *criaItem(char *nome, int preco, int bonus);

/**
 * @brief Lê da entrada padrão, na mesma linha, o nome, a o preco e o bonus do item (a palavra ITEM
 * já deve ter sido lida) e cria o item com criaItem.
 * @return Ponteiro para o item criado
 */
Item *leItem();

/**
 * @brief Converte o dado genérico para item e realiza a acao do item.
 * se o ouro do jogador for maior ou igual ao preco do item, o jogador compra o item (diminui o preco 
 * do item do ouro do jogador) e eh incrementado o valor do bonus do item na forca do jogador
 * @param dado Ponteiro genérico para o item
 * @param j Jogador que parou na celula
 * @return retorna 0 (quantidade de casas que o jogador deve andar)
 */ 
int executaItem(void *dado, Jogador *j);

/**
 * @brief Converte o dado genérico para item e imprime, sem quebra de linha:
 * "ITEM <nome> (P:<preco> F:+<bonus>)". Ex: "ITEM ESPADA (P:10 F:+2)"
 * @param dado Ponteiro genérico para o item
 */
void imprimeItem(void *dado);

/**
 * @brief Converte o dado genérico para item e libera a memória alocada para ele
 * @param dado Ponteiro genérico para o item
 */
void desalocaItem(void *dado);

#endif // _ACAO_ITEM_H_
