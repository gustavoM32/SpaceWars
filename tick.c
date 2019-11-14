#include <stdio.h>
#include <unistd.h>
#include "tick.h"
#include "display.h"
#include "objetos.h"
#include "io.h"
#include "fisica.h"
#include "keyboard.h"
#include <X11/Xlib.h>
#include "xwc.h"

static long int tick = 0;
int loser = 0;
int endTick = -1;

WINDOW *w;
PIC rasc;
PIC fundo;

int getTick() {
    return tick;
}

void endGame() {
    endTick = tick + 5 * TICKS_PER_FRAME * FRAMES_PER_SECOND;
    if (loser == 1) {
        printf("Jogador 2 ganhou!\n");
    } else if (loser == 2) {
        printf("Jogador 1 ganhou!\n");
    } else {
        printf("Ambos perderam!\n");
    }
}

void gameLoop() {
    tick = 0;
    iniciaTeclas();
    while (endTick == -1 || tick <= endTick) {
        checkForActions(w);
        atualizaPosicoes();
        detectaColisoes();
        mataObjetos();
        if (tick % TICKS_PER_FRAME == 0) {
            PutPic(rasc, fundo, 0, 0, WIDTH, HEIGHT, 0, 0);
            imprimaObjetos(rasc);
            PutPic(w, rasc, 0, 0, WIDTH, HEIGHT, 0, 0);
        }
        if (endTick == -1) {
            loser += nave[0].obj == NULL ? 1 : 0;
            loser += nave[1].obj == NULL ? 2 : 0;
            if (loser != 0) endGame();
        }
        usleep(1000000.0 * passoSimulacao);
        tick++;
    }
}

void game() {
    int i;
    int nProjeteis = leiaArquivo();

    passoSimulacao = 1.0 / (FRAMES_PER_SECOND * TICKS_PER_FRAME);
    w = InitGraph(WIDTH, HEIGHT, "My windows xp");
    InitKBD(w);
    rasc = NewPic(w, WIDTH, HEIGHT);
    carregaObjetos(w);
    printf("Carregando assets/background.xpm...\n");
    fundo = ReadPic(w, "assets/background.xpm", NULL);
    printf("Passo simulação = %lf\n", passoSimulacao);

    gameLoop();

    XAutoRepeatOn(getDisplay());
    CloseGraph();
}
