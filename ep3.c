/*
    Fase 1 - MAC0216
    Equipe:
        Gustavo de Medeiros Carlos, 11276298
        Luiza Barros Reis Soezima, 11221842
        Marcos Siolin Martins, 11221709
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "objetos.h"
#include "fisica.h"
#include "display.h"

/*
    DOC

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
int leiaArquivo(){
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
    printf("%lf %lf %lf\n", planeta.raio, planeta.massa, tempoSimulacao);
    // Raio do planeta será fixado em 100
    planeta.raio = 100;

    fscanf(arquivo, "%s %lf %lf %lf %lf %lf", &(nave1.nome), &(nave1.massa), &(nave1.pos[0]), &(nave1.pos[1]), &(nave1.vel[0]), &(nave1.vel[1]));
    printf("%s %lf %lf %lf %lf %lf\n", nave1.nome, nave1.massa, nave1.pos[0], nave1.pos[1], nave1.vel[0], nave1.vel[1]);

    fscanf(arquivo, "%s %lf %lf %lf %lf %lf", &(nave2.nome), &(nave2.massa), &(nave2.pos[0]), &(nave2.pos[1]), &(nave2.vel[0]), &(nave2.vel[1]));
    printf("%s %lf %lf %lf %lf %lf\n", nave2.nome, nave2.massa, nave2.pos[0], nave2.pos[1], nave2.vel[0], nave2.vel[1]);

    fscanf(arquivo, "%d %lf", &nProjeteis, &duracaoProjetil);
    printf("%d %lf\n", nProjeteis, duracaoProjetil);

    for(i = 0; i < nProjeteis; i++){
        projeteis[i].duracaoProjetil = duracaoProjetil;
        fscanf(arquivo, "%lf %lf %lf %lf %lf", &(projeteis[i].massa), &(projeteis[i].pos[0]), &(projeteis[i].pos[1]), &(projeteis[i].vel[0]), &(projeteis[i].vel[1]));
        printf("%lf %lf %lf %lf %lf\n", projeteis[i].massa, projeteis[i].pos[0], projeteis[i].pos[1], projeteis[i].vel[0], projeteis[i].vel[1]);
    }

    fclose(arquivo);

    return nProjeteis;
}

int main(){
    int i;
    WINDOW *w;
    PIC rasc;
    PIC fundo;
    passoSimulacao = 0.01;
    /*printf("Digite o passo da simulação em segundos: ");
    scanf("%lf", &passoSimulacao);
    TIRAR DEPOIS*/
    int nProjeteis = leiaArquivo();

    w = InitGraph(WIDTH, HEIGHT, "My windows xp");

    carregaObjetos(w);

    rasc = NewPic(w, WIDTH, HEIGHT);

    printf("Carregando assets/background.xpm...\n");
    fundo = ReadPic(w, "assets/background.xpm", NULL);

    printf("      Nave 1       |      Nave 2       |    Projéteis...   \n");
    while (1) {
        atualizaPosicoes();
        //mostraPosicoes();
        PutPic(rasc, fundo, 0, 0, WIDTH, HEIGHT, 0, 0);
        imprimaObjetos(rasc);
        PutPic(w, rasc, 0, 0, WIDTH, HEIGHT, 0, 0);
        usleep(2500);
    }
    CloseGraph();
    return EXIT_SUCCESS;
}
