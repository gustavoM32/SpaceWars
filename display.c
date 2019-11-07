#include <stdio.h>
#include <math.h>
#include "objetos.h"
#include "display.h"
#include "fisica.h"

void carregaSprite(PIC win, char nome[], int width, int height, Sprite *s) {
    char path[] = "assets/sprites/";
    char nomeSprite[256];
    sprintf(nomeSprite, "%s%s.xpm", path, nome);
    s->mask = NewMask(win, width, height);
    s->img = ReadPic(win, nomeSprite, s->mask);
}

void carregaSprites(PIC win, char nome[], int width, int height, Sprite s[]) {
    int i;
    for (i = 0; i < NUM_ROTACOES; i++) {
        char nomeRot[256];
        sprintf(nomeRot, "%s - %d", nome, i);
        carregaSprite(win, nomeRot, width, height, &(s[i]));
    }
}

void carregaObjetos(PIC win) {
    printf("Carregando planeta...\n");
    carregaSprite(win, "planeta", 100, 100, &planetaS);
    printf("Carregando nave1...\n");
    carregaSprites(win, "nave1", 50, 50, naves[0]);
    printf("Carregando nave2...\n");
    carregaSprites(win, "nave2", 50, 50, naves[1]);
    printf("Carregando projetil1...\n");
    carregaSprites(win, "projetil1", 50, 50, projetil);
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

void imprimeSprite(PIC dest, Sprite s, int width, int height, double pos[2]) {
    SetMask(dest, s.mask);
    PutPic(dest, s.img, 0, 0, width, height, pos[0] - width/2, pos[1] - height/2);
    UnSetMask(dest);
}

void imprimeRot(PIC dest, Sprite s[], int dim, double pos[2], double vel[2]) {
    double novaPos[2];
    transforma(pos, novaPos);
    //printf("(%7.2lf, %7.2lf) | ", novaPos[0], novaPos[1]);
    int dir = calculaDirecaoN(vel);
    imprimeSprite(dest, s[dir], dim, dim, novaPos);
}

void imprimaObjetos(PIC pic) {
    int i;
    double novaPos[2];
    transforma(planeta.pos, novaPos);
    imprimeSprite(pic, planetaS, 100, 100, novaPos);
    if (nave1.alive) imprimeRot(pic, naves[0], 50, nave1.pos, nave1.vel);
    if (nave2.alive) imprimeRot(pic, naves[1], 50, nave2.pos, nave2.vel);
    for (i = 0; i < nProjeteis; i++)
        imprimeRot(pic, projetil, 50, projeteis[i].pos, projeteis[i].vel);

    //printf("\n");
}
