#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "objetos.h"
#include "display.h"
#include "fisica.h"
#include "tick.h"

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
    carregaSprite(win, "planeta", 100, 100, &planetaS);
    printf("Carregando nave1...\n");
    carregaRots(win, "nave1", 50, 50, naves[0]);
    printf("Carregando nave2...\n");
    carregaRots(win, "nave2", 50, 50, naves[1]);
    printf("Carregando projetil1...\n");
    carregaRots(win, "projetil1", 50, 50, projetil);
    printf("Carregando explosion...\n");
    carregaAnims(win, "exp/explosion", 15, 50, 60, explosao);
}

void criaAnimacao(double pos[], int width, int height, int frames, int duracao, Sprite *s) {
    animacoes[nAnimacoes].pos[0] = pos[0];
    animacoes[nAnimacoes].pos[1] = pos[1];
    animacoes[nAnimacoes].width = width;
    animacoes[nAnimacoes].height = height;
    animacoes[nAnimacoes].frames = frames;
    animacoes[nAnimacoes].duracao = duracao;
    animacoes[nAnimacoes].inicio = getTick();
    animacoes[nAnimacoes].s = s;
    nAnimacoes++;
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

void imprimeRot(PIC dest, Sprite s[], int dim, double pos[2], double vel[2]) {
    double novaPos[2];
    transforma(pos, novaPos);
    //printf("(%7.2lf, %7.2lf) | ", novaPos[0], novaPos[1]);
    int dir = calculaDirecaoN(vel);
    imprimeSprite(dest, s+dir, dim, dim, novaPos);
}

void imprimeAnims(PIC dest, Animacao a) {
    double novaPos[2];
    int ticksPerSecond = FRAMES_PER_SECOND * TICKS_PER_FRAME;
    int frame = (getTick() - a.inicio) * a.frames / ticksPerSecond / a.duracao;
    if (frame >= a.frames) return;
    transforma(a.pos, novaPos);
    imprimeSprite(dest, a.s+frame, a.width, a.height, novaPos);
}

void imprimaObjetos(PIC pic) {
    int i;
    double novaPos[2];
    transforma(planeta.obj->pos, novaPos);
    for (i = 0; i < nObjetos; i++) {
        switch (objetos[i]->tipo) {
            case PLANETA:
                imprimeSprite(pic, objetos[i]->img, 100, 100, novaPos);
                break;
            case NAVE:
                imprimeRot(pic, objetos[i]->img, 50, objetos[i]->pos, objetos[i]->vel);
                break;
            case PROJETIL:
                imprimeRot(pic, objetos[i]->img, 50, objetos[i]->pos, objetos[i]->vel);
                break;
            default:
                printf("imprimaObjetos(): Tipo indefinido.\n");
                exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < nAnimacoes; i++) {
        imprimeAnims(pic, animacoes[i]);
    }
}
