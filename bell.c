#include<stdio.h>
#include <unistd.h>
#include "xwc.h"

int main(){
    WINDOW * w;
    int a = 0;
    w = InitGraph(800, 800, "Janelinha");
    InitKBD(w);
        
    while(a != 36){
        if(WCheckKBD(w)) printf("aaaa tecla: %d\n", a = WGetKey(w));
        while(WCheckKBD(w) && WGetKey(w) == a);
        printf("aaaa tecla: %d\n", a = WGetKey(w));
        /* se tentar segurar duas teclas, apenas uma aparecera, porque quando uma tecla e' pressionada 
        ele fica recebendo eventos de que esta pressionando e soltando
        */
        usleep(100);
    }
    

    return 0;
}