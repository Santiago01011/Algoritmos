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

void insertarEnPodioU(tLista *podio, void *d, size_t tam, Cmp cmp, int *top){
    tNodo *nue;
    if(*top < 3){
        ponerEnOrden(podio, d, tam, cmp);
        (*top)++;
    }else{
        ponerEnOrden(podio, d, tam, cmp);
        sacarUltimoLista(podio, NULL, 0);
        (*top)++;
    }
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

int convertirRegla(const char* linea, void* elem){
    Agrupacion* aux = (Agrupacion*)elem;
    if(sscanf(linea, "%d%25[^\n]", &aux->numero, aux->nombre) == 2)
        return 1;
    return 0;
}

int cmpAgru(const void *a, const void *b){
    Agrupacion *agr1 = (Agrupacion *)a;
    Agrupacion *agr2 = (Agrupacion *)b;
    return agr1->numero - agr2->numero;
}

int cmpAgruNombre(const void *a, const void *b){
    Agrupacion *agr1 = (Agrupacion *)a;
    Agrupacion *agr2 = (Agrupacion *)b;
    return strcmp(agr1->nombre, agr2->nombre);
}

int cmpRes(const void *a, const void *b){
    return ((Resultado *)b)->votosD - ((Resultado *)a)->votosD;
}

int leerAgrup(Agrupacion vec[]){
    int i = 0;
    char linea[100];
    void * elem;
    FILE* arch = fopen("../archTests/agrupaciones.txt", "r");
    if(!arch){
        puts("Error al abrir el archivo");
        return 0;
    }
    while(fgets(linea, 100, arch)){
        if(convertirRegla(linea, &vec[i]) == 1)
            i++;
    }
    fclose(arch);
    return i;
}

void leerVotos(int votosDistritos[MAX_AGRUP][MAX_DISTRI], Agrupacion vec[], int cantAgrup) {
    Voto aux;
    FILE *arch = fopen("../archTests/votos.dat", "rb");
    if (!arch) {
        puts("Error al abrir el archivo");
        return;
    }

    while (fread(&aux, sizeof(Voto), 1, arch) == 1) {
        int pos;
        if (buscarBin(vec, &aux, cmpAgru, &pos, cantAgrup, sizeof(Agrupacion)) == 1) {
            votosDistritos[pos][aux.distri - 1]++;
        }
    }

    fclose(arch);

    printf("      ");
    for(int i=0; i< MAX_DISTRI; i++){
        printf("%3d ", i+1);
    }
    puts("");
    for(int i = 0; i < cantAgrup; i++){
        printf("%4d: ", vec[i].numero);
        for(int j = 0; j < MAX_DISTRI; j++){
            printf("%3d ", votosDistritos[i][j]);
        }
        puts("");
    }
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