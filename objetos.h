#ifndef OBJETOS_H
#define OBJETOS_H

#include "xwc.h"

#define MAX_OBJETOS 1024
#define TEMPO_DISP 0.3

typedef enum objetos Categoria;
typedef struct sprite Sprite;
typedef struct objeto Objeto;
typedef struct nave Nave;
typedef struct projetil Projetil;
typedef struct animacao Animacao;
typedef union subObj SubObj;

enum objetos {
    PLANETA,
    NAVE,
    PROJETIL,
    ANIMACAO
};

struct sprite {
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
    int width;
    int height;
    double duracao;
    int inicio;
};

Objeto *planeta;
Objeto *nave[2];
double duracaoProjetil;
Objeto *listaObjetos;
Objeto *fimListaObjetos;

/*
    criaObjeto()

    Cria um novo objeto e adiciona ele no vetor objetos.
 */
Objeto *criaObjeto();

Objeto *criaNave();

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
Objeto *criaAnimacao(double pos[], int width, int height, int frames, int duracao, Sprite *s);

void disparaProjetil(Objeto *a);

/*
    mataObjetos()

    Destrói todos os objetos marcados como mortos.
 */
void mataObjetos();

#endif
