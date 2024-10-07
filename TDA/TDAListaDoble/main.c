#include "main.h"

void printInt(void *d){
    printf("%d\n", *(int *)d);
}

int main(){

    tLista lista;
    createDoubleList(&lista);
    int a[] = {8, 3, 1, 4, 1}, x = 0;
    for(int i = 0; i < 5; i++){
        addAtEndDoubleList(&lista, &a[i], sizeof(int));
    }

    addAtBeginningDoubleList(&lista, &a[1], sizeof(int));
    if(addInOrderDoubleList(&lista, &x, sizeof(int), cmpInt, NULL) == DUPKEY)
        puts("Clave duplicada");
    else
        puts("Clave insertada");

    puts("Lista sin ordenar:");
    mapDoubleList(&lista, imprimirLista, printInt);
    
    sortDoubleList(&lista, cmpInt);

    puts("Lista ordenada:");
    mapDoubleList(&lista, imprimirLista, printInt);


    return 0;
}