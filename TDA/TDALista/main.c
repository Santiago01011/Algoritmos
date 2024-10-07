#include "main.h"

// Se dispone de un archivo de texto con el número y el nombre de cada agrupación que se presenta en
// las elecciones para elegir los congresales de una asociación civil sin fines de lucro; y además de un
// archivo binario en el que se almacenó el número de agrupación, de distrito y de región (un registro
// por cada voto electrónico emitido).
// Se requiere un proceso que a partir de la lectura de ambos archivos almacene en arrays
// bidimensionales los nombres de las agrupaciones y el total de votos obtenidos por distrito.
// A partir de los arrays, genere una lista (con inserción en orden), a fin de poder mostrar, al final del
// proceso, los nombres de las tres agrupaciones que obtienen mayor cantidad de votos para cada
// distrito.

//ejemplo del archivo de texto:
// 1028Celeste y Blanca
// 4Verde
// 125Unión por Todos y Para Todos
// 3Frente para la Victoria
// 8Frente Renovador
// 2Liga Federal

void generarArch(){
    FILE *arch = fopen("../archTests/votos.dat", "wb");
    if(!arch){
        puts("Error al abrir el archivo");
        return;
    }
    Voto v[] = {
        {1028, 1, 15}, // Celeste y Blanca
        {4, 2, 0},    // Verde
        {125, 3, 3},  // Unión por Todos y Para Todos
        {3, 4, 5},    // Frente para la Victoria
        {8, 5, 0},    // Frente Renovador
        {2, 6, 0},    // Liga Federal
        {1028, 1, 11}, // Celeste y Blanca
        {4, 2, 0},    // Verde
        {125, 3, 16},  // Unión por Todos y Para Todos
        {3, 4, 8},    // Frente para la Victoria
        {8, 5, 7},    // Frente Renovador
        {2, 6, 0},    // Liga Federal
        {1028, 1, 0}, // Celeste y Blanca
        {4, 2, 3},    // Verde
        {125, 3, 9},  // Unión por Todos y Para Todos
        {3, 4, 0},    // Frente para la Victoria
        {8, 5, 1},    // Frente Renovador
        {2, 6, 0},    // Liga Federal
        {1028, 1, 2}, // Celeste y Blanca
        {4, 2, 0},    // Verde
    };
    fwrite(v, sizeof(Voto), sizeof(v)/sizeof(Voto), arch);
    fclose(arch);
}

void printVoto(const void *v){
    Voto *voto = (Voto *)v;
    printf("|Agrupacion: %d|", voto->nagrup);
    printf("Region: %d|", voto->region);
    printf("Distrito: %d|\n", voto->distri);
    puts("----------------------------");
}

void printAgrupacion(const void *a){
    Agrupacion *agr = (Agrupacion *)a;
    printf("|Numero: %d|", agr->numero);
    printf("Nombre: %s|\n", agr->nombre);
    puts("----------------------------");
}

int main(){
    //generarArch();
    mostrarArchivoGen("../archTests/votos.dat", sizeof(Voto), printVoto);
    txtABin_ALU("../archTests/agrupaciones.txt", "../archTests/agrupaciones.dat", sizeof(Agrupacion), convertirRegla);
    mostrarArchivoGen("../archTests/agrupaciones.dat", sizeof(Agrupacion), printAgrupacion);
    return 0;
}