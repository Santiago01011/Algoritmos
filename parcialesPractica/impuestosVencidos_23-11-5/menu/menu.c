#include "menu.h"
#include "../main.h"


char menuConErr(const char *msg, const char *opc){
    char opta;
    int flag = 1;
    do{
        printf("%s%s",
        flag ? flag = 0, "" : "ERROR - Opcion NO valida. Reingrese.\n",
        msg);
        fflush(stdin);
        scanf(" %c", &opta);
    }while(strchr(opc, opta) == NULL);
    return opta;
}

void mostrarMenu(void){
    tFecha fechaAct = ingresarFechaAct();
    tLista lista;
    crearLista(&lista);


    char opc;
    do{
        system("cls");
        printf("Fecha actual: %d/%d/%d\n", fechaAct.anio, fechaAct.mes, fechaAct.dia);
        opc = menuConErr("Elija una opcion:\n"
                        "A. Mostrar archivo impuestosVencidos.dat\n"
                        "B. Generar deuda.txt por dni y patente\n"
                        "C. Generar deuda.txt por dni\n"
                        "D. Salir\n", "ABCDabcdy");
        opc = toupper(opc);
        switch(opc){
            case 'A': printf("Opcion A\n"); mostrarArchGen(RUTARCH, sizeof(tImpuesto), printImpuesto); system("pause"); break;
            case 'B': printf("Opcion B\n"); generarDeudaTXT(RUTATXT, &lista, fprintImpuestoDniPatente); system("pause"); break;
            case 'C': printf("Opcion C\n"); cargarEnListaArch(RUTARCH, &lista, sizeof(tImpuesto), cmpDni, actualizarImporte); generarDeudaTXT(RUTATXT, &lista, fprintImpuestoDni); system("pause"); break;
            case 'D': printf("Saliendo..."); break;
        }
    }while(opc != 'D');
}


