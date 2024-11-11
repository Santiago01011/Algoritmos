#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../TDA/TDAArbol/Arbol.h"

typedef struct{
    char nombre[40];
    int dni;
    char estado;
}tAlumno;

typedef struct{
    int reg;
    int dni;
}Idx;

typedef void (*printStruct)(void*);

char menuConErr(const char *msg, const char *opc);
void generarArch();
void printAlumno(void* alu);
void printIdx(void* idx);
int mostrarArchGen(const char *ruta, size_t tam, printStruct prints);
int darDeBajaAlumno();
void mainMenu();

#endif // MAIN_H_INCLUDED
