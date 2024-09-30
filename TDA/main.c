#include "main.h"

void agregarArhivoProductos(){
    FILE *arch = fopen("archTests/productos.dat", "wb");
    if(arch == NULL)
        return;
    Producto p[] = {
        {1, "Espinaca", 130, 180.00},
        {2, "Lechuga", 100, 100.00},
        {3, "Tomate", 200, 200.00},
        {22, "Papa", 150, 100.00},
        {5, "Zanahoria", 120, 80.00},
        {6, "Cebolla", 100, 50.00},
        {15, "Ajo", 50, 30.00},
        {8, "Pimiento", 80, 70.00},
        {16, "Pepino", 70, 60.00},
        {10, "Calabaza", 90, 40.00},
        {0, "Higo", 160, 100.00},
        {4, "Banana", 170, 100.00},
        {7, "Pera", 80, 50.00},
        {9, "Manzana", 270, 70.00},
        {14, "Durazno", 340, 90.00}
    };
    fwrite(p, sizeof(Producto), sizeof(p)/sizeof(Producto), arch);
    fclose(arch);
}

int main(){
    //agregarArhivoProductos();
    tLista lista;
    crearLista(&lista);
    tLista podio;
    crearLista(&podio);
    tLista top10;
    crearLista(&top10);
    int cantTop = 0;

    cargarEnListaArch("archTests/productos.dat", &lista, sizeof(Producto));
    puts("Lista de productos:");
    for(tNodo *i = lista; i; i = i->sig)
        printProducto(i->info);
    puts("-------------------------------------------------");
    ordenarListaInsercion(&lista, cmpIntDesc);
    puts("Lista de productos ordenada por codigo:");
    for(tNodo *i = lista; i; i = i->sig)
        printProducto(i->info);
    puts("-------------------------------------------------");
    for(tNodo *i = lista; i; i = i->sig){
        insertarTop10(&top10, cantTop, i->info, sizeof(Producto), cmpPrecio);
        cantTop++;
        }
    puts("Top 10 de productos:");
    for(tNodo *i = top10; i; i = i->sig)
        printProducto(i->info);
    puts("-------------------------------------------------");
    ordenarListaInsercion(&lista, cmpPrecio);
    insertarEnPodio(&podio, &lista, cmpPrecio);
    mostrarPodio(&podio, cmpPrecio, printProducto);
    puts("-------------------------------------------------");


    
    return 0;
}