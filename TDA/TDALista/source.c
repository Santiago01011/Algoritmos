#include "main.h"

int cmpInt(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}
//algo
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
    insertarTop5(top, cantTop, dato, *tam, cmp);
}
int insertarTop5(tLista *top, int *cantTop, const void *dato, unsigned tam, Cmp cmp){
    tNodo *nue;
    if(*cantTop < 5){
        ponerEnOrden(top, dato, tam, cmp);
        (*cantTop)++;
        return 1;
    }
    ponerEnOrden(top, dato, tam, cmp);
    sacarUltimoLista(top, NULL, 0);
    return 1;
}

int insertarTop5V2(tLista *top, int *cantTop, const void *dato, unsigned tam, Cmp cmp){
    tNodo *nue;
    if(*cantTop < 5){
        while(*top && cmp((*top)->info, dato) < 0)
        top = &(*top)->sig;
    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL || (nue->info = malloc(tam)) == NULL){
        free(nue);
        return 0;
    }
    memcpy(nue->info, dato, tam);
    nue->tamInfo = tam;
    nue->sig = *top;
    *top = nue;
    (*cantTop)++;
    return 1;
    }
    while(*top && cmp((*top)->info, dato) < 0)
        top = &(*top)->sig;
    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL || (nue->info = malloc(tam)) == NULL){
        free(nue);
        return 0;
    }
    memcpy(nue->info, dato, tam);
    nue->tamInfo = tam;
    nue->sig = *top;
    *top = nue;
    while(*top && (*top)->sig)
        top = &(*top)->sig;
    if(*top == NULL)
        return 0;
    free((*top)->info);
    free(*top);
    *top = NULL;    
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

void insertarEnPodioU(tLista *podio, void *d, size_t tam, Cmp cmp, int *top){
    void *aux, *ult;
    if(*top < 3){
        ponerEnOrden(podio, d, tam, cmp);
        (*top)++;
    }else{
        if((aux = malloc(tam)) && (ult = malloc(tam))){
            verUltimoLista(podio, aux, tam);
            if(cmp(aux, d) > 0){
                ponerEnOrden(podio, d, tam, cmp);
                verUltimoLista(podio, ult, tam);
                if(cmp(ult, aux) != 0)
                    sacarUltimoLista(podio, NULL, 0);
            }
            if(cmp(aux, d) == 0){
                ponerEnOrden(podio, d, tam, cmp);
            }
            free(aux);
        }
    }
}
/*
[9]1
[9]1 -> d
[6]2
[1]3 -> aux, ult
[0]

[0]
*/

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

// void mostrarPodioDist(tLista *podio, Cmp cmp, print_callback printStruct){
//     int top, dist;
//     Resultado *aux;
//     while(*podio){
//         top = 1;
//         aux = (*podio)->info;
//         dist = aux->distri;
//         printf("Distrito %d\n", dist);
//         do{    
//             if(top == 1){
//                 printf("1er: ");
//                 printStruct((*podio)->info);
//                 if((*podio)->sig && cmp((*podio)->info, (*podio)->sig->info) != 0){
//                     top++;
//                 }
//             }else if(top == 2){
//                 printf("2do: ");
//                 printStruct((*podio)->info);
//                 if((*podio)->sig && cmp((*podio)->info, (*podio)->sig->info) != 0){
//                     top++;
//                 }
//             }else if(top == 3){
//                 printf("3ro: ");
//                 printStruct((*podio)->info);
//                 if((*podio)->sig && cmp((*podio)->info, (*podio)->sig->info) != 0){
//                     top++;
//                 }
//             }
//             podio = &(*podio)->sig;
//         }while(*podio && ((Resultado *)(*podio)->info)->distri == dist);
//     }
// }
//podio juli

int insertar_en_podio(tLista* pl, void* dato, size_t tam, Cmp cmp)
{
    int comp, pos = 1;
    unsigned cont = 1;
    tNodo* nue = NULL,
         * elim,
         * actual;
    while(*pl && pos<=3)
    {
        actual = *pl;
        if(!nue && (comp=cmp(actual->info,dato))<0)
        {
            nue = malloc(sizeof(tNodo));
            if(!nue)
                return 0;
            nue->info = malloc(tam);
            if(!nue->info)
            {
                free(nue);
                return 0;
            }
            memcpy(nue->info,dato,tam);
            nue->tamInfo = tam;
            nue->sig = *pl;
            *pl = nue;
            cont++;
            pl = &(*pl)->sig;
        }
        else do
        {
            cont++;
            pl = &(*pl)->sig;
        }while(*pl && (comp=cmp(actual->info,(*pl)->info))==0);
        if(comp)
            pos=cont;
    }
    if(!nue && ((cont<3) ||  !cmp(actual->info,dato)))//si todavia no lo inserte y hay lugar en el podio,
    {                                                 //o no lo inserte y empata con el ultimo
        nue = malloc(sizeof(tNodo));
        if(!nue)
            return 0;
        nue->info = malloc(tam);
        if(!nue->info)
        {
            free(nue);
            return 0;
        }
        memcpy(nue->info,dato,tam);
        nue->tamInfo = tam;
        nue->sig = *pl;
        *pl = nue;
    }
    else if(*pl && pos>3) //elimino los que ya no pertenecen al podio
    {
        while(*pl)
        {
            elim = *pl;
            *pl = elim->sig;
            free(elim->info);
            free(elim);
        }
    }
    if(nue)
        return 1;
    return 0;
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
 * @param cmp Puntero a función de comparación.
 * @return int Devuelve 1 si pudo cargar el archivo, 0 en caso contrario.
 */
int cargarEnListaArch(const char* nombreArch, tLista *lista, size_t tamElem, Cmp cmp){
    FILE* arch;
    void* elem;
    if (!(arch = fopen(nombreArch, "rb")))
        return 0;
    if(!(elem = (void *)malloc(tamElem))){
        return 0;
        fclose(arch);
    }
    while(fread(elem, tamElem, 1, arch) == 1)
        ponerEnOrden(lista, elem, tamElem, cmp);
    free(elem);
    fclose(arch);
    return 1;
}

int txtABin_ALU(const char* nombreArchTxt, const char* nombreBin, size_t tamElem, Conv convertir){
    FILE* archTxt = fopen(nombreArchTxt, "rt");
    if(!archTxt){
        printf("Error al abrir el archivo: %s",nombreArchTxt);
        return 11;
    }
    FILE* archBin = fopen(nombreBin, "wb");
    if(!archBin){
        fclose(archTxt);
        printf("Error al abrir el archivo: %s", nombreBin);
        return 12;
    }
    void* elem = malloc(tamElem);
    if(!elem){
        printf("Error al asignar memoria");
        fclose(archBin);
        fclose(archTxt);
        return 21;
    }
    char cad[1000];
    // fgets(cad, 1000, archTxt); //para saltear encabezado
    while(fgets(cad, 1000, archTxt)){
        if(convertir(cad, elem) == 1)
            fwrite(elem, tamElem, 1, archBin);
    }
    fclose(archTxt);
    fclose(archBin);
    free(elem);
    return 1;
}

int buscarBin(const void* v, const void* elem, Cmp cmp, int *pos, int ce, size_t tam){
    int i = 0, f = ce, m, res;
    while(i <= f){
        m = i + (f - i) / 2;
        // conseguir el elemento del medio del vector
        const void *med = (char*)v + m * tam;   
        res = cmp(med, elem);
        if(res == 0){
            *pos = m;
            return 1;
        }else if(res < 0){
            i = m + 1;
        }else {
            f = m - 1;
        }
    }
    *pos = -1;
    return 0;
}