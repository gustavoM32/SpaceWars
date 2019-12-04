/*
    Fase 1 - MAC0216
    Equipe:
        Gustavo de Medeiros Carlos, 11276298
        Luiza Barros Reis Soezima, 11221842
        Marcos Siolin Martins, 11221709
*/
#include <stdlib.h>
#include <stdio.h>
#include "debug.h"
#include "game.h"
#include "scanner.h"
#include "sounds.h"

int main() {
    loadSettings();
    checkForSoundPlayer();
    game();
    return EXIT_SUCCESS;
}
