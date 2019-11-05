#include<stdio.h>
#include "xwc.h"


int main(){
    WINDOW *w;
    w = InitGraph(800, 800, "Barney é um dinossauro");
    InitKBD(w);
    while(WGetKey(w) != 36){
        printf("Digite algo\n");
    }

    printf("DIGITOU!!!!\n");

    return 0;
}