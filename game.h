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
    double gameDuration;
    double duracaoProjetil;
};

Config config;

/*
    getTick()

    Retorna o tick atual.
*/
int getTick();

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
