#include <math.h>
#include <stdio.h>
#include "fisica.h"
#include "display.h"
#include "objetos.h"
#include "util.h"
#include "debug.h"
#include "keyboard.h"

void transforma(double coor[2], double nova[2]) {
    double fator = FATOR;
    nova[0] = coor[0];
    nova[1] = -coor[1];
    nova[0] /= fator;
    nova[1] /= fator;
    nova[0] += WIDTH/2;
    nova[1] += HEIGHT/2;
}

double calcNorma(double vetor[2]) {
    return sqrt(vetor[0] * vetor[0] + vetor[1] * vetor[1]);
}

double calculaDistancia(double pos1[2], double pos2[2]) {
    double dx, dy;
    dx = pos1[0] - pos2[0];
    dy = pos1[1] - pos2[1];
    return sqrt(dx * dx + dy * dy);
}

void calculaDirecao(double pos1[2], double pos2[2], double dir[2], double dist) {
    double dx, dy;
    dx = pos2[0] - pos1[0];
    dy = pos2[1] - pos1[1];
    dir[0] = dx / dist;
    dir[1] = dy / dist;
}

void addForcaGrav(Objeto *a, Objeto *b) {
    double dist = calculaDistancia(a->pos, b->pos);
    double fg, cfg;
    double dir[2] = {0, 0};
    if (dist > EPSILON) {
        calculaDirecao(a->pos, b->pos, dir, dist);
        fg = GRAVIDADE * a->massa * b->massa / (dist * dist);
        /*
            Limita a força caso ela seja grande demais.
            Não será necessário quando as colisões forem
            detectadas.
        */
        cfg = fg;
        if (cfg / a->massa > MAX_ACC) cfg = a->massa * MAX_ACC;
        a->res[0] += cfg * dir[0];
        a->res[1] += cfg * dir[1];
        cfg = fg;
        if (cfg / b->massa > MAX_ACC) cfg = b->massa * MAX_ACC;
        b->res[0] += -(cfg * dir[0]);
        b->res[1] += -(cfg * dir[1]);
    }
}

void atualizaPosicoes(WINDOW *w) {
    Objeto *obj1, *obj2;
    int i;
    int supw = FATOR*WIDTH;
    int suph = FATOR*HEIGHT;

    for (obj1 = objetos.iniObjs->prox; obj1 != NULL; obj1 = obj1->prox) {
        obj1->res[0] = obj1->res[1] = 0;
    }

    for (obj1 = objetos.iniObjs->prox; obj1 != NULL; obj1 = obj1->prox) {
        for (obj2 = obj1->prox; obj2 != NULL; obj2 = obj2->prox) {
            addForcaGrav(obj1, obj2);
        }
    }

    for (i = 0; i < 2; i++) {
        if (objetos.nave[i] == NULL) continue;
        if (teclas[i][0]) accUsuario(objetos.nave[i]);
        if (teclas[i][1]) rotacionaNave(objetos.nave[i], 1);
        if (teclas[i][2]) disparaProjetil(objetos.nave[i]);
        if (teclas[i][3]) rotacionaNave(objetos.nave[i], -1);
    }

    for (obj1 = objetos.iniObjs->prox; obj1 != NULL; obj1 = obj1->prox) {
        if (obj1->categoria == ANIMACAO) continue;
        /* aplica aceleração */
        obj1->vel[0] += (obj1->res[0] / obj1->massa) * passoSimulacao;
        obj1->vel[1] += (obj1->res[1] / obj1->massa) * passoSimulacao;

        /* aplica velocidade */
        obj1->pos[0] += obj1->vel[0] * passoSimulacao;
        obj1->pos[1] += obj1->vel[1] * passoSimulacao;

        /* imita um toro */
        obj1->pos[0] = modD(obj1->pos[0] + supw/2, supw) - supw/2;
        obj1->pos[1] = modD(obj1->pos[1] + suph/2, suph) - suph/2;
    }
}

int colidiu(Objeto *a, Objeto *b) {
    return calculaDistancia(a->pos, b->pos) <= a->raio*FATOR + b->raio*FATOR;
}

void detectaColisoes() {
    Objeto *obj1, *obj2;
    for (obj1 = objetos.iniObjs->prox; obj1 != NULL; obj1 = obj1->prox) {
        for (obj2 = obj1->prox; obj2 != NULL; obj2 = obj2->prox) {
            if (obj1->categoria == ANIMACAO || obj2->categoria == ANIMACAO) continue;
            if (colidiu(obj1, obj2)) {
                if (obj1->categoria != PLANETA) obj1->alive = 0;
                if (obj2->categoria != PLANETA) obj2->alive = 0;
                db(printf("Objeto de tipo %d colidiu com objeto de tipo %d\n", obj1->categoria, obj2->categoria));
            }
        }
    }
}

void accUsuario(Objeto *a) {
    a->res[0] += ACC_USUARIO * cos(a->ang);
    a->res[1] += ACC_USUARIO * sin(a->ang);
}

void rotacionaNave(Objeto *a, int sentido) {
    a->ang = modD(a->ang + sentido * 0.01, 2*PI);
}
