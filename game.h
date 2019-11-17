#ifndef GAME_H
#define GAME_H

#define FRAMES_PER_SECOND 50
#define TICKS_PER_FRAME 20

typedef struct config Config;

struct config {
    double duracaoProjetil;
};

Config config;

/*
    getTick()

    Retorna o tick atual.
*/
int getTick();

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
