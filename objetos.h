#ifndef OBJETOS_H
#define OBJETOS_H

#include "xwc.h"

#define MAX_OBJETOS 1024
#define TEMPO_DISP 1

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
    double ang;
    int alive;
} Objeto;

typedef struct planeta {
    Objeto *obj;
} Planeta;

typedef struct nave {
    Objeto *obj;
    int ultima;
    char nome[80];
} Nave;

typedef struct projetil {
    Objeto *obj;
    double duracao;
    int criado;
} Projetil;

Planeta planeta;
Nave nave[2];
int nProjeteis;
double duracaoProjetil;
Projetil projeteis[MAX_OBJETOS];
int nObjetos;
Objeto *objetos[MAX_OBJETOS];

/*
    criaObjeto()

    Cria um novo objeto e adiciona ele no vetor objetos.
 */
Objeto *criaObjeto();

void disparaProjetil(Nave *a);

/*
    mataObjetos()

    Destrói todos os objetos marcados como mortos.
 */
void mataObjetos();

#endif
