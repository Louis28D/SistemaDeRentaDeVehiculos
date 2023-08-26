/*----------------------------------------------------------------
|  Autor:   kenedy ventura/ luis angel                            Matricula: 1162939/
                                                                     1-20-1949   |
|  Fecha: 15/8/2023                              Versi?n: 0.4		           |
|-----------------------------------------------------------------            |
|  Descripci?n del Programa:  reenta de vehiculos                            |
|                                                                            |
| ----------------------------------------------------------------*/



#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
                                //deeclaro la eestructura 
typedef struct {
    int codigo;
    char descripcion[41];
    float precio;
} tproducto;


void continuar()
{
    printf("Presione una tecla para continuar\n\n");
    getch();
}

void crear()                 // funcion para crear archivo
{
    FILE *arch;              //declaracion  de puntero
    arch=fopen("inventario.txt","w");
    if (arch==NULL)
        exit(1);
    fclose(arch);
    continuar();
}


void cargar()             //funcion para ingresar vehioculos al archivo
{
    FILE *arch;
    arch=fopen("inventario.txt","a");  //abrir el archivo con a
    if (arch==NULL)
        exit(1);
    tproducto producto;       //crear una variable local para la estructura
    printf("Ingrese el codigo del vehiculo:");
    scanf("%i",&producto.codigo);
    fflush(stdin);                // limpiar la informacion del teclado
    printf("Ingrese el nombre del vehiculo:");
    gets(producto.descripcion);
    printf("Ingrese el precio:");
    scanf("%f",&producto.precio);
    fwrite(&producto, sizeof(tproducto), 1, arch); //escribir  la direccion de producto con el tamaño de la estructura
    fclose(arch);
    continuar();
}



void consulta() // funcion para visulizar por codigo
{
    FILE *arch;
    arch=fopen("inventario.txt","r");
    if (arch==NULL)
        exit(1);
    printf("Ingrese el codigo del veehiculo a consultar:");
    int cod; // variable entera para poder comparar el codigo almacenado con el codigo en el teclado
    scanf("%i", &cod);
    tproducto producto;
    int existe=0;
    fread(&producto, sizeof(tproducto), 1, arch);
    while(!feof(arch))
    {
        if (cod==producto.codigo)
        {
           printf("%i %s %0.2f\n", producto.codigo, producto.descripcion, producto.precio);
           existe=1;
           break;
        }
        fread(&producto, sizeof(tproducto), 1, arch);
    }
    if (existe==0)
        printf("No existe un vehiculo con dicho codigo\n");
    fclose(arch);
    continuar();
}


void listado() // funcion para visualizar eel inventario de vehiculos
{
    FILE *arch;
    arch=fopen("inventario.txt","r");
    if (arch==NULL)
        exit(1);
    tproducto producto;
    fread(&producto, sizeof(tproducto), 1, arch);
    while(!feof(arch))
    {
        printf("%i %s %0.2f\n", producto.codigo, producto.descripcion, producto.precio);
        fread(&producto, sizeof(tproducto), 1, arch);
    }
    fclose(arch);
    continuar();
}

void modificacion()  /// funcion para modificar el precio de un vehiculo
{
    FILE *arch;
    arch=fopen("inventario.txt","r+");
    if (arch==NULL)
        exit(1);
    printf("Ingrese el codigo de vehiculo a modificar:");
    int cod;            // variable entera para poder comparar el codigo almacenado con el codigo en el teclado
    scanf("%i", &cod);
    tproducto producto;
    int existe=0;
    fread(&producto, sizeof(tproducto), 1, arch);
    while(!feof(arch))
    {
        if (cod==producto.codigo)
        {
           printf("%i %s %0.2f\n", producto.codigo, producto.descripcion, producto.precio);
           printf("Ingrese nuevo precio:");
           scanf("%f",&producto.precio);
           int pos=ftell(arch)-sizeof(tproducto);  //se le resta a la pocision del puntero el nuevo valor en el registro para poder almacenar el nuevo precio
           fseek(arch,pos,SEEK_SET);
           fwrite(&producto, sizeof(tproducto), 1, arch);
           printf("Se modifico el precio para el vehiculo.\n");
           existe=1;
           break;
        }
        fread(&producto, sizeof(tproducto), 1, arch);
    }
    if (existe==0)
        printf("No existe un vehiculo con dicho codigo\n");
    fclose(arch);
    continuar();
}

int main()
{
    int opcion;
    do {                                                         //menu selecion switch con todas las opciones disponibles para usar 
        printf("1 - Crear un archivo  \"inventario.txt\"\n");
        printf("2 - agregar vehiculos al de registros \n");
        printf("3 - Listado completo de vehiculos.\n");
        printf("4 - Consulta de un vehiculo por su codigo.\n");
        printf("5 - Modificacion del precio de un vehiculo. \n");
        printf("6 - Finalizar\n\n");
        printf("Ingrese su opcion:");
        scanf("%i",&opcion);
        switch (opcion) {
            case 1:crear();
                   break;
            case 2:cargar();
                   break;
            case 3:listado();
                   break;
            case 4:consulta();
                   break;
            case 5:modificacion();
                   break;
        }
    } while (opcion!=6);
    return 0;
}
