#ifndef OBJETOS_H
#define OBJETOS_H

#include "xwc.h"

#define MAX_OBJETOS 1024

typedef struct sprite {
    PIC img;
    MASK mask;
} Sprite;

enum objetos {
    PLANETA,
    NAVE,
    PROJETIL
};

typedef enum objetos TipoObjeto;

typedef struct objeto {
    TipoObjeto tipo;
    Sprite *img;
    double massa;
    double raio;
    double pos[2];
    double vel[2];
    double res[2];
    int alive;
} Objeto;

typedef struct planeta {
    Objeto *obj;
} Planeta;

typedef struct nave {
    Objeto *obj;
    char nome[80];
    double dir[2];
} Nave;

typedef struct projetil {
    Objeto *obj;
    double duracao;
    int criado;
} Projetil;

Planeta planeta;
Nave nave[2];
int nProjeteis;
Projetil projeteis[MAX_OBJETOS];
int nObjetos;
Objeto *objetos[MAX_OBJETOS];

Objeto *criaObjeto();

void mataObjetos();

#endif
