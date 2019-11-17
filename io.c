#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "objetos.h"
#include "display.h"
#include "util.h"
#include "game.h"

void leiaArquivo() {
    FILE *arquivo;
    int i;
    Objeto *novo;
    int nProjeteis;

    arquivo = fopen("config.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(arquivo, "%lf %lf", &(objetos.planeta->massa), &tempoSimulacao);
    for (i = 0; i < 2; i++) {
        fscanf(arquivo, "%s %lf %lf %lf %lf %lf", &(objetos.nave[i]->oNave->nome), &(objetos.nave[i]->massa), &(objetos.nave[i]->pos[0]), &(objetos.nave[i]->pos[1]), &(objetos.nave[i]->vel[0]), &(objetos.nave[i]->vel[1]));
    }
    fscanf(arquivo, "%d %lf", &nProjeteis, &(config.duracaoProjetil));

    for (i = 0; i < nProjeteis; i++) {
        novo = criaProjetil();
        fscanf(arquivo, "%lf %lf %lf %lf %lf", &(novo->massa), &(novo->pos[0]), &(novo->pos[1]), &(novo->vel[0]), &(novo->vel[1]));
    }

    fclose(arquivo);

}
