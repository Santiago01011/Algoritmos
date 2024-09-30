#include "main.h"

int cmpInt(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}

int cmpIntDesc(const void *a, const void *b){
    return *(int *)b - *(int *)a;
}
/**
 * @brief Imprime un dato de la lista.
 * 
 * Imprime el dato utilizando la función de impresión recibida por param.
 * 
 * @param d Puntero al dato que se va a imprimir.
 * @param param Puntero a una función de impresión.
 */
void imprimirLista(void* d, void* param){
    print_callback printStruct = (print_callback)param;
    printStruct(d);
}
//ejercicio insertar top 10:

/**
 * @brief Inserta un elemento en la lista top 10 manteniendo el orden y el tamaño máximo.
 *
 * Esta función recibe un dato y un contexto que contiene la lista top 10, un contador de elementos en el top 10,
 * una función de comparación y el tamaño de los elementos. Inserta el dato en la lista top 10 si cumple con los
 * criterios de orden y tamaño.
 *
 * @param dato Puntero al dato que se va a insertar en la lista top 10.
 * @param contexto Puntero a un vector que contiene:
 *                 - tLista*: Puntero a la lista top 10.
 *                 - int*: Puntero al contador de elementos en el top 10.
 *                 - Cmp: Puntero a función de comparación para ordenar los elementos.
 *                 - unsigned: Tamaño de los elementos.
 */
void mapTop10(void *dato, void *contexto) {
    tLista *top = ((tLista **)contexto)[0];
    int *cantTop = ((int **)contexto)[1];
    Cmp cmp = ((Cmp *)contexto)[2];
    unsigned *tam = ((unsigned **)contexto)[3];
    insertarTop10(top, cantTop, dato, *tam, cmp);
}
int insertarTop10(tLista *top, int *cantTop, const void *dato, unsigned tam, Cmp cmp){
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

//Ejercicio Podio agregar los 3 primeros elementos de la lista, si hay empate se agrega segun regla top3.
/**
 * @brief Inserta un podio en una lista.
 *
 * Esta función recibe un lista podio y una lista de elementos. Inserta los primeros 3 elementos de la lista en el podio.
 * Si hay empate, se agrega el elemento según la regla top3.
 *
 * @param podio Puntero a la lista podio.
 * @param p Puntero a la lista de elementos.
 * @param cmp Función de comparación para ordenar los elementos.
 */
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

/**
 * @brief Imprime un dato del podio.
 * 
 * Imprime el dato del podio utilizando la función de impresión recibida por contexto.
 * 
 * @param d Puntero al dato que se va a imprimir.
 * @param contexto Puntero a un vector que contiene:
 *                - int*: Puntero al contador de elementos en el podio.
 *                - print_callback: Función de impresión.
 *                - Cmp: Puntero a función de comparación para ordenar los elementos.
 *                - void*: Puntero al ultimo dato de podio
 */
void printPodio(void* d, void* contexto){
    int *top = ((int **)contexto)[0];
    print_callback printStruct = ((print_callback*)contexto)[1];
    Cmp cmp = ((Cmp*)contexto)[2];
    if(*top == 1){
        printf("1er: ");
        printStruct(d);
    }else if(*top == 2){
        printf("2do: ");
        printStruct(d);
    }else{
        printf("3er: ");
        printStruct(d);
    }
    (*top)++;
}

void mostrarPodio(tLista *podio, Cmp cmp, print_callback printStruct){
    puts("Podio:");
    int top = 1;
    for(tNodo *i = *podio; i; i = i->sig) {
        if(top == 1){
            printf("1er: ");
            printStruct(i->info);
            if(i->sig && cmp(i->info, i->sig->info) != 0){
                top++;
            }
        }else if(top == 2){
            printf("2do: ");
            printStruct(i->info);
            if(i->sig && cmp(i->info, i->sig->info) != 0){
                top++;
            }
        }else{
            printf("3ro:");
            printStruct(i->info);
        }
    }
}

//funciones genericas para archivos

/**
 * @brief Muestra un archivo binario de forma generica.
 * 
 * Muestra el contenido de un archivo utilizando la función de impresión recibida por printStruct.
 * 
 * @param nombreArch Puntero a la ruta del archivo que se va a mostrar.
 * @param tamElem Tamaño de los elementos del archivo.
 * @param printStruct puntero a función de impresión.
 * @return int Devuelve 1 si se pudo abrir el archivo, 0 en caso contrario.
 */
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

/**
 * @brief Carga un archivo binario en una lista.
 * 
 * Carga el contenido de un archivo en una lista.
 * 
 * @param nombreArch Puntero a la ruta del archivo que se va a cargar.
 * @param lista Puntero a la lista donde se va a cargar el archivo.
 * @param tamElem Tamaño de los elementos del archivo.
 * @return int Devuelve 1 si pudo cargar el archivo, 0 en caso contrario.
 */
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

