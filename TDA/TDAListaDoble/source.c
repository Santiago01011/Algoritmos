#include "main.h"

void imprimirLista(void* d, void* param){
    print_callback printStruct = (print_callback)param;
    printStruct(d);
}

int cmpInt(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}

