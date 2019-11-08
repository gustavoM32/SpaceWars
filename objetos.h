#ifndef OBJETOS_H
#define OBJETOS_H

#include "xwc.h"
#include "display.h"

#define MAX_OBJETOS 1024

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
    int explodiu;
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

Planeta planeta;
Nave nave[2];
int nProjeteis;
Projetil projeteis[MAX_OBJETOS];

void mataObjetos();

#endif
