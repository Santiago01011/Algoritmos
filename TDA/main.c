#include "main.h"

int cmpInt(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}

int cmpIntDesc(const void *a, const void *b){
    return *(int *)b - *(int *)a;
}

int main(){
    tLista lista;
    crearLista(&lista);
    tLista podio;
    crearLista(&podio);


    int a = 1124, b = 456, c = 31;
    ponerAlComienzo(&lista, &a, sizeof(int));
    ponerAlComienzo(&lista, &a, sizeof(int));

    ponerAlComienzo(&lista, &b, sizeof(int));
    ponerAlComienzo(&lista, &c, sizeof(int));
    ponerAlComienzo(&lista, &c, sizeof(int));
    ponerAlComienzo(&lista, &c, sizeof(int));
    ponerAlComienzo(&lista, &c, sizeof(int));

    ordenarListaInsercion(&lista, cmpIntDesc);
    puts("Lista Ordenada:");
    for(tNodo *i = lista; i; i = i->sig){
        printf("%d\n", *(int *)i->info);
    }
    insertarEnPodio(&podio, &lista, cmpInt);
    vaciarLista(&lista);
    return 0;
}