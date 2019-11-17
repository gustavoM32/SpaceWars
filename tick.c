#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tick.h"
#include "debug.h"
#include "display.h"
#include "objetos.h"
#include "io.h"
#include "fisica.h"
#include "keyboard.h"
#include "util.h"
#include <X11/Xlib.h>
#include "xwc.h"

static int tick = 0;
int loser = 0;
int endTick;

WINDOW *w;
PIC rasc;
PIC fundo;

int getTick() {
    return tick;
}

void endGame() {
    endTick = tick + 5 * TICKS_PER_FRAME * FRAMES_PER_SECOND;
    if (loser == 1) {
        printf("Nave '%s' ganhou!\n", objetos.nave[1]->oNave->nome);
    } else if (loser == 2) {
        printf("Nave '%s' ganhou!\n", objetos.nave[0]->oNave->nome);
    } else {
        printf("Ambas perderam!\n");
    }
}

void gameLoop() {
    tick = 0;
    loser = 0;
    endTick = -1;
    criaObjetos();
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
            loser += objetos.nave[0] == NULL ? 1 : 0;
            loser += objetos.nave[1] == NULL ? 2 : 0;
            if (loser != 0) endGame();
        }
        usleep(1000000.0 * passoSimulacao);
        tick++;
    }
    freeObjetos();
}

void game() {
    int repeticoes = 3;
    passoSimulacao = 1.0 / (FRAMES_PER_SECOND * TICKS_PER_FRAME);

    w = InitGraph(WIDTH, HEIGHT, "My windows xp");
    InitKBD(w);
    rasc = NewPic(w, WIDTH, HEIGHT);
    carregaObjetos(w);

    db(printf("Carregando assets/background.xpm...\n"));
    fundo = ReadPic(w, "assets/background.xpm", NULL);
    db(printf("Passo simulação = %lf\n", passoSimulacao));

    while (repeticoes--) gameLoop();

    XAutoRepeatOn(getDisplay());
    CloseGraph();
}
