#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaSimpleEnlazada/listaEnlazada.h"

typedef struct{
    int numero;
    char nombre[25];
}Agrupacion;

typedef struct{
    int nagrup; //num agrupacion, de 1 a 9999
    int region; //num region, de 1 a 9
    int distri; //num distrito, de 1 a 20
}Voto;

typedef void (*print_callback)(const void *);
typedef int (*Conv)(const char*, void*);

int cmpInt(const void *a, const void *b);
int cmpIntDesc(const void *a, const void *b);
void imprimirLista(void* d, void* param);
int mostrarArchivoGen(const char* nombreArch, size_t tamElem, print_callback printStruct);
int cargarEnListaArch(const char* nombreArch, tLista *lista, size_t tamElem);

int convertirRegla(const char* linea, void* elem);
int txtABin_ALU(const char* nombreArchTxt, const char* nombreBin, size_t tamElem, Conv convertir);

//ejercicio podio
void insertarEnPodio(tLista *podio, tLista *p, Cmp cmp);
void mostrarPodio(tLista *podio, Cmp cmp, print_callback printStruct);
//ejercicio insertar top 10
int insertarTop10(tLista *top, int* cantTop, const void* dato, unsigned tam, Cmp cmp);
void mapTop10(void *dato, void *contexto);




