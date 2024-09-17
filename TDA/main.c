#include "main.h"

int cmpInt(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}

int main(){
    tLista lista;
    crearLista(&lista);
    int x = 5;
    ponerAlComienzo(&lista, &x, sizeof(int));
    int y;
    verPrimeroLista(&lista, &y, sizeof(int));
    printf("%d\n", y);
    x=4;
    ponerAlFinal(&lista, &x, sizeof(int));
    verUltimoLista(&lista, &y, sizeof(int));
    printf("%d\n", y);
    x=3;
    ponerEnOrden(&lista, &x, sizeof(int), cmpInt);
    x=7;
    ponerAlComienzo(&lista, &x, sizeof(int));
    verPrimeroLista(&lista, &y, sizeof(int));
    printf("%d\n", y);
    puts("Lista:");
    for(tNodo *i = lista; i; i = i->sig){
        printf("%d\n", *(int *)i->info);
    }
    vaciarLista(&lista);
    return 0;
}