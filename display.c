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
    int i, j;
    char nome[100];
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

    db(printf("Carregando botões do menu...\n"));
    carregaSprite(win, "botoes/Jogar-off", 200, 100, &(sprites.botao[0][0].s));
    carregaSprite(win, "botoes/Jogar-on", 200, 100, &(sprites.botao[0][1].s));
    carregaSprite(win, "botoes/Ajuda-off", 200, 100, &(sprites.botao[1][0].s));
    carregaSprite(win, "botoes/Ajuda-on", 200, 100, &(sprites.botao[1][1].s));
    carregaSprite(win, "botoes/Sair-off", 200, 100, &(sprites.botao[2][0].s));
    carregaSprite(win, "botoes/Sair-on", 200, 100, &(sprites.botao[2][1].s));

    db(printf("Carregando coração S2...\n"));
    carregaSprite(win, "coracao/coracao", 50, 40, &(sprites.coracao.s));

    db(printf("Carregando contagem...\n"));
    carregaSprite(win, "contagem/contagem - 1", 200, 200, &(sprites.contagem[0].s));
    carregaSprite(win, "contagem/contagem - 2", 200, 200, &(sprites.contagem[1].s));
    carregaSprite(win, "contagem/contagem - 3", 200, 200, &(sprites.contagem[2].s));
    for (i = 0; i < 3; i++) {
        sprites.contagem[i].pos[0][0] = WIDTH/2;
        sprites.contagem[i].pos[0][1] = HEIGHT/2;
    }
    carregaSprite(win, "contagem/go", 404, 246, &(sprites.go.s));
    sprites.go.pos[0][0] = WIDTH/2;
    sprites.go.pos[0][1] = HEIGHT/2;

    db(printf("Carregando trophy...\n"));
    for (i = 0; i < 60; i++) {
        sprintf(nome, "trophy/%d", i);
        carregaSprite(win, nome, 100, 100, &(sprites.trophy[i].s));
        sprites.trophy[i].pos[0][0] = WIDTH/2;
        sprites.trophy[i].pos[0][1] = HEIGHT/2 - 100;
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++) {
            sprites.botao[i][j].pos[0][0] = WIDTH/2;
            sprites.botao[i][j].pos[0][1] = HEIGHT/2 + (i - 1)*120;
        }
    }

    for (i = 0; i < 3; i++) {
        sprites.coracao.pos[i][0] = 40 + 40*i;
        sprites.coracao.pos[i][1] = 30;
        sprites.coracao.pos[3+i][0] = WIDTH - 40 - 40*i;
        sprites.coracao.pos[3+i][1] = 30;
    }
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

void imprimeSprite(PIC dest, Objeto *obj, int ind) {
    double vet[2];
    transforma(obj->pos, vet);
    if (obj->s[ind].mask == NULL) return;
    SetMask(dest, obj->s[ind].mask);
    PutPic(dest, obj->s[ind].img, 0, 0, obj->s[ind].width, obj->s[ind].height, vet[0] - obj->s[ind].width/2, vet[1] - obj->s[ind].height/2);
    UnSetMask(dest);
}

void imprimeFixed(PIC dest, Fixed *fixed, int ind) {
    if (fixed->s.mask == NULL) return;
    SetMask(dest, fixed->s.mask);
    PutPic(dest, fixed->s.img, 0, 0, fixed->s.width, fixed->s.height, fixed->pos[ind][0] - fixed->s.width/2, fixed->pos[ind][1] - fixed->s.height/2);
    UnSetMask(dest);
}

void imprimaObjetos(PIC pic) {
    Objeto *obj;
    double vet[2];
    int i, j;
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
