#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "objetos.h"
#include "display.h"

int leiaArquivo() {
    FILE * arquivo;
    char nomeDoArquivo[80];
    double duracaoProjetil;
    int i;

    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    arquivo = fopen(nomeDoArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        exit(EXIT_FAILURE);
    }

    planeta.obj = criaObjeto();
    planeta.obj->tipo = PLANETA;
    planeta.obj->img = &planetaS;
    fscanf(arquivo, "%lf %lf %lf", &(planeta.obj->raio), &(planeta.obj->massa), &tempoSimulacao);
    planeta.obj->raio = 45;

    for (i = 0; i < 2; i++) {
        nave[i].obj = criaObjeto();
        nave[i].obj->tipo = NAVE;
        nave[i].obj->img = naves[i];
        fscanf(arquivo, "%s %lf %lf %lf %lf %lf", &(nave[i].nome), &(nave[i].obj->massa), &(nave[i].obj->pos[0]), &(nave[i].obj->pos[1]), &(nave[i].obj->vel[0]), &(nave[i].obj->vel[1]));
        nave[i].obj->alive = 1;
        nave[i].obj->raio = 15;
    }

    fscanf(arquivo, "%d %lf", &nProjeteis, &duracaoProjetil);

    for(i = 0; i < nProjeteis; i++) {
        projeteis[i].obj = criaObjeto();
        projeteis[i].obj->tipo = PROJETIL;
        projeteis[i].obj->img = projetil;
        projeteis[i].duracao = duracaoProjetil;
        fscanf(arquivo, "%lf %lf %lf %lf %lf", &(projeteis[i].obj->massa), &(projeteis[i].obj->pos[0]), &(projeteis[i].obj->pos[1]), &(projeteis[i].obj->vel[0]), &(projeteis[i].obj->vel[1]));
        projeteis[i].obj->alive = 1;
        projeteis[i].obj->raio = 4;
        projeteis[i].criado = 0;
    }

    fclose(arquivo);

    nAnimacoes = 0;

    return nProjeteis;
}
