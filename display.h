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

typedef struct animacao {
    double pos[2];
    int frames;
    int width;
    int height;
    double duracao;
    int inicio;
    Sprite *s;
} Animacao;

Sprite naves[2][NUM_ROTACOES];
Sprite projetil[NUM_ROTACOES];
Sprite planetaS;
Sprite explosao[MAX_FRAMES];
int nAnimacoes;
Animacao animacoes[MAX_ANIMS];

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
void criaAnimacao(double pos[], int width, int height, int frames, int duracao, Sprite *s);

/*
    calculaDirecaoN()

    Calcula a direção discreta do vetor dir.

    Parâmetros:
        dir[] - vetor cuja direção será calculada
*/
int calculaDirecaoN(double dir[2]);

/*
    imprimeSprite()

    Imprime o sprite s em dest.

    Parâmetros:
        dest - PIC em que será impresso o sprite
        s - sprite a ser impresso
        width - largura do sprite
        height - altura do sprite
        pos[] - posição do objeto que o sprite representa
*/
void imprimeSprite(PIC dest, Sprite *s, int width, int height, double pos[2]);

/*
    imprimeRot()

    Imprime o sprite s em dest de acordo com a orientação
    do objeto que ele representa.

    Parâmetros:
        dest - PIC em que será impresso o sprite
        s[] - sprite a ser impresso
        width - largura do sprite
        height - altura do sprite
        pos[] - posição do objeto que o sprite representa
        vel[] - veliocidade do objeto que o sprite representa
*/
void imprimeRot(PIC dest, Sprite s[], int dim, double pos[2], double vel[2]);

/*
    imprimaObjetos()

    Realiza todas as chamadas para impressão de objetos em
    um dado instante.

    Parâmetros:
        pic - PIC em que serão feitas as impressões
*/
void imprimaObjetos(PIC pic);
#endif
