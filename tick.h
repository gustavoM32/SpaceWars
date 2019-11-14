#ifndef TICK_H
#define TICK_H

#define FRAMES_PER_SECOND 50
#define TICKS_PER_FRAME 20

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
