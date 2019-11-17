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

int teclas[2][4];

/*
    menuActions()

    realiza a acao 'acao'

    Parametros:
        WINDOW *w - ponteiro para a janela de onde serao identificadas as teclas
        int acao - codigo da acao a ser realizada:
            0 = desce a seta
            1 = sobe a seta
            2 = confirma opcao
*/
void menuActions(WINDOW *w, int acao);

/*
    checkForMenuActions()

    Checa se a ultima tecla pressionada e' uma acao valida do menu
    Assume que InitKDB() ja foi dado

    Parametros:
        WINDOW *w - ponteiro para a janela de onde serao identificadas as teclas
*/
void checkForMenuActions(WINDOW *w);

/*
    iniciaTeclas()

    Inicia todas as teclas como não pressionadas.
*/
void iniciaTeclas();

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
    naveAc()

    Realiza as acoes das naves.
*/
void naveAc();
