#include "main.h"
// Dado un archivo binario “impuestosVencidos.dat” que contiene todas las cuotas vencidas de las
// patentes de una localidad determinada (este archivo no tiene ningún tipo de orden):
// La estructura de cada registro es:
// • patente: cada patente tiene el formato AB123CD
// • nroCuota: número entero de 1 a 6
// • titular: apellido y nombre (25 caracteres)
// • dni: número entero entre 1.000.000 y 99.999.999
// • vto: fecha de vencimiento aaaa/mm/dd (año, mes, día)
// • importe: importe máximo 99.999,99

void generarArchivo(){
    FILE *arch = fopen(RUTARCH, "wb");
    if(!arch){
        printf("Error al abrir el archivo");
        return;
    }
    tImpuesto imp[] = {
    {"AB123CD", 1, "Perez Juan", 40123456, {2023, 11, 23}, 1000.0},
    {"CD456EF", 2, "Gomez Maria", 41234567, {2023, 11, 24}, 2000.0},
    {"EF789GH", 3, "Gonzalez Pedro", 42345678, {2023, 11, 25}, 3000.0},
    {"GH012IJ", 4, "Rodriguez Ana", 43456789, {2023, 11, 26}, 4000.0},
    {"IJ345KL", 5, "Fernandez Juan", 49234567, {2023, 11, 27}, 5000.0},
    {"KL678MN", 6, "Lopez Maria", 46789012, {2023, 11, 28}, 6000.0},
    {"MN901OP", 7, "Manez Adeline", 45678901, {2023, 11, 29}, 1000.0},
    {"OP234QR", 8, "Aramburu José", 49123456, {2023, 11, 30}, 2000.0},
    {"QR567ST", 9, "Fernandez Pablo", 44525943, {2023, 11, 1}, 3000.0},
    {"ST890UV", 10, "Mouche Pablo", 12122012, {2024, 11, 2}, 4000.0},
    {"UV123WX", 11, "Palermo Juan Martin", 26062011, {2023, 12, 3}, 5000.0},
    {"WX456YZ", 12, "Jesus Maria", 49012345, {2023, 12, 4}, 6000.0},
    {"XLR8ZZZ", 7, "Mouche Pablo", 12122012, {2021, 9, 9}, 6000.0},
    {"UV123WX", 10, "Palermo Juan Martin", 26062011, {2023, 11, 3}, 6000.0}
};
    fwrite(imp, sizeof(tImpuesto), sizeof(imp)/sizeof(tImpuesto), arch);
    fclose(arch);
}

int main()
{
    generarArchivo();
    mostrarMenu();

    return 0;
}
