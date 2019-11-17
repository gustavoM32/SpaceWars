#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "objetos.h"
#include "tick.h"
#include "display.h"
#include "util.h"
#include "debug.h"

Objeto *criaObjeto() {
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
    novo->prox = NULL;
    fimListaObjetos = fimListaObjetos->prox = novo;
    return novo;
}

Objeto *criaNave() {
    Objeto *novo = criaObjeto();
    novo->oNave = (Nave *) mallocSafe(sizeof(Nave));
    novo->oNave->ultimoDisparo = 0;
    strcpy(novo->oNave->nome, "nave");
    return novo;
}

Objeto *criaProjetil() {
    Objeto *novo = criaObjeto();
    novo->oProj = (Projetil *) mallocSafe(sizeof(Projetil));
    novo->oProj->duracao = duracaoProjetil;
    novo->oProj->criado = 0;
    return novo;
}

Objeto *criaAnimacao(double pos[], int width, int height, int frames, int duracao, Sprite *s) {
    Objeto *novo = criaObjeto();
    novo->oAnim = (Animacao *) mallocSafe(sizeof(Animacao));
    novo->s = s;
    novo->categoria = ANIMACAO;
    novo->pos[0] = pos[0];
    novo->pos[1] = pos[1];
    novo->oAnim->width = width;
    novo->oAnim->height = height;
    novo->oAnim->frames = frames;
    novo->oAnim->duracao = duracao;
    novo->oAnim->inicio = getTick();
    return novo;
}

void disparaProjetil(Objeto *a) {
    Objeto *novo;
    if (getTick() - a->oNave->ultimoDisparo < TEMPO_DISP * FRAMES_PER_SECOND * TICKS_PER_FRAME) return;
    a->oNave->ultimoDisparo = getTick();
    novo = criaProjetil();
    novo->categoria = PROJETIL;
    novo->s = projetil;
    novo->alive = 1;
    novo->raio = 4;
    novo->massa = 2;
    novo->pos[0] = a->pos[0] + 40 * FATOR * cos(a->ang);
    novo->pos[1] = a->pos[1] + 40 * FATOR * sin(a->ang);
    novo->vel[0] = 400 * FATOR * cos(a->ang);
    novo->vel[1] = 400 * FATOR * sin(a->ang);
    novo->oProj->criado = getTick();
}

void mataObjetos() {
    int ticksPerSec = (FRAMES_PER_SECOND * TICKS_PER_FRAME);
    Objeto *fimLista = listaObjetos;
    Objeto *atual = listaObjetos->prox;
    while (atual != NULL) {
        switch (atual->categoria) {
            case NAVE:
                if (!atual->alive) {
                    db(printf("Nave '%s' explodiu.\n", atual->oNave->nome));
                    criaAnimacao(atual->pos, 50, 60, 15, 1, explosao);
                    nave[atual->oNave->id] = NULL;
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
        }
        // Tomar cuidado com o fato de as naves não existirem mais depois de explodidas
        if (!atual->alive) {
            fimLista->prox = atual->prox;
            free(atual);
        } else {
            fimLista = atual;
        }
        atual = fimLista->prox;
    }
    fimListaObjetos = fimLista;
}
