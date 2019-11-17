#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "objetos.h"
#include "display.h"
#include "fisica.h"
#include "tick.h"
#include "util.h"

void carregaSprite(PIC win, char nome[], int width, int height, Sprite *s) {
    char path[] = "assets/sprites/";
    char nomeSprite[256];
    sprintf(nomeSprite, "%s%s.xpm", path, nome);
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
    printf("Carregando planeta...\n");
    carregaSprite(win, "planeta/planeta", 100, 100, &planetaS);
    printf("Carregando nave1...\n");
    carregaRots(win, "nave1/nave1", 50, 50, naves[0]);
    printf("Carregando nave2...\n");
    carregaRots(win, "nave2/nave2", 50, 50, naves[1]);
    printf("Carregando projetil1...\n");
    carregaRots(win, "projetil1/projetil1", 50, 50, projetil);
    printf("Carregando explosion...\n");
    carregaAnims(win, "exp/explosion", 15, 50, 60, explosao);
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

void imprimeSprite(PIC dest, Sprite *s, int width, int height, double pos[2]) {
    SetMask(dest, s->mask);
    PutPic(dest, s->img, 0, 0, width, height, pos[0] - width/2, pos[1] - height/2);
    UnSetMask(dest);
}

void imprimeRot(PIC dest, Sprite s[], int dim, double pos[2], double dir[2]) {
    double novaPos[2];
    transforma(pos, novaPos);
    int direcao = calculaDirecaoN(dir);
    imprimeSprite(dest, s+direcao, dim, dim, novaPos);
}

void imprimeAnims(PIC dest, Objeto *a) {
    double novaPos[2];
    int ticksPerSecond = FRAMES_PER_SECOND * TICKS_PER_FRAME;
    int frame = (getTick() - a->oAnim->inicio) * a->oAnim->frames / ticksPerSecond / a->oAnim->duracao;
    if (frame >= a->oAnim->frames) return;
    transforma(a->pos, novaPos);
    imprimeSprite(dest, a->s+frame, a->oAnim->width, a->oAnim->height, novaPos);
}

void imprimaObjetos(PIC pic) {
    Objeto *obj;
    double vet[2];
    for (obj = listaObjetos->prox; obj != NULL; obj = obj->prox) {
        switch (obj->categoria) {
            case PLANETA:
                transforma(planeta->pos, vet);
                imprimeSprite(pic, obj->s, 100, 100, vet);
                break;
            case NAVE:
                vet[0] = cos(obj->ang);
                vet[1] = sin(obj->ang);
                imprimeRot(pic, obj->s, 50, obj->pos, vet);
                break;
            case PROJETIL:
                imprimeRot(pic, obj->s, 50, obj->pos, obj->vel);
                break;
            case ANIMACAO:
                imprimeAnims(pic, obj);
                break;
            default:
                printf("imprimaObjetos(): Tipo indefinido.\n");
                exit(EXIT_FAILURE);
        }
    }
}
