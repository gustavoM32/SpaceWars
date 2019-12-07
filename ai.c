#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ai.h"
#include "keyboard.h"
#include "fisica.h"
#include "objetos.h"
#include "display.h"
#include "util.h"

double distPla;
double distIni;
double colPla;
double colIni;
Objeto *ini, *ai, *pla;
double vecPla[2];
double angVel;
double epsilon = 0.1;

double randomChance() {
    return (double) rand() / RAND_MAX;
}

int randomEvent(double chance) {
    return randomChance() < chance;
}

int aimAtAngle(double ang) {
    double angDist = ang - ai->ang;
    if (angDist > epsilon) {
        if (angDist < PI) teclas[1][1] = 1;
        else teclas[1][3] = 1;
    } else if (angDist < -epsilon) {
        if (absD(angDist) < PI) teclas[1][3] = 1;
        else teclas[1][1] = 1;
    } else {
        return 1;
    }
    return 0;
}

double getVecAngle(double vec[2]) {
    int ang;
    if (vec[0] == 0) {
        ang = PI/2 + PI * (vec[1] < 0);
    } else {
        ang = modD(atan2(vec[1], vec[0]), 2*PI);
    }
    return ang;
}

double getAimPos(double pos[2]) {
    double vec[2];
    vec[0] = pos[0] - ai->pos[0];
    vec[1] = pos[1] - ai->pos[1];
    return getVecAngle(vec);
}

void escapaObjeto(double pos[2]) {
    // Gira pra direção oposta á posição do objeto
    double opAngVel = modD(getAimPos(pos) + PI, 2*PI);
    aimAtAngle(opAngVel);
    teclas[1][0] = 1;
}

void desacelera() {
    double ang = getVecAngle(ai->vel);
    double opAngVel = modD(ang + PI, 2*PI);
    //printf("velang %f\n", ang);
    //printf("tentando atingir de %f  para %f\n", ai->ang, opAngVel);
    //printf("")
    if (aimAtAngle(opAngVel)) {
        teclas[1][0] = 1;
        //printf("acc\n");
    }
}

void jogaAI() {
    ai = objetos.nave[1];
    ini = objetos.nave[0];
    pla = objetos.planeta;
    if (ai == NULL || ini == NULL) return;
    //printf(" --- Nave 2 ---\n");
    //printf("pos %f %f\n", ai->pos[0], ai->pos[1]);
    //printf("vel %f %f\n", ai->vel[0], ai->vel[1]);
    //printf("ang %f\n", ai->ang);

    if (pla != NULL) {
        distPla = calculaDistancia(ai->pos, pla->pos);
        colPla = (ai->raio + pla->raio)*FATOR;
    }
    if (objetos.nave[0] != NULL) {
        distIni = calculaDistancia(ai->pos, ini->pos);
        colIni = (ai->raio + ini->raio)*FATOR;
    }
    //printf("----\n");
    //printf("colPlaneta = %f\n", colPla);
    //printf("colInimigo = %f\n", colIni);
    //printf("distPlaneta = %f\n", distPla);
    //printf("distInimigo = %f\n", distIni);

    //***** Tenta ficar parado *****//

    int i;
    for (i = 0; i < 4; i++) {
        teclas[1][i] = 0;
    }

    //printf("angvel = %f\n", angVel);

    //printf("vel %f\n", calcNorma(ai->vel));

    if (distPla < (3.5 + randomChance()) * colPla) {
        //printf("Escapando do planeta\n");
        escapaObjeto(pla->pos);
    } else if (distIni < (4.5 + randomChance()) * colIni) {
        //printf("Escapando do inimigo\n");
        escapaObjeto(ini->pos);
    } else if (calcNorma(ai->vel) > 10000000*(1 + randomChance())) {
        //printf("Desacelerando\n");
        desacelera();
    } else {
        //printf("Mirando no inimigo\n");
            if (aimAtAngle(getAimPos(ini->pos))) {
                //printf("Atirando!\n");
                if (randomEvent(0.9)) teclas[1][2] = 1;
            } else {
                if (randomEvent(0.001)) teclas[1][2] = 1;
            }
    }

}
