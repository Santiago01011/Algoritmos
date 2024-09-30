#include "main.h"

void printProducto(const void *p){
    Producto *prod = (Producto *)p;
    printf("Cod: %d, Descrp: %s, Stock: %d, Precio: %.2f\n", prod->codProd, prod->descrp, prod->stock, prod->precio);
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

void imprimirLista(void* d, void* param){
    print_callback printStruct = (print_callback)param;
    printStruct(d);
}
//ejercicio insertar top 10: 
int insertarTop10(tLista *top, int* cantTop, const void* dato, unsigned tam, Cmp cmp){
    tNodo *nue;
    if(*cantTop < 10){
        ponerEnOrden(top, dato, tam, cmp);
        (*cantTop)++;
        return 1;
    }
    ponerEnOrden(top, dato, tam, cmp);
    sacarUltimoLista(top, NULL, 0);
    return 1;
}

void mapTop10(void *dato, void *contexto) {
    tLista *top10 = ((tLista **)contexto)[0];
    int *cantTop = ((int **)contexto)[1];
    Cmp cmp = ((Cmp *)contexto)[2];
    insertarTop10(top10, cantTop, dato, sizeof(Producto), cmp);
}
//Ejercicio Podio agregar los 3 primeros elementos de la lista, si hay empate se agrega segun regla top3
void insertarEnPodio(tLista *podio, tLista *p, Cmp cmp){
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

void printPodio(void* d, void* contexto){
    Producto *prod = (Producto *)d;
    int *top = ((int **)contexto)[0];
    print_callback printStruct = ((print_callback*)contexto)[1];
    if(*top == 1){
        printf("1er: ");
        printStruct(prod);
    }else if(*top == 2){
        printf("2do: ");
        printStruct(prod);
    }else{
        printf("3er: ");
        printStruct(prod);
    }
    (*top)++;
}

//ejercicio con archivo productos

int mostrarArchivoGen(const char* nombreArch, size_t tamElem, print_callback printStruct){
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
        printStruct(elem);
    }
    puts("---------------------------------------------");
    free(elem);
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

