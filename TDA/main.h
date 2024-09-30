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

int cmpInt(const void *a, const void *b);
int cmpIntDesc(const void *a, const void *b);
int cmpPrecio(const void *a, const void *b);
int mostrarArchivoGen(const char* nombreArch, size_t tamElem, void (*print_callback)(const void*));
void printProducto(const void *p);
void printMovimiento(const void *m);
int cargarProductosEnLista(const char* nombreArch, tLista *lista);
int cargarEnListaArch(const char* nombreArch, tLista *lista, size_t tamElem);


//ejercicio podio
void insertarEnPodio(tLista *podio, tLista *p, int (*cmp)(const void *, const void *));
void mostrarPodio(tLista *podio, int (*cmp)(const void *, const void *), void (*print_callback)(const void*));
//ejercicio insertar top 10
int insertarTop10(tLista *top, int cantTop, const void* dato, unsigned tam, int (*cmp)(const void *, const void *));




