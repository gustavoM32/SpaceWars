#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
#include "ai.h"

typedef enum {
    JOGAR,
    AJUDA,
    SAIR
} SELECAO;

int selecionado = JOGAR;

static int tick = 0;
int loser = 0;
int endTick;
int vidasP1 = 3;
int vidasP2 = 3;

WINDOW *w;
PIC rasc;
PIC fundo;
PIC ajudaFundo;
PIC intro;
PIC telaGanhador[3];

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
    int i;
    tick = 0;
    while (1) {
        checkForMenuActions(w);
        if (tick % TICKS_PER_FRAME == 0) {
            PutPic(rasc, fundo, 0, 0, WIDTH, HEIGHT, 0, 0);
            for (i = 0; i < 3; i++) {
                imprimeFixed(rasc, &(sprites.botao[i][i == selecionado]), 0);
            }
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
            case AJUDA:
            PutPic(w, ajudaFundo, 0, 0, WIDTH, HEIGHT, 0, 0);
            while (1) {
                if (WCheckKBDPress(w) && WGetKeyPress(w) == config.pauseKey) break;
            }
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
        vidasP1--;
        printf("Nave 1 perdeu uma vida!\n");
    } else if (loser == 2) {
        vidasP2--;
        printf("Nave 2 perdeu uma vida!\n");
    } else {
        vidasP1--;
        vidasP2--;
        printf("As duas naves perderam uma vida!\n");
    }
}

void gameLoop() {
    int i;
    int roundStart, countdown = 0, victory = 0;
    tick = 0;
    vidasP1 = vidasP2 = 3;
    XAutoRepeatOff(getDisplay());
    // Tela de história do jogo
    PutPic(w, intro, 0, 0, WIDTH, HEIGHT, 0, 0);
    while (tick++ < segsToTicks(20.0) && !checkForActions(w)) {
        usleep(1000000.0 * passoSimulacao);
    }
    tick = 0;
    // Loop do jogo
    while (vidasP1 > 0 && vidasP2 > 0) {
        criaObjetos();
        iniciaTeclas();
        db(printf("Vidas P1 = %d   Vidas P2 = %d\n", vidasP1, vidasP2));
        loser = 0;
        endTick = -1;
        roundStart = tick;
        playMusic(1);
        // Loop da rodada
        while (endTick == -1 || tick <= endTick) {
            playMusic(1);
            // Se for pressionada a tecla para voltar ao menu
            jogaAI();
            if (checkForActions(w)) {
                freeObjetos();
                playMusic(0);
                XAutoRepeatOn(getDisplay());
                return;
            }
            if (tick - roundStart >= segsToTicks(4.0)) {
                atualizaPosicoes();
                countdown = 0;
            }
            detectaColisoes();
            mataObjetos();
            if (tick % TICKS_PER_FRAME == 0) {
                if(tick % TICKS_PER_FRAME*FRAMES_PER_SECOND == 0);
                PutPic(rasc, fundo, 0, 0, WIDTH, HEIGHT, 0, 0);
                imprimaObjetos(rasc);
                for (i = 0; i < vidasP1; i++)
                    imprimeFixed(rasc, &(sprites.coracao), i);
                for (i = 0; i < vidasP2; i++)
                    imprimeFixed(rasc, &(sprites.coracao), 3+i);
                // Se está no começo da rodada, mostra a contagem
                if (tick - roundStart < segsToTicks(4.0)) {
                    if(!countdown) {
                        playSound(COUNTDOWN_SOUND);
                        countdown = 1;
                    }
                    switch ((tick - roundStart)/ segsToTicks(1.0)) {
                        case 0:
                        imprimeFixed(rasc, sprites.contagem+2, 0);
                        break;
                        case 1:
                        imprimeFixed(rasc, sprites.contagem+1, 0);
                        break;
                        case 2:
                        imprimeFixed(rasc, sprites.contagem+0, 0);
                        break;
                        case 3:
                        imprimeFixed(rasc, &(sprites.go), 0);
                        break;
                        default:
                        break;
                    }
                }
                PutPic(w, rasc, 0, 0, WIDTH, HEIGHT, 0, 0);
            }
            // Verifica se alguém perdeu
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
    tick = 0;
    // Mostra tela final
    while (tick++ < segsToTicks(5.0)) {
        if (vidasP1 == 0 && vidasP2 == 0) {
            if(!victory) { victory = 1; playMusic(0); playSound(VICTORY_SOUND);}
            PutPic(rasc, telaGanhador[0], 0, 0, WIDTH, HEIGHT, 0, 0);
        } else if (vidasP1 == 0) {
            if(!victory) { victory = 1; playMusic(0); playSound(VICTORY_SOUND);}
            PutPic(rasc, telaGanhador[2], 0, 0, WIDTH, HEIGHT, 0, 0);
        } else if (vidasP2 == 0) {
            if(!victory) { victory = 1; playMusic(0); playSound(VICTORY_SOUND);}
            PutPic(rasc, telaGanhador[1], 0, 0, WIDTH, HEIGHT, 0, 0);
        }
        if (vidasP1 != 0 || vidasP2 != 0) imprimeFixed(rasc, &(sprites.trophy[tick / segsToTicks(0.02) % 60]), 0);
        PutPic(w, rasc, 0, 0, WIDTH, HEIGHT, 0, 0);
        usleep(1000000.0 * passoSimulacao);
    }
    victory = 0;
    playMusic(0);
    XAutoRepeatOn(getDisplay());
}

void game() {
    srand(time(0));
    passoSimulacao = ticksToSegs(1);
    musicDuration = segsToTicks(34.0);
    singleplayer = 1;

    w = InitGraph(WIDTH, HEIGHT, "Space Wars");
    InitKBD(w);
    rasc = NewPic(w, WIDTH, HEIGHT);
    carregaObjetos(w);

    // Carrega fundos das telas
    db(printf("Carregando assets/background.xpm...\n"));
    fundo = ReadPic(w, "assets/background.xpm", NULL);
    db(printf("Carregando assets/ajuda.xpm...\n"));
    ajudaFundo = ReadPic(w, "assets/ajuda.xpm", NULL);
    db(printf("Carregando assets/intro.xpm...\n"));
    intro = ReadPic(w, "assets/intro.xpm", NULL);
    db(printf("Carregando telas finais...\n"));
    telaGanhador[0] = ReadPic(w, "assets/empate.xpm", NULL);
    telaGanhador[1] = ReadPic(w, "assets/nave1ganhou.xpm", NULL);
    telaGanhador[2] = ReadPic(w, "assets/nave2ganhou.xpm", NULL);
    db(printf("Passo simulação = %lf\n", passoSimulacao));

    menuLoop(w);

    exitGame();
}
