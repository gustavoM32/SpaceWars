#include "objetos.h"
#include "tick.h"

void mataObjetos() {
    int i = 0;
    int j = 0;
    int ticksPerSec = (FRAMES_PER_SECOND * TICKS_PER_FRAME);
    if (!nave1.alive) {
        nave1.massa = 0;
        nave1.pos[0] = nave1.pos[1] = 0;
        nave1.raio = 0;
    }
    if (!nave2.alive) {
        nave2.massa = 0;
        nave2.pos[0] = nave2.pos[1] = 0;
        nave2.raio = 0;
    }
    for (i = 0; i < nProjeteis; i++) {
        if (!projeteis[i].alive || (projeteis[i].criado + projeteis[i].duracao * ticksPerSec) < getTick()) continue;
        projeteis[j++] = projeteis[i];
    }
    nProjeteis = j;
}
