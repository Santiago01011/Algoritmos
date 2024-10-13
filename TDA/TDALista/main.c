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
//         {125, 1, 1}, // Unión por Todos y Para Todos
//         {125, 1, 1}, // Unión por Todos y Para Todos
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

void printResultado(const void *r){
    Resultado *res = (Resultado *)r;
    printf("|Agrupacion: %s|", res->nagrup);
    printf("Distrito: %d|", res->distri);
    printf("Votos Distrito: %d|", res->votosD);
    printf("Total Votos: %d|\n", res->totalVotos);
    puts("----------------------------");
}

int main(){
    //generarArch();
    int cantAgrup = 0;
    int pos, top = 0;
    Agrupacion agrupaciones[MAX_AGRUP];
    Resultado auxRes;
    tLista podioAgrup;
    crearLista(&podioAgrup);
    int votosDistritos[MAX_AGRUP][MAX_DISTRI] = {0};
    if(!(cantAgrup = leerAgrup(agrupaciones))){
        puts("Error al leer las agrupaciones");
        return 1;
    }
    qsort(agrupaciones, cantAgrup, sizeof(Agrupacion), cmpAgru);
    leerVotos(votosDistritos, agrupaciones, cantAgrup);
    //podioAux apunta al principio de la lista, voy a usar el puntero para moverme por el top
    tLista *podioAux = &podioAgrup;
    for(int j = 0; j < MAX_DISTRI; j++){
        top = 0;
        for(int i = 0; i < cantAgrup; i++){
            auxRes.distri = j + 1;
            auxRes.votosD = votosDistritos[i][j];
            strcpy(auxRes.nagrup, agrupaciones[i].nombre);
            auxRes.totalVotos = 0;
            if(auxRes.votosD > 0)
                insertarEnPodioU(podioAux, &auxRes, sizeof(Resultado), cmpRes, &top);
        }
        while(*podioAux){
            podioAux = &(*podioAux)->sig;
        }

    }


    puts("Podios por distrito:");
    mostrarPodioDist(&podioAgrup, cmpRes, printResultado);
    vaciarLista(&podioAgrup);


    // for (int i = 0; i < cantAgrup; i++){
        
    //     if(buscarBin(&agrupaciones, &agrupaciones[i], cmpAgru, &pos, cantAgrup, sizeof(Agrupacion))){ 
    //         printf("Encontrado en la posicion %d\n", pos);
    //         printAgrupacion(&agrupaciones[pos]);
    //     }
    // }

    
    return 0;
}


    // for(int i = 0; i < MAX_DISTRI; i++){
    //     for(int j = 0; j < cantAgrup; j++){
    //         auxRes.distri = i+1;
    //         auxRes.votosD = votosDistritos[j][i];
    //         strcpy(auxRes.nagrup, agrupaciones[j].nombre);
    //         auxRes.totalVotos = 0;
    //         insertar_en_podio(&podioAgrup, &auxRes, sizeof(Resultado), cmpRes);
    //     }
    // }