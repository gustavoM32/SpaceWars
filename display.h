#ifndef DISPLAY_H
#define DISPLAY_H

#include "xwc.h"
#include "fisica.h"

#define WIDTH 1000
#define HEIGHT 600
#define FATOR 100000

/* Quantidade de rotacoes do sprite */
#define NUM_ROTACOES 32
#define MAX_FRAMES 32
#define MAX_ANIMS 128

typedef struct sprites {
    Sprite nave[2][NUM_ROTACOES];
    Sprite projetil[NUM_ROTACOES];
    Sprite planetaS;
    Sprite explosao[MAX_FRAMES];
} Sprites;

Sprites sprites;

/*
    carregaSprite()

    Carrega um sprite da pasta sprites.

    Parâmetros:
        win - janela de exibição
        nome[] - nome do que deve ser carregado
        width - largura do sprite
        height - altura do sprite
        s - apontador para onde o sprite deve ser armazenado
*/
void carregaSprite(PIC win, char nome[], int width, int height, Sprite *s);

/*
    carregaRots()

    Carrega os sprites das rotações de um objeto.

    Parâmetros:
        win - janela de exibição
        nome[] - nome do objeto
        width - largura dos sprites
        height - altura dos sprites
        s[] - vetor onde os sprites devem ser armazenados
*/
void carregaRots(PIC win, char nome[], int width, int height, Sprite s[]);

/*
    carregaAnims()

    Carrega os sprites de uma animação.

    Parâmetros:
        win - janela de exibição
        nome[] - nome da animação
        frames - número de frames da animação
        width - largura dos frames
        height - altura dos frames
        s[] - vetor onde os frames da animação devem ser armazenados
*/
void carregaAnims(PIC win, char nome[], int frames, int width, int height, Sprite s[]);

/*
    carregaObjetos()

    Carrega todas as imagens usadas pelo programa

    Parâmetros:
        win - janela de exibição
*/
void carregaObjetos(PIC win);

/*
    calculaDirecaoN()

    Calcula a direção discreta do vetor dir.

    Parâmetros:
        dir[] - vetor cuja direção será calculada
*/
int calculaDirecaoN(double dir[2]);

/*
    calculaFrame()

    Calcula o frame atual da animação.

    Parâmetros:
        obj - apontador para objeto de categoria ANIMACAO
*/
int calculaFrame(Objeto *obj);

/*
    imprimeSprite()

    Imprime o sprite de obj em dest.

    Parâmetros:
        dest - PIC em que será impresso o sprite
        obj - objeto a ser impresso
        ind - posição do sprite no vetor de sprites do objeto
*/
void imprimeSprite(PIC dest, Objeto *obj, int ind);

/*
    imprimaObjetos()

    Realiza todas as chamadas para impressão de objetos em
    um dado instante.

    Parâmetros:
        pic - PIC em que serão feitas as impressões
*/
void imprimaObjetos(PIC pic);
#endif
