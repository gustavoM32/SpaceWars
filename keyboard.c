#include <stdio.h>
#include <stdlib.h>
#include "keyboard.h"
#include "fisica.h"
#include "objetos.h"
#include "game.h"
#include "sounds.h"

int opcao = 0;

void checkForMenuActions(WINDOW *w) {
    int key;
    if(WCheckKBDPress(w)){
        key = WGetKeyPress(w);
        switch (key)
        {
        case W_KEY:
        case UP_ARROW_KEY:
            playSound(MENUCHANGE_SOUND);
            menuActions(w, 1);
            break;
        case DOWN_ARROW_KEY:
        case S_KEY:
            playSound(MENUCHANGE_SOUND);
            menuActions(w, 0);
            break;
        case ENTER_KEY:
            menuActions(w, 2);
            break;
        default:
            break;
        }
    }
}

void iniciaTeclas() {
    int i, j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            teclas[i][j] = 0;
        }
    }
}

void checkForActions(WINDOW *w) {
    int key;
    if (WCheckKBDPress(w)) {
        key = WGetKeyPress(w);
        if (key == config.player1.up) teclas[0][0] = 1;
        if (key == config.player1.left) teclas[0][1] = 1;
        if (key == config.player1.down) teclas[0][2] = 1;
        if (key == config.player1.right) teclas[0][3] = 1;
        if (key == config.player2.up) teclas[1][0] = 1;
        if (key == config.player2.left) teclas[1][1] = 1;
        if (key == config.player2.down) teclas[1][2] = 1;
        if (key == config.player2.right) teclas[1][3] = 1;
    }
    if (WCheckKBDRelease(w)) {
        key = WGetKeyRelease(w);        
        if (key == config.player1.up) teclas[0][0] = 0;
        if (key == config.player1.left) teclas[0][1] = 0;
        if (key == config.player1.down) teclas[0][2] = 0;
        if (key == config.player1.right) teclas[0][3] = 0;
        if (key == config.player2.up) teclas[1][0] = 0;
        if (key == config.player2.left) teclas[1][1] = 0;
        if (key == config.player2.down) teclas[1][2] = 0;
        if (key == config.player2.right) teclas[1][3] = 0;
    }
}
