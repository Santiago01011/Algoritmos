#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu/menu.h"
#include "../../TDA/TDALista/listaSimpleEnlazada/listaEnlazada.h"

// La estructura de cada registro es:
// • patente: cada patente tiene el formato AB123CD
// • nroCuota: número entero de 1 a 6
// • titular: apellido y nombre (25 caracteres)
// • dni: número entero entre 1.000.000 y 99.999.999
// • vto: fecha de vencimiento aaaa/mm/dd (año, mes, día)  (vamos a usar TDA fecha)
// • importe: importe máximo 99.999,99

#define RUTARCH "archivos/impuestosVencidos.dat"
#define RUTATXT "archivos/deuda.txt"

typedef struct{
    int dia;
    int mes;
    int anio;
}tFecha;

typedef struct{
    char patente[8];
    int nroCuota;
    char titular[26];
    int dni;
    tFecha vto;
    float importe;
}tImpuesto;

typedef void (*printStruct)(const void *);
typedef void (*Actualizar) (void*, void*);

//resolucion de la consigna

//genericas
void generarArchivo();
tFecha ingresarFechaAct();
int mostrarArchGen(const char *ruta, size_t tam, printStruct prints);
void printImpuesto(const void *imp);
void imprimirLista(void* d, void* param);
void fprintImpuestoDniPatente(const void *imp, FILE* pf);
void fprintImpuestoDni(const void *imp, FILE* pf);
int cmpDni(const void *a, const void *b);
void actualizarImporte(void* d, void* param);
void generarDeudaTXT(const char *ruta, tLista *p , void fprints(const void*, FILE*));


#endif // MAIN_H_INCLUDED
