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
    int i, j;
    int supw = FATOR*WIDTH;
    int suph = FATOR*HEIGHT;

    for (i = 0; i < nObjetos; i++) {
        objetos[i]->res[0] = objetos[i]->res[1] = 0;
    }

    for (i = 0; i < nObjetos; i++) {
        for (j = i+1; j < nObjetos; j++) {
            addForcaGrav(objetos[i], objetos[j]);
        }
    }

    for (i = 0; i < 2; i++) {
        if (nave[i].obj == NULL) continue;
        if (teclas[i][0]) accUsuario(nave[i].obj);
        if (teclas[i][1]) rotacionaNave(nave[i].obj, 1);
        if (teclas[i][2]) disparaProjetil(nave+i);
        if (teclas[i][3]) rotacionaNave(nave[i].obj, -1);
    }


    for (i = 0; i < nObjetos; i++) {
        /* aplica aceleração */
        objetos[i]->vel[0] += (objetos[i]->res[0] / objetos[i]->massa) * passoSimulacao;
        objetos[i]->vel[1] += (objetos[i]->res[1] / objetos[i]->massa) * passoSimulacao;

        /* aplica velocidade */
        objetos[i]->pos[0] += objetos[i]->vel[0] * passoSimulacao;
        objetos[i]->pos[1] += objetos[i]->vel[1] * passoSimulacao;

        /* imita um toro */
        objetos[i]->pos[0] = mod(objetos[i]->pos[0] + supw/2, supw) - supw/2;
        objetos[i]->pos[1] = mod(objetos[i]->pos[1] + suph/2, suph) - suph/2;

    }
}

int colidiu(Objeto *a, Objeto *b) {
    return calculaDistancia(a->pos, b->pos) <= a->raio*FATOR + b->raio*FATOR;
}

void detectaColisoes() {
    int i, j;
    for (i = 0; i < nObjetos; i++) {
        for (j = i+1; j < nObjetos; j++) {
            if (colidiu(objetos[i], objetos[j])) {
                if (objetos[i]->tipo != PLANETA) objetos[i]->alive = 0;
                if (objetos[j]->tipo != PLANETA) objetos[j]->alive = 0;
                db(printf("Objeto %d colidiu com objeto %d\n", i, j));
            }
        }
    }
}

void accUsuario(Objeto *a) {
    db(printf("Resultante antes: (%g, %g)\n", a->res[0], a->res[1]));
    a->res[0] += ACC_USUARIO * cos(a->ang);
    a->res[1] += ACC_USUARIO * sin(a->ang);
    db(printf("Resultante depois: (%g, %g)\n", a->res[0], a->res[1]));
}

/*
    cos x   -sin x
    sin x    cos x
 */
void rotacionaNave(Objeto *a, int sentido) {
    db(printf("Angulo antes: (%g)\n", a->ang));
    a->ang = modD(a->ang + sentido * 0.01, 2*PI);
    db(printf("Angulo depois: (%g)\n", a->ang));
}
