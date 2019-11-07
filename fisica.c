#include <math.h>
#include <stdio.h>
#include "fisica.h"
#include "display.h"
#include "objetos.h"

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

void somaVetores(double f1[2], double f2[2], double soma[2]) {
    soma[0] = f1[0] + f2[0];
    soma[1] = f1[1] + f2[1];
}

void calculaDirecao(double pos1[2], double pos2[2], double dir[2], double dist) {
    double dx, dy;
    dx = pos1[0] - pos2[0];
    dy = pos1[1] - pos2[1];
    dir[0] = dx / dist;
    dir[1] = dy / dist;
}


void addForcaGrav(double massa1, double pos1[2], double massa2, double pos2[2], double res[2]) {
    double dist = calculaDistancia(pos1, pos2);
    double fg;
    double dir[2] = {0, 0};
    if (dist > EPSILON) {
        calculaDirecao(pos2, pos1, dir, dist);
        fg = GRAVIDADE * massa1 * massa2 / (dist * dist);
        /*
            Limita a força caso ela seja grande demais.
            Não será necessário quando as colisões forem
            detectadas.
        */
        if (fg / massa1 > MAX_ACC) fg = massa1 * MAX_ACC;
        res[0] += fg * dir[0];
        res[1] += fg * dir[1];
    }
}

void calculaResultante(double massa, double pos[2], double resultante[2]) {
    double forcaCorpo[2];
    int i;
    resultante[0] = resultante[1] = 0;
    /* adiciona forças gravitacionais à resultante do corpo */
    addForcaGrav(massa, pos, nave1.massa, nave1.pos, resultante);
    addForcaGrav(massa, pos, nave2.massa, nave2.pos, resultante);
    addForcaGrav(massa, pos, planeta.massa, planeta.pos, resultante);

    for (i = 0; i < nProjeteis; i++)
        addForcaGrav(massa, pos, projeteis[i].massa, projeteis[i].pos, resultante);
}

/*
    mod(int a, int b)

    Recebe um inteiro 'a' e um inteiro 'b' retorna o valor
    de a % b.

*/
int mod(int a, int b) {
    return a > 0 ? a % b : (a % b + b) % b;
}

void calculoDosMovimentos(double massa, double pos[2], double vel[2], double resultante[2]) {
    /* aplica aceleração */
    vel[0] += (resultante[0] / massa) * passoSimulacao;
    vel[1] += (resultante[1] / massa) * passoSimulacao;

    /* aplica velocidade */
    pos[0] += (vel[0]) * passoSimulacao;
    pos[1] += (vel[1]) * passoSimulacao;

    /*
        altera a posição do corpo se ele sair da tela a fim
        de imitar um toro, será implementado em uma fase posterior
        do projeto visto que ainda não estamos projetando os
        objetos em uma interface gráfica
    */
    int supw = FATOR*WIDTH;
    int suph = FATOR*HEIGHT;
    pos[0] = mod(pos[0] + supw/2, supw) - supw/2;
    pos[1] = mod(pos[1] + suph/2, suph) - suph/2;
}

void atualizaPosicoes() {
    int i;
    calculaResultante(nave1.massa, nave1.pos, nave1.res);
    calculaResultante(nave2.massa, nave2.pos, nave2.res);

    for (i = 0; i < nProjeteis; i++)
        calculaResultante(projeteis[i].massa, projeteis[i].pos, projeteis[i].res);

    calculoDosMovimentos(nave1.massa, nave1.pos, nave1.vel, nave1.res);
    calculoDosMovimentos(nave2.massa, nave2.pos, nave2.vel, nave2.res);

    for (i = 0; i < nProjeteis; i++)
        calculoDosMovimentos(projeteis[i].massa, projeteis[i].pos, projeteis[i].vel, projeteis[i].res);
}

int colidiu(double pos1[2], double r1, double pos2[2], double r2) {
    return calculaDistancia(pos1, pos2) <= r1*FATOR + r2*FATOR;
}

void detectaColisoes() {
    int i, j;
    if (colidiu(planeta.pos, planeta.raio, nave1.pos, nave1.raio)) nave1.alive = 0;
    if (colidiu(planeta.pos, planeta.raio, nave2.pos, nave2.raio)) nave2.alive = 0;

    for (i = 0; i < nProjeteis; i++) {
        if (colidiu(planeta.pos, planeta.raio, projeteis[i].pos, projeteis[i].raio)) projeteis[i].alive = 0;
    }

    if (colidiu(nave1.pos, nave1.raio, nave2.pos, nave2.raio)) {
        nave1.alive = 0;
        nave2.alive = 0;
    }

    for (i = 0; i < nProjeteis; i++) {
        //printf("Testando colesão\n");
        //printf("%lf %lf %lf %lf %lf %lf\n", nave1.pos[0], nave1.pos[1], nave1.raio, projeteis[i].pos[0], projeteis[i].pos[1], projeteis[i].raio);
        if (colidiu(nave1.pos, nave1.raio, projeteis[i].pos, projeteis[i].raio)) {
            nave1.alive = 0;
            projeteis[i].alive = 0;
        }
    }

    for (i = 0; i < nProjeteis; i++) {
        if (colidiu(nave2.pos, nave2.raio, projeteis[i].pos, projeteis[i].raio)) {
            nave2.alive = 0;
            projeteis[i].alive = 0;
        }
    }

    for (i = 0; i < nProjeteis; i++) {
        for (j = i+1; j < nProjeteis; j++) {
            if (colidiu(projeteis[i].pos, projeteis[i].raio, projeteis[j].pos, projeteis[j].raio)) {
                projeteis[i].alive = 0;
                projeteis[j].alive = 0;
            }
        }
    }

}
