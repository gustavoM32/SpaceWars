#include "xwc.h"
#define W_KEY 25
#define A_KEY 38
#define S_KEY 39
#define D_KEY 40

#define UP_ARROW_KEY 111
#define LEFT_ARROW_KEY 113
#define DOWN_ARROW_KEY 116
#define RIGHT_ARROW_KEY 114

#define ENTER_KEY 36

/*
    checkForActions()

    Checa se a ultima tecla pressionada e' uma acao valida das naves
    (movimentacao ou atirar), se for realiza a acao da respectiva nave.
    Assume que InitKDB() ja foi dado

    Parametros:
        WINDOW *w - ponteiro para a janela de onde serao identificadas as teclas
*/
void checkForActions(WINDOW *w);

/*
    nave1Ac()

    Realiza as acoes da nave1 mediante o codigo em key
    
    Parametros:
        key - codigo da tecla
*/
void nave1Ac(int key);

/*
    nave2Ac()

    Realiza as acoes da nave2 mediante o codigo em key
    
    Parametros:
        key - codigo da tecla
*/
void nave2Ac(int key);
