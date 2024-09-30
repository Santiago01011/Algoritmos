#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaSimpleEnlazada/listaEnlazada.h"

int cmpInt(const void *a, const void *b);
int cmpIntDesc(const void *a, const void *b);

//ejercicio podio
void insertarEnPodio(tLista *podio, tLista *p, int (*cmp)(const void *, const void *));
void mostrarPodio(tLista *podio, int (*cmp)(const void *, const void *));
//ejercicio insertar top 10
int insertarTop10(tLista *top, int cantTop, const void* dato, unsigned tam, int (*cmp)(const void *, const void *));




