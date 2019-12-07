#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

void *mallocSafe(size_t tam) {
    void *ptr;
    ptr = malloc(tam);
    if (ptr == NULL) {
        printf("Não foi possível alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

int mod(int a, int b) {
    return a > 0 ? a % b : (a % b + b) % b;
}

double modD(double a, double b) {
    return a > 0.0 ? fmod(a, b) : fmod((fmod(a, b) + b), b);
}

double absD(double n) {
    return n > 0 ? n : -n;
}
