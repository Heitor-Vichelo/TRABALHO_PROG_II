#ifndef _ACAO_VOLTA_H_
#define _ACAO_VOLTA_H_

#include "jogador.h"

typedef struct Volta Volta;

Avanco *criaAvanco(int qtd);

Avanco *leAvanco();

int executaAvanco(void *dado, Jogador *j);

void imprimeAvanco(void *dado);

void desalocaAvanco(void *dado);

#endif 
