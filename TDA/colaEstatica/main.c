#include "main.h"


void crearArchivos(){
    FILE *f = fopen("cuentas.dat", "wb");
    if(f == NULL)
        return;
    Cuenta cuentas [] = {
        {1, 300, 1},
        {1, 3900, 2},
        {1, 800, 3},
        {2, 4000, 4},
        {3, 5000, 5},
        {5, 6000, 5},
        {5, 7000, 8},
        {6, 8000, 7},
        {7, 9000, 10},
        {8, 10000, 9}
    };
    fwrite(cuentas, sizeof(Cuenta), 10, f);
    fclose(f);
}


int main(){

    tCola cola;
    Cuenta c, anterior, acum;
    crearCola(&cola);
    crearArchivos();
    //dame un codigo que me ayude a probar si las funciones de cola estan bien
    FILE *f = fopen("cuentas.dat", "rb");
    FILE *arch = fopen("cuentasAcum.dat", "wb");
    if(f == NULL)
        return 1;
    
    while(fread(&c, sizeof(Cuenta), 1, f) == 1){
        ponerEnCola(&cola, &c, sizeof(Cuenta));
    }
    fclose(f);
    while(!colaVacia(&cola)){
        sacarDeCola(&cola, &c, sizeof(Cuenta));
        printf("Cuenta: %d\n", c.nroCuenta);
        anterior = c;
        do{
            //printf("Cuenta: %d\n", c.nroCuenta);
            sacarDeCola(&cola, &c, sizeof(Cuenta));
            printf("Cuenta: %d\n", c.nroCuenta);

            
            //guardar en un archivo los movimientos de la cuenta

        }while(c.nroCuenta == anterior.nroCuenta && !colaVacia(&cola));
    }
   

    vaciarCola(&cola);
    return 0;
}

