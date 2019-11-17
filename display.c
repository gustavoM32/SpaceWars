#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "objetos.h"
#include "display.h"
#include "fisica.h"
#include "game.h"
#include "util.h"
#include "debug.h"

void carregaSprite(PIC win, char nome[], int width, int height, Sprite *s) {
    char path[] = "assets/sprites/";
    char nomeSprite[256];
    sprintf(nomeSprite, "%s%s.xpm", path, nome);
    s->width = width;
    s->height = height;
    s->mask = NewMask(win, width, height);
    s->img = ReadPic(win, nomeSprite, s->mask);
}

void carregaRots(PIC win, char nome[], int width, int height, Sprite s[]) {
    int i;
    for (i = 0; i < NUM_ROTACOES; i++) {
        char nomeRot[256];
        sprintf(nomeRot, "%s - %d", nome, i);
        carregaSprite(win, nomeRot, width, height, &(s[i]));
    }
}

void carregaAnims(PIC win, char nome[], int frames, int width, int height, Sprite s[]) {
    int i;
    for (i = 0; i < frames; i++) {
        char nomeFrame[256];
        sprintf(nomeFrame, "%s - %d", nome, i);
        carregaSprite(win, nomeFrame, width, height, &(s[i]));
    }
}

void carregaObjetos(PIC win) {
    db(printf("Carregando planeta...\n"));
    carregaSprite(win, "planeta/planeta", 100, 100, &(sprites.planetaS));
    db(printf("Carregando nave1...\n"));
    carregaRots(win, "nave1/nave1", 50, 50, sprites.nave[0]);
    db(printf("Carregando nave2...\n"));
    carregaRots(win, "nave2/nave2", 50, 50, sprites.nave[1]);
    db(printf("Carregando projetil1...\n"));
    carregaRots(win, "projetil1/projetil1", 50, 50, sprites.projetil);
    db(printf("Carregando explosion...\n"));
    carregaAnims(win, "exp/explosion", 15, 50, 60, sprites.explosao);
}

int calculaDirecaoN(double dir[2]) {
    double intervalo = 2*PI / NUM_ROTACOES;
    double norma = calcNorma(dir);
    if (norma <= EPSILON) return 0;
    double angulo = acos(dir[1] / norma);
    if (dir[0] < 0) angulo = 2*PI - angulo;
    angulo += intervalo / 2;
    angulo /= intervalo;
    return (int) angulo % NUM_ROTACOES;
}

int calculaFrame(Objeto *obj) {
    int ticksPerSecond = FRAMES_PER_SECOND * TICKS_PER_FRAME;
    int frame = (getTick() - obj->oAnim->inicio) * obj->oAnim->frames / ticksPerSecond / obj->oAnim->duracao;
    return frame < obj->oAnim->frames ? frame : obj->oAnim->frames;
}

void imprimeSprite(PIC dest, Objeto *obj, int dir) {
    double vet[2];
    transforma(obj->pos, vet);
    SetMask(dest, obj->s[dir].mask);
    PutPic(dest, obj->s[dir].img, 0, 0, obj->s[dir].width, obj->s[dir].height, vet[0] - obj->s[dir].width/2, vet[1] - obj->s[dir].height/2);
    UnSetMask(dest);
}

void imprimaObjetos(PIC pic) {
    Objeto *obj;
    double vet[2];
    for (obj = objetos.iniObjs->prox; obj != NULL; obj = obj->prox) {
        switch (obj->categoria) {
            case PLANETA:
                imprimeSprite(pic, obj, 0);
                break;
            case NAVE:
                vet[0] = cos(obj->ang);
                vet[1] = sin(obj->ang);
                imprimeSprite(pic, obj, calculaDirecaoN(vet));
                break;
            case PROJETIL:
                imprimeSprite(pic, obj, calculaDirecaoN(obj->vel));
                break;
            case ANIMACAO:
                imprimeSprite(pic, obj, calculaFrame(obj));
                break;
            default:
                printf("imprimaObjetos(): Tipo indefinido.\n");
                exit(EXIT_FAILURE);
        }
    }
}
