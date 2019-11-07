#include "objetos.h"
#include "tick.h"
#include "display.h"

void mataObjetos() {
    int i, j;
    int ticksPerSec = (FRAMES_PER_SECOND * TICKS_PER_FRAME);
    if (!nave1.alive) {
        if (!nave1.explodiu) criaAnimacao(nave1.pos, 50, 60, 15, 1, explosao);
        nave1.explodiu = 1;
        nave1.massa = 0;
        nave1.pos[0] = nave1.pos[1] = 0;
        nave1.raio = 0;
    }
    if (!nave2.alive) {
        if (!nave2.explodiu) criaAnimacao(nave2.pos, 50, 60, 15, 1, explosao);
        nave2.explodiu = 1;
        nave2.massa = 0;
        nave2.pos[0] = nave2.pos[1] = 0;
        nave2.raio = 0;
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
