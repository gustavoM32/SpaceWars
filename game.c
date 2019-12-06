#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "game.h"
#include "debug.h"
#include "display.h"
#include "objetos.h"
#include "io.h"
#include "fisica.h"
#include "keyboard.h"
#include "util.h"
#include <X11/Xlib.h>
#include "xwc.h"
#include "sounds.h"

typedef enum {
    JOGAR,
    OPCOES,
    SAIR
} SELECAO;

int selecionado = JOGAR;

static int tick = 0;
int loser = 0;
int endTick;

WINDOW *w;
PIC rasc;
PIC fundo;

int getTick() {
    return tick;
}

double ticksToSegs(int ticks) {
    return (double) ticks / (TICKS_PER_FRAME * FRAMES_PER_SECOND);
}

int segsToTicks(double segs) {
    return segs * (TICKS_PER_FRAME * FRAMES_PER_SECOND);
}

void exitGame() {
    XAutoRepeatOn(getDisplay());
    playMusic(0);
    CloseGraph();
    exit(EXIT_SUCCESS);
}

void menuLoop(WINDOW *w) {
    tick = 0;
    while (1) {
        checkForMenuActions(w);
        if (tick % TICKS_PER_FRAME == 0) {
            PutPic(rasc, fundo, 0, 0, WIDTH, HEIGHT, 0, 0);
            PutPic(rasc, botao[0][selecionado == JOGAR], 0, 0, 190, 90, WIDTH/2 - 95, HEIGHT/2 - 100 - 45);
            PutPic(rasc, botao[1][selecionado == OPCOES], 0, 0, 190, 90, WIDTH/2 - 95, HEIGHT/2 - 45);
            PutPic(rasc, botao[2][selecionado == SAIR], 0, 0, 190, 90, WIDTH/2 - 95, HEIGHT/2 + 100 - 45);
            //imprimaObjetos(rasc);
            PutPic(w, rasc, 0, 0, WIDTH, HEIGHT, 0, 0);
        }
        usleep(1000000.0 * passoSimulacao);
        tick++;
    }
    freeObjetos();
}

void menuActions(WINDOW *w, int acao) {
    if (acao == 0) selecionado = (selecionado + 1) % OPTIONS_LIMIT;
    else if (acao == 1) selecionado = (selecionado + OPTIONS_LIMIT - 1) % OPTIONS_LIMIT;
    else {
        playSound(MENUSELECT_SOUND);
        switch (selecionado) {
            case JOGAR:
            gameLoop();
            break;
            case OPCOES:
            break;
            case SAIR:
            exitGame();
            break;
        }
    }
}


void endGame() {
    endTick = tick + segsToTicks(3.0);
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
    XAutoRepeatOff(getDisplay());
    iniciaTeclas();
    while (endTick == -1 || tick <= endTick) {
        playMusic(1);
        checkForActions(w);
        if (goToMenu) {
            goToMenu = 0;
            break;
        }
        atualizaPosicoes();
        detectaColisoes();
        mataObjetos();
        if (tick % TICKS_PER_FRAME == 0) {
            if(tick % TICKS_PER_FRAME*FRAMES_PER_SECOND == 0);
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
    playMusic(0);
    XAutoRepeatOn(getDisplay());
}

void game() {
    passoSimulacao = ticksToSegs(1);
    musicDuration = segsToTicks(34.0);
    goToMenu = 0;

    w = InitGraph(WIDTH, HEIGHT, "My windows xp");
    InitKBD(w);
    rasc = NewPic(w, WIDTH, HEIGHT);
    carregaObjetos(w);

    db(printf("Carregando assets/background.xpm...\n"));
    fundo = ReadPic(w, "assets/background.xpm", NULL);
    db(printf("Passo simulação = %lf\n", passoSimulacao));

    menuLoop(w);

    exitGame();
}
