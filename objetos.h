#ifndef OBJETOS_H
#define OBJETOS_H

#include "xwc.h"

#define OPTIONS_LIMIT 3
#define TEMPO_DISP 0.5

typedef enum categoria Categoria;
typedef struct sprite Sprite;
typedef struct objeto Objeto;
typedef struct nave Nave;
typedef struct projetil Projetil;
typedef struct animacao Animacao;
typedef struct botao Botao;
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

    Cria um novo objeto e adiciona ele na lista ligada de objetos.
 */
Objeto *criaObjeto();

/*
    criaNave()

    Cria nave e adiciona na lista ligada de objetos.

    Parâmetros:
        id - 0 ou 1
*/
Objeto *criaNave(int id);

/*
    criaProjetil()

    Cria projetil e adiciona na lista ligada de objetos.
*/
Objeto *criaProjetil();

/*
    criaAnimacao()

    Cria uma animação e adiciona na lista ligada de objetos.

    Parâmetros:
        pos[] - posição da animação
        frames - número de frames da animação
        duracao - duração em segundos da animação
        s - vetor dos frames da animação
*/
Objeto *criaAnimacao(double pos[], int frames, double duracao, Sprite *s);

/*
    criaObjetos()

    Cria todos os objetos iniciais do jogo.
*/
void criaObjetos();

/*
    freeObjeto()

    Libera a memória usada por um objeto.

    Parâmetros:
        obj - apontador para o objeto
*/
void freeObjeto(Objeto *obj);

/*
    freeObjetos()

    Libera a memória usada por todos os objetos.
*/
void freeObjetos();

/*
    disparaProjetil()

    Dispara um projétil partindo do objeto a.

    Parâmetros:
        a - apontador para o objeto a
*/
void disparaProjetil(Objeto *a);

/*
    mataObjetos()

    Destrói todos os objetos marcados como mortos.
*/
void mataObjetos();

#endif
