#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaSimpleEnlazada/listaEnlazada.h"

typedef struct{
    int codProd;
    char descrp[30];
    int stock;
    float precio;
}Producto;

typedef struct{
    int codProd;
    char descrp[30];
    int cantidad;
}Movimiento;

typedef int (*Cmp)(const void *, const void *);
typedef void (*print_callback)(const void *);

int cmpInt(const void *a, const void *b);
int cmpIntDesc(const void *a, const void *b);
int cmpPrecio(const void *a, const void *b);
void imprimirLista(void* d, void* param);
int mostrarArchivoGen(const char* nombreArch, size_t tamElem, print_callback printStruct);
void printProducto(const void *p);
int cargarEnListaArch(const char* nombreArch, tLista *lista, size_t tamElem);

//ejercicio podio
void insertarEnPodio(tLista *podio, tLista *p, Cmp cmp);
void printPodio(void* d, void* contexto);
//ejercicio insertar top 10
int insertarTop10(tLista *top, int* cantTop, const void* dato, unsigned tam, Cmp cmp);
void mapTop10(void *dato, void *contexto);




