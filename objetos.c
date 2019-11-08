#include <stdio.h>
#include <stdlib.h>
#include "objetos.h"
#include "tick.h"
#include "display.h"
#include "util.h"
#include "debug.h"

Objeto *criaObjeto() {
    Objeto *novo = (Objeto *) mallocSafe(sizeof(Objeto));
    int i = 0;
    novo->massa = 0.0;
    novo->raio = 0.0;
    for (i = 0; i < 2; i++) {
        novo->pos[i] = 0.0;
        novo->vel[i] = 0.0;
        novo->res[i] = 0.0;
    }
    novo->alive = 1;
    objetos[nObjetos++] = novo;
    return novo;
}

void mataObjetos() {
    int i, j;
    int ticksPerSec = (FRAMES_PER_SECOND * TICKS_PER_FRAME);
    for (i = 0; i < 2; i++) {
        if (nave[i].obj != NULL && !nave[i].obj->alive) {
            db(printf("Nave %d explodiu.\n", i+1));
            criaAnimacao(nave[i].obj->pos, 50, 60, 15, 1, explosao);
            nave[i].obj = NULL;
        }
    }

    for (i = 0, j = 0; i < nProjeteis; i++) {
        if (!projeteis[i].obj->alive || (projeteis[i].criado + projeteis[i].duracao * ticksPerSec) < getTick()) continue;
        projeteis[j++] = projeteis[i];
    }
    nProjeteis = j;

    for (i = 0, j = 0; i < nObjetos; i++) {
        if (!objetos[i]->alive) {
            free(objetos[i]);
            continue;
        }
        objetos[j++] = objetos[i];
    }
    nObjetos = j;

    for (i = 0, j = 0; i < nAnimacoes; i++) {
        if ((animacoes[i].inicio + animacoes[i].duracao * ticksPerSec) < getTick()) continue;
        animacoes[j++] = animacoes[i];
    }
    nAnimacoes = j;
}
