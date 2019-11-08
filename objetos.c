#include <stdio.h>
#include "objetos.h"
#include "tick.h"
#include "display.h"
#include "util.h"
#include "debug.h"

void mataObjetos() {
    int i, j;
    int ticksPerSec = (FRAMES_PER_SECOND * TICKS_PER_FRAME);
    for (i = 0; i < 2; i++) {
        if (!nave[i].alive) {
            if (!nave[i].explodiu) {
                db(printf("Nave %d explodiu.\n", i+1));
                criaAnimacao(nave[i].pos, 50, 60, 15, 1, explosao);
                nave[i].explodiu = 1;
                nave[i].massa = 0;
                nave[i].pos[0] = nave[i].pos[1] = 0;
                nave[i].raio = 0;
            }
        }
    }

    for (i = 0, j = 0; i < nProjeteis; i++) {
        if (!projeteis[i].alive || (projeteis[i].criado + projeteis[i].duracao * ticksPerSec) < getTick()) continue;
        projeteis[j++] = projeteis[i];
    }
    nProjeteis = j;

    for (i = 0, j = 0; i < nAnimacoes; i++) {
        if ((animacoes[i].inicio + animacoes[i].duracao * ticksPerSec) < getTick()) continue;
        animacoes[j++] = animacoes[i];
    }
    nAnimacoes = j;
}
