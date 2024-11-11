#include "main.h"


int cmpDniIdx(const void *a, const void *b){
    return ((Idx*)a)->dni - ((Idx*)b)->dni;
}
void generarArch(){
    FILE *f = fopen("alumnos.dat", "wb");
    tAlumno alu[] = {
        {"Perez Juan", 40123456, 'A'},
        {"Gomez Maria", 41234567, 'A'},
        {"Gonzalez Pedro", 42345678, 'A'},
        {"Rodriguez Ana", 43456789, 'A'},
        {"Fernandez Juan", 49234567, 'A'},
        {"Lopez Maria", 46789012, 'A'},
        {"Manez Adeline", 45678901, 'A'},
        {"Aramburu Jose", 49123456, 'A'},
        {"Fernandez Pablo", 44525943, 'A'},
        {"Mouche Pablo", 12122012, 'A'},
        {"Palermo Juan Martin", 26062011, 'A'},
        {"Jesus Maria", 49012345, 'A'},
        {"Martinez Carlos", 40123457, 'A'},
        {"Sanchez Laura", 41234568, 'A'},
        {"Ramirez Luis", 42345679, 'A'},
        {"Torres Sofia", 43456780, 'A'},
        {"Diaz Miguel", 49234568, 'A'},
        {"Suarez Camila", 46789013, 'A'},
        {"Morales Diego", 45678902, 'A'},
        {"Rojas Valeria", 49123457, 'A'},
        {"Gutierrez Javier", 44525944, 'A'},
        {"Blanco Lucia", 12122013, 'A'},
        {"Castro Andres", 26062012, 'A'},
        {"Vega Natalia", 49012346, 'A'},
        {"Alvarez Tomas", 40123458, 'A'},
        {"Benitez Clara", 41234569, 'A'},
        {"Cabrera Lucas", 42345680, 'A'},
        {"Dominguez Sofia", 43456781, 'A'},
        {"Espinoza Mateo", 49234569, 'A'},
        {"Flores Valentina", 46789014, 'A'},
        {"Garcia Martin", 45678903, 'A'},
        {"Hernandez Paula", 49123458, 'A'},
        {"Iglesias Juan", 44525945, 'A'},
        {"Jimenez Maria", 12122014, 'A'},
        {"Krause Andres", 26062013, 'A'},
        {"Luna Natalia", 49012347, 'A'}
    };
    if(!f){
        printf("Error al abrir el archivo\n");
        return;
    }
    fwrite(alu, sizeof(tAlumno), sizeof(alu)/sizeof(tAlumno), f);
    fclose(f);
    FILE *f2 = fopen("alumnos.idx", "wb");

    Idx idx[sizeof(alu) / sizeof(tAlumno)];
    for (int i = 0; i < sizeof(alu) / sizeof(tAlumno); i++) {
        idx[i].reg= i;
        idx[i].dni = alu[i].dni;
    }

    // Ordenar el índice por dni
    qsort(idx, sizeof(idx) / sizeof(Idx), sizeof(Idx), cmpDniIdx);

    if (!f2) {
        printf("Error al abrir el archivo\n");
        return;
    }
    fwrite(idx, sizeof(Idx), sizeof(idx) / sizeof(Idx), f2);
    fclose(f2);
}


int main()
{
    generarArch();
    mostrarArchGen("alumnos.dat", sizeof(tAlumno), printAlumno);
    mostrarArchGen("alumnos.idx", sizeof(Idx), printIdx);
    system("pause");
    mainMenu();
    return 0;
}
