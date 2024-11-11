#include "main.h"

tFecha ingresarFechaAct(){
    printf("Ingresar fecha actual: ");
    tFecha fecha;
    puts("Ingrese el anio: ");
    scanf("%d", &fecha.anio);
    puts("Ingrese el mes: ");
    scanf("%d", &fecha.mes);
    puts("Ingrese el dia: ");
    scanf("%d", &fecha.dia);
    return fecha;
}

void printImpuesto(const void *imp){
    printf("|Patente: %s|Nro Cuota: %d|Titular: %s|DNI: %d|Vto: %d/%d/%d|Importe: %.2f|\n",
           ((tImpuesto*)imp)->patente, ((tImpuesto*)imp)->nroCuota, ((tImpuesto*)imp)->titular,
           ((tImpuesto*)imp)->dni, ((tImpuesto*)imp)->vto.anio, ((tImpuesto*)imp)->vto.mes,
           ((tImpuesto*)imp)->vto.dia, ((tImpuesto*)imp)->importe);
}


void fprintImpuestoDniPatente(const void *imp, FILE* pf){
    fprintf(pf,"|Patente: %s|Nro Cuota: %d|Titular: %s|DNI: %d|Vto: %d/%d/%d|Importe: %.2f|\n",
           ((tImpuesto*)imp)->patente, ((tImpuesto*)imp)->nroCuota, ((tImpuesto*)imp)->titular,
           ((tImpuesto*)imp)->dni, ((tImpuesto*)imp)->vto.anio, ((tImpuesto*)imp)->vto.mes,
           ((tImpuesto*)imp)->vto.dia, ((tImpuesto*)imp)->importe);
}

void fprintImpuestoDni(const void *imp, FILE* pf){
    fprintf(pf,"|DNI: %d|Titular: %s|Importe Total: %.2f|\n", ((tImpuesto*)imp)->dni, ((tImpuesto*)imp)->titular, ((tImpuesto*)imp)->importe);
}

int cmpDni(const void *a, const void *b){
    return ((tImpuesto*)a)->dni - ((tImpuesto*)b)->dni;
}

int mostrarArchGen(const char *ruta, size_t tam, printStruct prints){
    FILE* arch = fopen(ruta, "rb");
    if(!arch)   return 0;
    void* buffer = malloc(tam);
    if(!buffer){
        fclose(arch);
        return 0;
    }
    printf("Leyendo archivo: %s\n", ruta);
    while(fread(buffer, tam, 1, arch)){
        prints(buffer);
    }
    puts("Fin de archivo");
    free(buffer);
    fclose(arch);
    return 1;
}

void generarDeudaTXT(const char *ruta, tLista *p , void fprints(const void*, FILE*)){
    FILE *fp = fopen(ruta, "wt");
    if(!fp) return;
    for(tNodo *i = *p; i; i = i->sig){
        fprints(i->info, fp);
    }
    fclose(fp);
}

void actualizarImporte(void* d, void* param){
    tImpuesto* imp = (tImpuesto*)d;
    tImpuesto* aux = (tImpuesto*)param;
    imp->importe += aux->importe;
}

void imprimirLista(void* d, void* param){
    printStruct prints = (printStruct)param;
    prints(d);
}

