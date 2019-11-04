#include <stdio.h>
#include <unistd.h>
#include "tick.h"
#include "display.h"
#include "objetos.h"
#include "io.h"
#include "fisica.h"

static long int tick = 0;

void gameLoop() {
    int i;
    WINDOW *w;
    PIC rasc;
    PIC fundo;
    int nProjeteis = leiaArquivo();

    passoSimulacao = 1.0 / (FRAMES_PER_SECOND * TICKS_PER_FRAME);
    w = InitGraph(WIDTH, HEIGHT, "My windows xp");
    rasc = NewPic(w, WIDTH, HEIGHT);
    carregaObjetos(w);
    printf("Carregando assets/background.xpm...\n");
    fundo = ReadPic(w, "assets/background.xpm", NULL);
    printf("Passo simulação = %lf\n", passoSimulacao);

    while (1) {
        atualizaPosicoes();
        detectaColisoes();
        if (tick % TICKS_PER_FRAME == 0) {
            PutPic(rasc, fundo, 0, 0, WIDTH, HEIGHT, 0, 0);
            imprimaObjetos(rasc);
            PutPic(w, rasc, 0, 0, WIDTH, HEIGHT, 0, 0);
        }
        usleep(1000000.0 * passoSimulacao);
        tick++;
    }

    CloseGraph();
}
