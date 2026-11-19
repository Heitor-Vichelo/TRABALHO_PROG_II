#ifndef _ACAO_AVANCO_H_
#define _ACAO_AVANCO_H_

#include "jogador.h"

typedef struct Avanco Avanco;

Avanco *criaAvanco(int qtd);

Avanco *leAvanco();

int executaAvanco(void *dado, Jogador *j);

void imprimeAvanco(void *dado);

void desalocaAvanco(void *dado);

#endif 
