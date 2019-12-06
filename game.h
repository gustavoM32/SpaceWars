#ifndef GAME_H
#define GAME_H

#include "xwc.h"

#define FRAMES_PER_SECOND 50
#define TICKS_PER_FRAME 20

typedef struct config Config;

typedef struct playerControls PlayerControls;

struct playerControls {
    int up;
    int down;
    int left;
    int right;
};

struct config {
    PlayerControls player1;
    PlayerControls player2;
    int pauseKey;
    int numberOfLives;
    int isSoundActive;
    double gameDuration;
    double duracaoProjetil;
};

Config config;
int goToMenu;

/*
    getTick()

    Retorna o tick atual.
*/
int getTick();

/*
    ticksToSegs()

    Converte o número de ticks dado para segundos de jogo.

    Parametros:
        ticks - número de ticks
*/
double ticksToSegs(int ticks);

/*
    segsToTicks()

    Converte o número de segundos para tick.

    Parametros:
        segs - número de segudos
*/
int segsToTicks(double segs);

/*
    menuActions()

    realiza a acao 'acao'

    Parametros:
        WINDOW *w - ponteiro para a janela de onde serao identificadas as teclas
        int acao - codigo da acao a ser realizada:
            0 = desce a seta
            1 = sobe a seta
            2 = confirma opcao
*/

/*
    exitGame()

    Sai do jogo de maneira graciosa.
*/
void exitGame();

void menuActions(WINDOW *w, int acao);

/*
    gameLoop()

    Executa o loop principal do jogo.
*/
void gameLoop();

/*
    game()

    Executa o jogo.
*/
void game();

#endif
