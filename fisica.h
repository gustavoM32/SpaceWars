#ifndef FISICA_H
#define FISICA_H

#include "objetos.h"

#define PI 3.14159265
#define EPSILON 1.0e-10
#define MAX_ACC 1.0e7
#define GRAVIDADE 6.67e-11

double tempoSimulacao;
double passoSimulacao;

/*
    transforma()

    Transforma as coordenadas de coor para exibição dos
    objetos na interface gráfica.

    Parâmetros:
        coor[] - vetor original
        nova[] - vetor transformado
*/
void transforma(double coor[2], double nova[2]);

/*
    calcNorma()

    Calcula a norma do vetor.

    Parâmetros:
        vetor[] - vetor qualquer
*/
double calcNorma(double vetor[2]);

/*
    calculaDistancia()

    Calcula a distância entre dois corpos.

    Parâmetros:
        pos1[] - vetor posição do corpo 1
        pos2[] - vetor posição do corpo 2
*/
double calculaDistancia(double pos1[2], double pos2[2]);

/*
    calculaDirecao()

    Calcula o vetor unitário com a mesma direção da reta
que liga as posições 1 e 2. O sentido é de 2 para 1.

    Parâmetros:
        pos1[] - vetor posição do corpo 1
        pos2[] - vetor posição do corpo 2
        dir[] - vetor unitário resultante
        dist - distância entre as posições
*/
void calculaDirecao(double pos1[2], double pos2[2], double dir[2], double dist);

/*
    addForcaGrav()

    Adiciona a força gravitacional entre os objetos a e b em seus
    vetores resultantes.

    Parâmetros:
        a - apontador para o objeto a
        b - apontador para o objeto b
*/
void addForcaGrav(Objeto *a, Objeto *b);

/*
    atualizaPosicoes()

    Executa o passo da simulação para todos os corpos.
*/
void atualizaPosicoes();

/*
    colidiu()

    Retorna 1 se dois objetos colidiram, 0 caso contrário.

    Parâmetros:
        a - apontador para o objeto a
        b - apontador para o objeto b
*/
int colidiu(Objeto *a, Objeto *b);

/*
    detectaColisoes()

    Verifica todas as colisões e marca os objetos que colidiram como mortos.
*/
void detectaColisoes();
#endif
