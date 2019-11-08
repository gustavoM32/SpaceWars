#include <stdio.h>
#include "objetos.h"

/*
    mostraPosicoes()

    Imprime posições das naves e dos projéteis.
*/
void mostraPosicoes() {
    int i;
    printf("(%7.2lf, %7.2lf) | ", nave[0].pos[0], nave[0].pos[1]);
    printf("(%7.2lf, %7.2lf)", nave[1].pos[0], nave[1].pos[1]);
    for (i = 0; i < nProjeteis; i++) {
        printf(" | (%7.2lf, %7.2lf)", i, projeteis[i].pos[0], projeteis[i].pos[1]);
    }
    printf("\n");
}
