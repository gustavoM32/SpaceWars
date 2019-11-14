#include "keyboard.h"
#include "fisica.h"
#include "objetos.h"

void checkForActions(WINDOW *w){
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

void nave1Ac(int key){
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

void nave2Ac(int key){
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