#ifndef OBJETOS_H
#define OBJETOS_H

#include "xwc.h"

#define MAX_OBJETOS 1024
#define TEMPO_DISP 0.3

typedef enum categoria Categoria;
typedef struct sprite Sprite;
typedef struct objeto Objeto;
typedef struct nave Nave;
typedef struct projetil Projetil;
typedef struct animacao Animacao;
typedef struct objetos Objetos;
typedef union subObj SubObj;

enum categoria {
    PLANETA,
    NAVE,
    PROJETIL,
    ANIMACAO
};

struct sprite {
    int width;
    int height;
    PIC img;
    MASK mask;
};

union subObj {
    Nave *nave;
    Projetil *projetil;
    Animacao *animacao;
};

struct objeto {
    Categoria categoria;
    SubObj subObj;
    Sprite *s;
    double massa;
    double raio;
    double pos[2];
    double vel[2];
    double res[2];
    double ang;
    int alive;
    Objeto *prox;
};

struct nave {
    int id;
    int ultimoDisparo;
    char nome[80];
};

struct projetil {
    double duracao;
    int criado;
};

struct animacao {
    int frames;
    double duracao;
    int inicio;
};

struct objetos {
    Objeto *planeta;
    Objeto *nave[2];
    Objeto *iniObjs;
    Objeto *fimObjs;
};

Objetos objetos;

/*
    criaObjeto()

    Cria um novo objeto e adiciona ele no vetor objetos.
 */
Objeto *criaObjeto();

Objeto *criaNave(int id);

Objeto *criaProjetil();

/*
    criaAnimacao()

    Adiciona uma animação na lista de animações ativas na tela.

    Parâmetros:
        pos[] - posição da animação
        width - largura da animação
        height - altura da animação
        frames - número de frames da animação
        duracao - duração em segundos da animação
        s - vetor dos frames da animação
*/
Objeto *criaAnimacao(double pos[], int frames, int duracao, Sprite *s);

void criaObjetos();

void freeObjeto(Objeto *obj);

void freeObjetos();

void disparaProjetil(Objeto *a);

/*
    mataObjetos()

    Destrói todos os objetos marcados como mortos.
 */
void mataObjetos();

#endif
