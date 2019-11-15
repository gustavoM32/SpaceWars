#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

void disparaProjetil(Nave *a) {
    if (getTick() - a->ultima < TEMPO_DISP * FRAMES_PER_SECOND * TICKS_PER_FRAME) return;
    a->ultima = getTick();
    projeteis[nProjeteis].obj = criaObjeto();
    projeteis[nProjeteis].obj->tipo = PROJETIL;
    projeteis[nProjeteis].obj->img = projetil;
    projeteis[nProjeteis].obj->alive = 1;
    projeteis[nProjeteis].obj->raio = 4;
    projeteis[nProjeteis].obj->massa = 2;
    projeteis[nProjeteis].obj->pos[0] = a->obj->pos[0] + 40 * FATOR * cos(a->obj->ang);
    projeteis[nProjeteis].obj->pos[1] = a->obj->pos[1] + 40 * FATOR * sin(a->obj->ang);
    projeteis[nProjeteis].obj->vel[0] = 400 * FATOR * cos(a->obj->ang);
    projeteis[nProjeteis].obj->vel[1] = 400 * FATOR * sin(a->obj->ang);
    projeteis[nProjeteis].duracao = duracaoProjetil;
    printf("!!!!criado em %d\n", getTick());
    projeteis[nProjeteis].criado = getTick();
    nProjeteis++;
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
        if (projeteis[i].criado + projeteis[i].duracao * ticksPerSec < getTick()) projeteis[i].obj->alive = 0;
        if (!projeteis[i].obj->alive) continue;
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
