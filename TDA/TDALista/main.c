#include "main.h"

// Se dispone de un archivo de texto con el número y el nombre de cada agrupación que se presenta en
// las elecciones para elegir los congresales de una asociación civil sin fines de lucro; y además de un
// archivo binario en el que se almacenó el número de agrupación, de distrito y de región (un registro
// por caxda voto electrónico emitido).
// Se requiere un proceso que a partir de la lectura de ambos archivos almacene en arrays
// bidimensionales los nombres de las agrupaciones y el total de votos obtenidos por distrito.
// A partir de los arrays, genere una lista (con inserción en orden), a fin de poder mostrar, al final del
// proceso, los nombres de las tres agrupaciones que obtienen mayor cantidad de votos para cada
// distrito.
// En todo momento en la lista sólo deben quedar a lo sumo las tres agrupaciones ganadoras para cada
// distrito, con nombre de agrupación (sólo los primeros 25 caracteres para el ordenamiento alfabético)
// y los votos obtenidos por la agrupación en qué distrito y el total de votos obtenidos en el país.

//ejemplo del archivo de texto:
// 1028Celeste y Blanca
// 4Verde
// 125Unión por Todos y Para Todos
// 3Frente para la Victoria
// 8Frente Renovador
// 2Liga Federal

// void generarArch(){
//     FILE *arch = fopen("../archTests/votos.dat", "ab");
//     if(!arch){
//         puts("Error al abrir el archivo");
//         return;
//     }
//     Voto v[] = {
//         {2, 6, 10},   // Liga Federal
//         {1028, 1, 10}, // Celeste y Blanca
//         {4, 2, 10},   // Verde
//         {125, 3, 10}, // Unión por Todos y Para Todos
//         {4, 2, 10},   // Verde
//         {4, 2, 10},   // Verde
//         {3, 4, 10},   // Frente para la Victoria
//         {8, 5, 10},   // Frente Renovador
//         {8, 5, 10},   // Frente Renovador
//         {8, 5, 10},   // Frente Renovador
//         {2, 6, 10},   // Liga Federal
//         {2, 6, 10},   // Liga Federal
//         {2, 6, 10},   // Liga Federal
//         {1028, 1, 10}, // Celeste y Blanca
//         {4, 2, 10},   // Verde
//         {125, 3, 10}, // Unión por Todos y Para Todos
//         {3, 4, 10},   // Frente para la Victoria
//     };
//     fwrite(v, sizeof(Voto), sizeof(v)/sizeof(Voto), arch);
//     fclose(arch);
// }



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
    int cantAgrup = 0;
    int pos;
    Agrupacion agrupaciones[MAX_AGRUP];
    tLista podioAgrup;
    crearLista(&podioAgrup);
    int votosDistritos[MAX_AGRUP][MAX_DISTRI] = {0};
    if(!(cantAgrup = leerAgrup(agrupaciones))){
        puts("Error al leer las agrupaciones");
        return 1;
    }
    qsort(agrupaciones, cantAgrup, sizeof(Agrupacion), cmpAgru);
    leerVotos(votosDistritos, agrupaciones, cantAgrup);


    // for (int i = 0; i < cantAgrup; i++){
        
    //     if(buscarBin(&agrupaciones, &agrupaciones[i], cmpAgru, &pos, cantAgrup, sizeof(Agrupacion))){ 
    //         printf("Encontrado en la posicion %d\n", pos);
    //         printAgrupacion(&agrupaciones[pos]);
    //     }
    // }

    
    return 0;
}

