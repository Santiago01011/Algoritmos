#include "main.h"

int cmpInt(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}

int cmpIntDesc(const void *a, const void *b){
    return *(int *)b - *(int *)a;
}

//ejercicio insertar top 10: los primeros 10 entran directo y de forma ordenada,
// y cuando quiero insertar otro debo comparar para saber si entra y eliminar el
//�ltimo en caso de que entre.

int insertarTop10(tLista *top, int cantTop, const void* dato, unsigned tam, int (*cmp)(const void *, const void *)){
    tNodo *nue;
    if(cantTop < 10){
        ponerEnOrden(top, dato, tam, cmp);
        return 1;
    }
    ponerEnOrden(top, dato, tam, cmp);
    sacarUltimoLista(top, NULL, 0);
    return 1;
}

//Ejercicio Podio agregar a una lista los 3 primeros elementos de la lista, si hay mas de un top 1, 
//se va descontando los lugres del podio, lo mismo con los top 2, top 3 cantidad de elementos iguales
//ejercicio podio: puedo tener muchos primeros, segundos y terceros si est�n empatados
//si tengo dos primeros, no hay segundo.
//si tengo tres primeros, no hay segundo ni tercero.
//voy contabilizando los primeros y segundos.

void insertarEnPodio(tLista *podio, tLista *p, int (*cmp)(const void *, const void *)){
    int top = 0;
    tNodo *aux;
    while(*p){
        if(top < 3){
            aux = *p;
            ponerAlFinal(podio, aux->info, aux->tamInfo);
            top++;
        }
        else{
            verUltimoLista(podio, aux->info, aux->tamInfo);
            if(cmp(aux->info, (*p)->info) == 0)
                ponerAlFinal(podio, (*p)->info, (*p)->tamInfo);
        }
        p = &(*p)->sig;
    }
}

void mostrarPodio(tLista *podio, int (*cmp)(const void *, const void *)){
    puts("Podio:");
    int top = 1;
    for(tNodo *i = *podio; i; i = i->sig) {
        if(top == 1){
            printf("1er: %d\n", *(int *)i->info);
            if(i->sig && cmp(i->info, i->sig->info) != 0){
                top++;
            }
        }else if(top == 2){
            printf("2do: %d\n", *(int *)i->info);
            if(i->sig && cmp(i->info, i->sig->info) != 0){
                top++;
            }
        }else{
            printf("3ro: %d\n", *(int *)i->info);
        }
    }
}
