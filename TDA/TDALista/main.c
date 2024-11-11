#include "main.h"

// Ejercicio 1:
// Dado un archivo binario “lote.dat” cuyos registros, no están ordenados y tienen la siguiente estructura:
// • Provincia: 99 (dos dígitos – 23 provincias numeradas del 01 al 23)
// • Localidad: xxx...x (50 caracteres)
// • Superficie: 99999.99 (kilómetros cuadrados)
// • Población: 9999 (habitantes)
// Se pide:
// Desarrollar una aplicación que informe las 5 localidades con mayor superficie.

// El proceso debe trabajar de forma óptima, manipulando las estructuras de datos la menor cantidad de ve-
// ces posible y utilizando la menor cantidad de memoria posible.

// Al finalizar el proceso no debe quedar nada en memoria.

void generarArch(){
    FILE *arch = fopen("../archTests/lote.dat", "wb");
    if(!arch){
        puts("Error al abrir el archivo");
        return;
    }
    Lote v[] = {
        {1, "Yerba Buena", 500.0, 5000},
        {3, "Tafi Viejo", 300.0, 3000},
        {5, "Banda del Rio Sali", 200.0, 2000},
        {12, "Aguilares", 100.0, 1000},
        {12, "Famailla", 50.0, 500},
        {12, "Lules", 30.0, 300},
        {21, "Monteros", 20.0, 200},
        {6, "Rafaela", 156.6, 110709},
        {6, "Sunchales", 100.0, 10000},
        {6, "Esperanza", 50.0, 5000},
        {12, "San Miguel de Tucuman", 1000.0, 10000},
        {6, "San Cristobal", 30.0, 3000},
        {6, "San Guillermo", 20.0, 2000},
        {6, "San Vicente", 10.0, 1000},
        {6, "San Justo", 5.0, 500},
        {6, "San Javier", 3.0, 300}       
    };
    fwrite(v, sizeof(Lote), sizeof(v)/sizeof(Lote), arch);
    fclose(arch);
}

void printLote(const void *l){
    Lote *lote = (Lote *)l;
    printf("|Provincia: %d|Localidad: %s|Superficie: %.2f|Poblacion: %d|\n", lote->numProv, lote->loc, lote->sup, lote->pob);
}

int cmpSup(const void *a, const void *b){
    Lote *l1 = (Lote *)a;
    Lote *l2 = (Lote *)b;
    if(l1->sup > l2->sup)
        return -1;
    if(l1->sup < l2->sup)
        return 1;
    return 0;
}
int main(){
    generarArch();
    int top = 0;
    // mostrarArchivoGen("../archTests/lote.dat", sizeof(Lote), printLote);
    tLista lista, top5;
    crearLista(&lista);
    crearLista(&top5);
    if(cargarEnListaArch("../archTests/lote.dat", &lista, sizeof(Lote))!=1){
        puts("Error al cargar el archivo");
        return 1;
    }
    puts("Lista:");
    map(&lista, imprimirLista, printLote);
    puts("Top 5:");
    for(tNodo *i = lista; i; i = i->sig) {
        insertarTop5V2(&top5, &top, i->info, i->tamInfo, cmpSup);
    }
    map(&top5, imprimirLista, printLote);

    vaciarLista(&lista);
    vaciarLista(&top5);    
    return 0;
}
