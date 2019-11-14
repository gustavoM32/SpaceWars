#include "keyboard.h"
#include "fisica.h"
#include "objetos.h"

#define OPTIONS_LIMIT 2

int opcao = 0;

void menuActions(WINDOW *w, int acao) {
    switch (acao)
    {
    case 0:
        if(opcao < OPTIONS_LIMIT) {
            opcao++;
            /* desce seta */
        }
        break;
    case 1:
        if(opcao) {
            opcao--;
            /* sobe seta */
        }
        break;
    case 2:
        /* pressiona enter */
    default:
        break;
    }
}

void checkForMenuActions(WINDOW *w) {
    int key;
    if(WCheckKBD(w)){
        key = WGetKey(w);
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

void checkForActions(WINDOW *w) {
    int key;
    if(WCheckKBD(w)){
        key = WGetKey(w);
        switch (key)
        {
        case W_KEY:
        case A_KEY:
        case S_KEY:
        case D_KEY:        
            nave1Ac(key);
            break;
        case UP_ARROW_KEY:
        case LEFT_ARROW_KEY:
        case DOWN_ARROW_KEY:
        case RIGHT_ARROW_KEY:        
            nave2Ac(key);
            break;
        default:
            break;
        }
    }
}

void nave1Ac(int key) {
    switch (key)
    {
    case W_KEY:
        aumentaVelocidade(nave->obj);
        break;
    case A_KEY:
        rotacionaNaveH(nave);
        break;
    case S_KEY:
        /*dispara projetil */
        break;
    case D_KEY:
        rotacionaNaveA(nave);        
        break;
    default:
        break;
    }
}

void nave2Ac(int key) {
    switch (key)
    {
    case UP_ARROW_KEY:
        aumentaVelocidade((nave + sizeof(Nave))->obj);
        break;
    case LEFT_ARROW_KEY:
        rotacionaNaveH(nave + sizeof(Nave));
        break;
    case DOWN_ARROW_KEY:
        /*dispara projetil */
        break;
    case RIGHT_ARROW_KEY:
        rotacionaNaveA(nave + sizeof(Nave));        
        break;
    default:
        break;
    }
}