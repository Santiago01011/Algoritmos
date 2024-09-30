#include "main.h"

void printProducto(const void *p){
    Producto *prod = (Producto *)p;
    printf("Cod: %d, Descrp: %s, Stock: %d, Precio: %.2f\n", prod->codProd, prod->descrp, prod->stock, prod->precio);
}

void printMovimiento(const void *m){
    Movimiento *mov = (Movimiento *)m;
    printf("Cod: %d, Descrp: %s, Cantidad: %d\n", mov->codProd, mov->descrp, mov->cantidad);
}

int cmpInt(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}

int cmpIntDesc(const void *a, const void *b){
    return *(int *)b - *(int *)a;
}

int cmpPrecio(const void *a, const void *b){
    return ((Producto *)b)->precio - ((Producto *)a)->precio;
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

void mostrarPodio(tLista *podio, int (*cmp)(const void *, const void *), void (*print_callback)(const void*)){
    puts("Podio:");
    int top = 1;
    for(tNodo *i = *podio; i; i = i->sig) {
        if(top == 1){
            printf("1er: ");
            print_callback(i->info);
            if(i->sig && cmp(i->info, i->sig->info) != 0){
                top++;
            }
        }else if(top == 2){
            printf("2do: ");
            print_callback(i->info);
            if(i->sig && cmp(i->info, i->sig->info) != 0){
                top++;
            }
        }else{
            printf("3er: ");
            print_callback(i->info); 
        }
    }
}

//ejercicio con archivo productos

int mostrarArchivoGen(const char* nombreArch, size_t tamElem, void (*print_callback)(const void*)){
    FILE *arch;
    void *elem;
    if((arch = fopen(nombreArch, "rb")) == NULL)
        return 0;
    elem = malloc(tamElem);
    if(elem == NULL){
        fclose(arch);
        return 0;
    }
    printf("-----------------Archivo: %s-----------------\n", nombreArch);
    while(fread(elem, tamElem, 1, arch) == 1){
        print_callback(elem);
    }
    puts("---------------------------------------------");
    free(elem);
    fclose(arch);
    return 1;
}

int cargarProductosEnLista(const char* nombreArch, tLista *lista) {
    FILE *arch;
    Producto prod;
    if (!(arch = fopen(nombreArch, "rb")))
        return 0;
    while(fread(&prod, sizeof(Producto), 1, arch))
        ponerAlFinal(lista, &prod, sizeof(Producto));
    fclose(arch);
    return 1;
}

int cargarEnListaArch(const char* nombreArch, tLista *lista, size_t tamElem){
    FILE* arch;
    void* elem;
    if (!(arch = fopen(nombreArch, "rb")))
        return 0;
    if(!(elem = (void *)malloc(tamElem))){
        return 0;
        fclose(arch);
    }
    while(fread(elem, tamElem, 1, arch) == 1)
        ponerAlFinal(lista, elem, tamElem);
    fclose(arch);
    return 1;
}

