#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "objetos.h"
#include "io.h"
#include "game.h"
#include "display.h"
#include "util.h"
#include "game.h"
#include "debug.h"
#include "sounds.h"

Objeto *criaObjeto(int addObjs) {
    Objeto *novo = (Objeto *) mallocSafe(sizeof(Objeto));
    int i;
    novo->massa = 0.0;
    novo->raio = 0.0;
    for (i = 0; i < 2; i++) {
        novo->pos[i] = 0.0;
        novo->vel[i] = 0.0;
        novo->res[i] = 0.0;
    }
    novo->alive = 1;
    if (addObjs) {
        novo->prox = NULL;
        objetos.fimObjs = objetos.fimObjs->prox = novo;
    }
    return novo;
}

Objeto *criaNave(int id) {
    Objeto *novo = criaObjeto(1);
    novo->categoria = NAVE;
    novo->raio = 15;
    novo->s = sprites.nave[id];
    novo->ang = PI/2 + id*PI;
    novo->oNave = (Nave *) mallocSafe(sizeof(Nave));
    novo->oNave->id = id;
    novo->oNave->ultimoDisparo = 0;
    strcpy(novo->oNave->nome, "nave");
    return novo;
}

Objeto *criaProjetil() {
    Objeto *novo = criaObjeto(1);
    novo->categoria = PROJETIL;
    novo->s = sprites.projetil;
    novo->raio = 4;
    novo->oProj = (Projetil *) mallocSafe(sizeof(Projetil));
    novo->oProj->duracao = config.duracaoProjetil;
    novo->oProj->criado = getTick();
    return novo;
}

Objeto *criaAnimacao(double pos[], int frames, double duracao, Sprite *s) {
    Objeto *novo = criaObjeto(1);
    novo->oAnim = (Animacao *) mallocSafe(sizeof(Animacao));
    novo->s = s;
    novo->categoria = ANIMACAO;
    novo->pos[0] = pos[0];
    novo->pos[1] = pos[1];
    novo->oAnim->frames = frames;
    novo->oAnim->duracao = duracao;
    novo->oAnim->inicio = getTick();
    return novo;
}

void criaObjetos() {
    int i, j;
    objetos.fimObjs = objetos.iniObjs = (Objeto *) mallocSafe(sizeof(Objeto));
    objetos.iniObjs->prox = NULL;

    objetos.planeta = criaObjeto(1);
    objetos.planeta->categoria = PLANETA;
    objetos.planeta->s = &(sprites.planetaS);
    objetos.planeta->raio = 45;

    for (i = 0; i < 2; i++) {
        objetos.nave[i] = criaNave(i);
    }

    leiaArquivo();
}

void freeObjeto(Objeto *obj) {
    switch (obj->categoria) {
        case PLANETA:
            break;
        case NAVE:
            free(obj->oNave);
            break;
        case PROJETIL:
            free(obj->oProj);
            break;
        case ANIMACAO:
            free(obj->oAnim);
            break;
        default:
            printf("freeObjeto(): Tipo indefinido.\n");
            exit(EXIT_FAILURE);
    }
    free(obj);
}

void freeObjetos() {
    Objeto *atual = objetos.iniObjs->prox;
    Objeto *del;
    while (atual != NULL) {
        del = atual;
        atual = atual->prox;
        freeObjeto(del);
    }
    objetos.iniObjs->prox = NULL;
    objetos.fimObjs = objetos.iniObjs;
}

void disparaProjetil(Objeto *a) {
    Objeto *novo;
    if (getTick() - a->oNave->ultimoDisparo < TEMPO_DISP * FRAMES_PER_SECOND * TICKS_PER_FRAME) return;
    playSound(LASER_SOUND);
    a->oNave->ultimoDisparo = getTick();
    novo = criaProjetil();
    novo->massa = 2;
    novo->pos[0] = a->pos[0] + 40 * FATOR * cos(a->ang);
    novo->pos[1] = a->pos[1] + 40 * FATOR * sin(a->ang);
    novo->vel[0] = 400 * FATOR * cos(a->ang);
    novo->vel[1] = 400 * FATOR * sin(a->ang);
}

void mataObjetos() {
    int ticksPerSec = (FRAMES_PER_SECOND * TICKS_PER_FRAME);
    Objeto *fimLista = objetos.iniObjs;
    Objeto *atual = objetos.iniObjs->prox;
    while (atual != NULL) {
        switch (atual->categoria) {
            case PLANETA:
                break;
            case NAVE:
                if (!atual->alive) {
                    db(printf("Nave '%s' explodiu.\n", atual->oNave->nome));
                    playSound(EXPLOSION_SOUND);
                    criaAnimacao(atual->pos, 15, 1, sprites.explosao);
                    objetos.nave[atual->oNave->id] = NULL;
                }
                break;
            case PROJETIL:
                if (atual->oProj->criado + atual->oProj->duracao * ticksPerSec < getTick()) atual->alive = 0;
                break;
            case ANIMACAO:
                if (atual->oAnim->inicio + atual->oAnim->duracao * ticksPerSec < getTick()) {
                    atual->alive = 0;
                }
                break;
            default:
                printf("mataObjetos(): Tipo indefinido.\n");
                exit(EXIT_FAILURE);
        }
        if (!atual->alive) {
            fimLista->prox = atual->prox;
            free(atual);
        } else {
            fimLista = atual;
        }
        atual = fimLista->prox;
    }
    objetos.fimObjs = fimLista;
}
