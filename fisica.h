#ifndef FISICA_H
#define FISICA_H

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
    somaVetores()

    Soma dois vetores.

    Parâmetros:
        f1[] - vetor 1
        f2[] - vetor 2
        soma[] - vetor resultado
*/
void somaVetores(double f1[2], double f2[2], double soma[2]);

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

    Adiciona a força gravitacional entre os corpos 1 e 2 no
vetor res.

    Parâmetros:
        massa1 - massa do corpo 1
        pos1[] - vetor posição do corpo 1
        massa2 - massa do corpo 2
        pos2[] - vetor posição do corpo 2
        res[] - vetor onde é adicionado a força calculada
*/
void addForcaGrav(double massa1, double pos1[2], double massa2, double pos2[2], double res[2]);

/*
    calculaResultante()

    Calcula a força resultante em um corpo.

    Parâmetros:
        massa - massa do corpo
        pos[] - vetor posição do corpo
        resultante[] - vetor força resultante sobre o corpo;
*/
void calculaResultante(double massa, double pos[2], double resultante[2]);

/*
    calculoDosMovimentos()

    Atualiza a velocidade e a posição de um corpo.

    Parâmetros:
        massa - massa do corpo
        pos[] - vetor posição do corpo
        vel[] - vetor velocidade do corpo
        resultante[] - vetor força resultante sobre o corpo;
*/
void calculoDosMovimentos(double massa, double pos[2], double vel[2], double resultante[2]);

/*
    atualizaPosicoes()

    Executa o passo da simulação para todos os corpos.
*/
void atualizaPosicoes();

int colidiu(double pos1[2], double r1, double pos2[2], double r2);

void detectaColisoes();
#endif
