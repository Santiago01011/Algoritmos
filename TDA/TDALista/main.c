#include "main.h"

void genArhivoAlumnos(){
    FILE *arch = fopen("../archTests/alumnos.dat", "wb");
    if(arch == NULL)
        return;
    Alumno a[]={ {1, "Juan", "Perez", 20, 8.5},
                  {2, "Maria", "Gomez", 22, 7.5},
                  {3, "Carlos", "Lopez", 21, 6.5},
                  {4, "Ana", "Rodriguez", 23, 9.5},
                  {5, "Pedro", "Garcia", 24, 7.0},
                  {6, "Laura", "Fernandez", 25, 8.0},
                  {7, "Diego", "Martinez", 26, 6.0},
                  {8, "Silvia", "Alvarez", 27, 9.0},
                  {9, "Jorge", "Diaz", 28, 5.5},
                  {10, "Marta", "Torres", 29, 10.0},
                  {11, "Raul", "Suarez", 30, 4.5},
                  {12, "Elena", "Ramirez", 31, 9.8},
                  {13, "Oscar", "Benitez", 32, 9.8},
                  {14, "Luis", "Paz", 33, 6.8},
                  {15, "Cecilia", "Vega", 34, 8.8},
                  {16, "Fernando", "Rios", 35, 5.8},
                  {17, "Gabriela", "Sosa", 36, 9.8},
                  {18, "Hugo", "Molina", 37, 7.2},
                  {19, "Adriana", "Luna", 38, 6.2},
                  {20, "Ricardo", "Aguirre", 39, 8.2} };
    fwrite(a, sizeof(Alumno), 20, arch);
    fclose(arch);
}

void printAlumno(const void *a){
    Alumno *al = (Alumno *)a;
    printf("Legajo: %d | Apellido y Nombre: %s, %s | Edad: %d | Promedio: %.2f\n", al->legajo, al->apellido, al->nombre, al->edad, al->promedio);
}

int cmpPromedio(const void* a, const void* b){
    float diff = ((Alumno*)b)->promedio - ((Alumno*)a)->promedio;
    return diff > 0 ? 1 : diff < 0 ? -1 : 0;
}


int main(){
    genArhivoAlumnos();
    tLista listaAlums, listaTop10, podio;
    crearLista(&listaAlums);
    crearLista(&listaTop10);
    crearLista(&podio);
    int *contTop = 0, contPodio = 1;
    unsigned tam = sizeof(Alumno);
    void *contextoTop10[] = {&listaTop10, &contTop, cmpPromedio, &tam};
    //void *contextoPodio[] = {&contPodio, printAlumno, cmpPromedio};

    cargarEnListaArch("../archTests/alumnos.dat", &listaAlums, sizeof(Alumno));
    puts("Lista de alumnos sin ordenar:");
    map(&listaAlums, imprimirLista, printAlumno);
    puts("-------------------------------------------");
    ordenarListaQuickSort(&listaAlums, cmpPromedio);
    puts("Lista de alumnos ordenada por promedio:");
    map(&listaAlums, imprimirLista, printAlumno);
    puts("-------------------------------------------");
    puts("Lista de Top 10 alumnos por promedio:");
    map(&listaAlums, mapTop10, contextoTop10);
    map(&listaTop10, imprimirLista, printAlumno);
    puts("-------------------------------------------");
    puts("Podio de alumnos por promedio:");
    insertarEnPodio(&podio, &listaTop10, cmpPromedio);
    //map(&podio, printPodio, contextoPodio);
    mostrarPodio(&podio, cmpPromedio, printAlumno);


    return 0;
}