#include "listaEnlazada.h"

#define minimo(x, y) ((x) <= (y) ? (x) : (y))



void crearLista(tLista *p){
    *p = NULL;
}

int listaVacia(const tLista *p){
    return *p == NULL;
}

int listaLlena(const tLista *p, unsigned cantBytes){
    tNodo *aux = (tNodo *)malloc(sizeof(tNodo));
    void *info = malloc(cantBytes);
    free(info);
    free(aux);
    return info == NULL || aux == NULL;
}

void vaciarLista(tLista *p){
    while (*p){
        tNodo *aux = *p;
        *p = aux->sig;
        free(aux->info);
        free(aux);
    }    
}

int ponerAlComienzo(tLista *p, const void *d, unsigned cantBytes){
    tNodo *nue;
    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL ||
    (nue->info = malloc(cantBytes)) == NULL){
        free(nue);
        return 0;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = *p;
    *p = nue;
    return 1;
}

int sacarPrimeroLista(tLista *p, void *d, unsigned cantBytes){
    tNodo *aux = *p;

    if(aux == NULL)
        return 0;
    *p = aux->sig;
    memcpy(d, aux->info, minimo(cantBytes, aux->tamInfo));
    free(aux->info);
    free(aux);
    return 1;
}

int verPrimeroLista(const tLista *p, void *d, unsigned cantBytes){
    if(*p == NULL)
        return 0;
    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));
    return 1;
}

int ponerAlFinal(tLista *p, const void *d, unsigned cantBytes){
    tNodo *nue;
    while(*p)
        p = &(*p)->sig;
    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL ||
    (nue->info = malloc(cantBytes)) == NULL){
        free(nue);
        return 0;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = NULL;
    *p = nue;
    return 1;
}

int sacarUltimoLista(tLista *p, void *d, unsigned cantBytes){
    while(*p && (*p)->sig)
        p = &(*p)->sig;
    if(*p == NULL)
        return 0;
    tNodo *aux = *p;
    memcpy(d, aux->info, minimo(cantBytes, aux->tamInfo));
    free(aux->info);
    free(aux);
    *p = NULL;
    return 1;
}

int verUltimoLista(const tLista *p, void *d, unsigned cantBytes){
    while(*p && (*p)->sig)
        p = &(*p)->sig;
    if(*p == NULL)
        return 0;
    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));
    return 1;
}

int ponerEnOrden(tLista *p, const void *d, unsigned cantBytes, int (*cmp)(const void *, const void *)){
    tNodo *nue;
    while(*p && cmp((*p)->info, d) < 0)
        p = &(*p)->sig;
    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL ||
    (nue->info = malloc(cantBytes)) == NULL){
        free(nue);
        return 0;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = *p;
    *p = nue;
    return 1;
}

void ordenarListaInsercion(tLista *p, int (*cmp)(const void *, const void *)){
    tLista listaOrdenada;
    crearLista(&listaOrdenada);
    while(*p){
        tNodo *aux = *p;
        *p = aux->sig;
        aux->sig = NULL;
        tNodo **q = &listaOrdenada;
        while(*q && cmp((*q)->info, aux->info) < 0)
            q = &(*q)->sig;
        aux->sig = *q;
        *q = aux;
    }
    *p = listaOrdenada;
}

void map(tLista *p, void accion(void*, void*), void *param){
    while(*p){
        accion((*p)->info, param);
        p = &(*p)->sig;
    }
}

void filter(tLista *p, int condicion(const void*, void*), void *param){
    tNodo *aux;
    while(*p){
        if(!condicion((*p)->info, param)){ //si condicion devuelve 0, elimino el nodo. Si devuelve 1, avanzo.
            aux = *p;
            *p = aux->sig;
            free(aux->info);
            free(aux);
        }else{
            p = &(*p)->sig;
        }
    }
}

void* reduce(tLista *p, void *res, void accion(const void*, void*, void*), void *param){
    while(*p){
        accion((*p)->info, res, param);
        p = &(*p)->sig;
    }
    return res;
}


//ejercicio insertar top 10: los primeros 10 entran directo y de forma ordenada,
// y cuando quiero insertar otro debo comparar para saber si entra y eliminar el
//�ltimo en caso de que entre.

//Ejercicio Podio agregar a una lista los 3 primeros elementos de la lista, si hay mas de un top 1, 
//se va descontando los lugres del podio, lo mismo con los top 2, top 3 cantidad de elementos iguales
//ejercicio podio: puedo tener muchos primeros, segundos y terceros si est�n empatados
//si tengo dos primeros, no hay segundo.
//si tengo tres primeros, no hay segundo ni tercero.
//voy contabilizando los primeros y segundos.

void insertarEnPodio(tLista *p, int (*cmp)(const void *, const void *)){ //*p es una lista ordenada
    int pri = 0, seg = 0 , ter = 0;
    tLista podio;
    crearLista(&podio);
    tNodo *auxPod , *auxN;

    while(*p && (pri + seg + ter) < 3){
        
        if(pri + seg + ter < 3){
            if(pri == 0 || cmp((*p)->info, podio->info) == 0){
                ponerAlFinal(&podio, (*p)->info, (*p)->tamInfo);
                auxN = *p;
                *p = auxN->sig;
                pri++;
            }
            else if(seg == 0 || cmp((*p)->info, podio->info) == 0){ //cmp devuelve 1 si el primero es mayor
                ponerAlFinal(&podio, (*p)->info, (*p)->tamInfo);
                auxN = *p;
                *p = auxN->sig;
                seg++;            
            }
            else if(cmp((*p)->info, podio->info) == 0){
                ponerAlFinal(&podio, (*p)->info, (*p)->tamInfo);
                auxN = *p;
                *p = auxN->sig;                
            }
        }
        printf("pri: %d, seg: %d, ter: %d\n", pri, seg, ter);
        getchar();
    }
    puts("Podio:");
    for(tNodo *i = podio; i; i = i->sig){
        printf("%d\n", *(int *)i->info);
    }
} 
