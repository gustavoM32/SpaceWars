#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "objetos.h"
#include "display.h"

/*
    leiaArquivo()

A entrada será fornecida em um arquivo com o seguinte formato:

    A primeira linha tem os parâmetros globais, separados por espaço:
        Tamanho do planeta (raio).
        Massa do planeta.
        Tempo total de simulação.
    A segunda linha contém a descrição da primeira nave, com os seguintes campos separados por espaço:
        nome — nome da nave, para referência posterior.
        massa — massa da nave.
        pos_x — coordenada x da posição da nave.
        pos_y — coordenada y da posição da nave.
        vel_x — componente x da velocidade da nave.
        vel_y — componente y da velocidade da nave.
    A terceira linha descreve a segunda nave, da mesma forma.
    A quarta linha indicará o número de projéteis e a duração (tempo de vida) deles.
    As linhas seguintes conterão a descrição de cada projétil, da mesma forma que nas naves, mas sem o campo nome.

    Os valores serão fornecidos no sistema métrico.
 */
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

    planeta.pos[0] = planeta.pos[1] = 0.0;
    fscanf(arquivo, "%lf %lf %lf", &(planeta.raio), &(planeta.massa), &tempoSimulacao);

    planeta.raio = 45;

    for (i = 0; i < 2; i++) {
        fscanf(arquivo, "%s %lf %lf %lf %lf %lf", &(nave[i].nome), &(nave[i].massa), &(nave[i].pos[0]), &(nave[i].pos[1]), &(nave[i].vel[0]), &(nave[i].vel[1]));
        nave[i].alive = 1;
        nave[i].raio = 15;
    }

    fscanf(arquivo, "%d %lf", &nProjeteis, &duracaoProjetil);

    for(i = 0; i < nProjeteis; i++){
        projeteis[i].duracao = duracaoProjetil;
        fscanf(arquivo, "%lf %lf %lf %lf %lf", &(projeteis[i].massa), &(projeteis[i].pos[0]), &(projeteis[i].pos[1]), &(projeteis[i].vel[0]), &(projeteis[i].vel[1]));
        projeteis[i].alive = 1;
        projeteis[i].raio = 4;
        projeteis[i].criado = 0;
    }

    fclose(arquivo);

    nAnimacoes = 0;

    return nProjeteis;
}
