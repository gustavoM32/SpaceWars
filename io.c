#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "objetos.h"
#include "display.h"
#include "util.h"

void leiaArquivo() {
    FILE *arquivo;
    char nomeDoArquivo[80];
    int i;
    Objeto *novo;
    int nProjeteis;

    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    arquivo = fopen(nomeDoArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        exit(EXIT_FAILURE);
    }

    fimListaObjetos = listaObjetos = (Objeto *) mallocSafe(sizeof(Objeto));
    listaObjetos->prox = NULL;

    planeta = criaObjeto();
    planeta->categoria = PLANETA;
    planeta->s = &(sprites.planetaS);
    fscanf(arquivo, "%lf %lf %lf", &(planeta->raio), &(planeta->massa), &tempoSimulacao);
    planeta->raio = 45;

    for (i = 0; i < 2; i++) {
        nave[i] = criaNave();
        nave[i]->oNave->id = i;
        nave[i]->categoria = NAVE;
        nave[i]->s = sprites.naves[i];
        fscanf(arquivo, "%s %lf %lf %lf %lf %lf", &(nave[i]->oNave->nome), &(nave[i]->massa), &(nave[i]->pos[0]), &(nave[i]->pos[1]), &(nave[i]->vel[0]), &(nave[i]->vel[1]));
        nave[i]->alive = 1;
        nave[i]->raio = 15;
        nave[i]->ang = i*PI;
    }

    fscanf(arquivo, "%d %lf", &nProjeteis, &duracaoProjetil);

    for(i = 0; i < nProjeteis; i++) {
        novo = criaProjetil();
        novo->categoria = PROJETIL;
        novo->s = sprites.projetil;
        fscanf(arquivo, "%lf %lf %lf %lf %lf", &(novo->massa), &(novo->pos[0]), &(novo->pos[1]), &(novo->vel[0]), &(novo->vel[1]));
        novo->alive = 1;
        novo->raio = 4;
    }

    fclose(arquivo);

}
