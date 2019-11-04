/*
    addDelay()

    Adiciona delay para o movimento corresponder ao tempo
determinado.
    Obs: implementado para debug.
*/
void addDelay(double segundos) {
    clock_t tempo_inicial = clock();
    while (clock() < tempo_inicial + segundos*CLOCKS_PER_SEC);
}

/*
    mostraPosicoes()

    Imprime posições das naves e dos projéteis.
*/
void mostraPosicoes() {
    int i;
    printf("(%7.2lf, %7.2lf) | ", nave1.pos[0], nave1.pos[1]);
    printf("(%7.2lf, %7.2lf)", nave2.pos[0], nave2.pos[1]);
    for (i = 0; i < nProjeteis; i++) {
        printf(" | (%7.2lf, %7.2lf)", i, projeteis[i].pos[0], projeteis[i].pos[1]);
    }
    printf("\n");
}
