#include <stdio.h>
#include "keyboard.h"
#include "fisica.h"
#include "objetos.h"
#include "game.h"

int opcao = 0;

void checkForMenuActions(WINDOW *w) {
    int key;
    if(WCheckKBDPress(w)){
        key = WGetKeyPress(w);
        switch (key)
        {
        case W_KEY:
        case UP_ARROW_KEY:
            menuActions(w, 1);
            break;
        case DOWN_ARROW_KEY:
        case S_KEY:
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
        if (key == W_KEY) teclas[0][0] = 1;
        if (key == A_KEY) teclas[0][1] = 1;
        if (key == S_KEY) teclas[0][2] = 1;
        if (key == D_KEY) teclas[0][3] = 1;
        if (key == UP_ARROW_KEY) teclas[1][0] = 1;
        if (key == LEFT_ARROW_KEY) teclas[1][1] = 1;
        if (key == DOWN_ARROW_KEY) teclas[1][2] = 1;
        if (key == RIGHT_ARROW_KEY) teclas[1][3] = 1;
    }
    if (WCheckKBDRelease(w)) {
        key = WGetKeyRelease(w);
        if (key == W_KEY) teclas[0][0] = 0;
        if (key == A_KEY) teclas[0][1] = 0;
        if (key == S_KEY) teclas[0][2] = 0;
        if (key == D_KEY) teclas[0][3] = 0;
        if (key == UP_ARROW_KEY) teclas[1][0] = 0;
        if (key == LEFT_ARROW_KEY) teclas[1][1] = 0;
        if (key == DOWN_ARROW_KEY) teclas[1][2] = 0;
        if (key == RIGHT_ARROW_KEY) teclas[1][3] = 0;
    }
}
