#ifndef listaEnlazada_h
#define listaEnlazada_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
} tNodo;

typedef tNodo *tLista;

//prototipos
void crearLista(tLista *p);
int listaVacia(const tLista *p);
int listaLlena(const tLista *p, unsigned cantBytes);
void vaciarLista(tLista *p);
int ponerAlComienzo(tLista *p, const void *d, unsigned cantBytes);
int sacarPrimeroLista(tLista *p, void *d, unsigned cantBytes);
int verPrimeroLista(const tLista *p, void *d, unsigned cantBytes);
int ponerAlFinal(tLista *p, const void *d, unsigned cantBytes);
int sacarUltimoLista(tLista *p, void *d, unsigned cantBytes);
int verUltimoLista(const tLista *p, void *d, unsigned cantBytes);
int ponerEnOrden(tLista *p, const void *d, unsigned cantBytes, int (*cmp)(const void *, const void *));
int ordenarListaInsercion(tLista *p, int (*cmp)(const void *, const void *));
void map(tLista *p, void accion(void*, void*), void *param);
void filter(tLista *p, int condicion(const void*, void*), void *param);
void* reduce(tLista *p, void *res, void accion(const void*, void*, void*), void *param);
#endif