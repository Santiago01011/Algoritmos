#include "main.h"

int main(){
    tLista lista;
    crearLista(&lista);
    tLista top10;
    crearLista(&top10);
    tLista podio;
    crearLista(&podio);
    int cantTop = 0;
    int *dato;
    int vec[] = {101, 241, 8135 ,8135 , 72, 11, 55, 83, 2734, 4367, 723, 632, 423, 213, 6};
    //cargar los elementos de vec en la lista en el mismo orden que se reciben
    for(int i = 0; i < sizeof(vec)/sizeof(int); i++){
        ponerAlFinal(&lista, &vec[i], sizeof(int));
    }
    //mostrar los elementos de la lista
    for(tNodo *i = lista; i; i = i->sig){
        printf("%d \n", *(int *)i->info);
    }
    puts("Top 10");
    //cargar los elementos de lista en el top10
    for(tNodo *i = lista; i; i = i->sig){
        insertarTop10(&top10, cantTop, i->info, i->tamInfo, cmpIntDesc);
        cantTop++;
    }
    //mostrar los elementos de top10
    cantTop = 1;
    for(tNodo *i = top10; i; i = i->sig){
        printf("%d: %d\n",cantTop ,*(int *)i->info);
        cantTop++;
    }
    //insertar en podio de top10
    insertarEnPodio(&podio, &top10, cmpIntDesc);
    //mostrar podio
    mostrarPodio(&podio, cmpIntDesc);
    //vaciar las listas
    vaciarLista(&podio);
    vaciarLista(&top10);
    vaciarLista(&lista);
    return 0;
}