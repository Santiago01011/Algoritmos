#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaSimpleEnlazada/listaEnlazada.h"
#define MAX_AGRUP 99
#define MAX_DISTRI 20
//Dado un archivo binario “lote.dat” cuyos registros, no están ordenados y tienen la siguiente estructura:
// • Provincia: 99 (dos dígitos – 23 provincias numeradas del 01 al 23)
// • Localidad: xxx...x (50 caracteres)
// • Superficie: 99999.99 (kilómetros cuadrados)
// • Población: 9999 (habitantes)
typedef struct{
    int numProv;
    char loc[51];
    float sup;
    int pob;
}Lote;

typedef void (*print_callback)(const void *);
typedef int (*Conv)(const char*, void*);

int cmpInt(const void *a, const void *b);
int cmpIntDesc(const void *a, const void *b);
void imprimirLista(void* d, void* param);

//parcial lotes
int cmpSup(const void *a, const void *b);
void printLote(const void *l);



//genericos archivos
int mostrarArchivoGen(const char* nombreArch, size_t tamElem, print_callback printStruct);
int txtABin_ALU(const char* nombreArchTxt, const char* nombreBin, size_t tamElem, Conv convertir);
int cargarEnListaArch(const char* nombreArch, tLista *lista, size_t tamElem);

//ejercicio podio
void insertarEnPodio(tLista *podio, tLista *p, Cmp cmp);
void insertarEnPodioU(tLista *podio, void *d, size_t tam, Cmp cmp, int *top);
void mostrarPodio(tLista *podio, Cmp cmp, print_callback printStruct);
int insertar_en_podio(tLista* pl, void* dato, size_t tam, Cmp cmp);
//ejercicio insertar top 10
int insertarTop5(tLista *top, int* cantTop, const void* dato, unsigned tam, Cmp cmp);
int insertarTop5V2(tLista *top, int *cantTop, const void *dato, unsigned tam, Cmp cmp);
void mapTop10(void *dato, void *contexto);




