#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>

#define oNave subObj.nave
#define oProj subObj.projetil
#define oAnim subObj.animacao

/*
    mallocSafe()

    Aloca espaço na memória, saindo do programa se ocorrer um erro.

    Fonte:  http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html
*/
void *mallocSafe(size_t tam);

/*
    mod()

    Calcula a módulo b, podendo a ser negativo, de maneira
    que 0 <= a mod b < b.

    Parâmetros:
        a - inteiro qualquer
        b - inteiro positivo
*/
int mod(int a, int b);

/*
    modD()

    Calcula a módulo b, podendo a ser negativo, de maneira
    que 0 <= a mod b < b.

    Parâmetros:
        a - real qualquer
        b - real positivo
*/
double modD(double a, double b);

/*
    absD()

    Retorna o módulo do número n.

    Parâmetros:
        n - real qualquer
*/
double absD(double n);

#endif
