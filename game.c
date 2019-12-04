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

#define OPTIONS_LIMIT 3

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
PIC botao[OPTIONS_LIMIT][2];

int getTick() {
    return tick;
}

void exitGame() {
    XAutoRepeatOn(getDisplay());
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
    XAutoRepeatOff(getDisplay());
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
    passoSimulacao = 1.0 / (FRAMES_PER_SECOND * TICKS_PER_FRAME);

    w = InitGraph(WIDTH, HEIGHT, "My windows xp");
    InitKBD(w);
    rasc = NewPic(w, WIDTH, HEIGHT);
    carregaObjetos(w);

    botao[0][0] = ReadPic(w, "assets/botoes/Jogar-off.xpm", NULL);
    botao[0][1] = ReadPic(w, "assets/botoes/Jogar-on.xpm", NULL);
    botao[1][0] = ReadPic(w, "assets/botoes/Opcoes-off.xpm", NULL);
    botao[1][1] = ReadPic(w, "assets/botoes/Opcoes-on.xpm", NULL);
    botao[2][0] = ReadPic(w, "assets/botoes/Sair-off.xpm", NULL);
    botao[2][1] = ReadPic(w, "assets/botoes/Sair-on.xpm", NULL);

    db(printf("Carregando assets/background.xpm...\n"));
    fundo = ReadPic(w, "assets/background.xpm", NULL);
    db(printf("Passo simulação = %lf\n", passoSimulacao));

    menuLoop(w);

    exitGame();
}
