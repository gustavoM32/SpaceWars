#ifndef OBJETOS_H
#define OBJETOS_H

#include "xwc.h"
#include "display.h"

#define MAXN 10000

typedef struct planeta {
    double massa;
    double raio;
    double pos[2];
} Planeta;

typedef struct nave {
    char nome[80];
    double massa;
    double raio;
    double pos[2];
    double vel[2];
    double res[2];
    double dir[2];
    int alive;
} Nave;

typedef struct projetil {
    double massa;
    double raio;
    double pos[2];
    double vel[2];
    double res[2];
    double duracao;
    int criado;
    int alive;
} Projetil;

typedef struct explosao {
    PIC imgs[NUM_ROTACOES];
    MASK masks[NUM_ROTACOES];
} Explosao;

int nProjeteis;
Planeta planeta;
Nave nave1, nave2;
Projetil projeteis[MAXN];
//Explosao explosao;

void mataObjetos();

#endif
