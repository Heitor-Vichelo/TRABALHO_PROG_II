#include "jogo.h"
#include <stdlib.h>

int main(void) {
    Jogo *jogo = criaJogo();

    if (jogo == NULL) {
        return 1;
    }

    leJogo(jogo);
    desalocaJogo(jogo);

    return 0;
}