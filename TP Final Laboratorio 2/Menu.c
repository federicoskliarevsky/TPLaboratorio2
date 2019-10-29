#include "Menu.h"

void imprimirCabecera()
{
    system("COLOR 02");
    char cabecera[] = "FIFA 20";
    int i;
    printf("%c", 201);
    for(i=0; i<50; i++)
    {
        printf("%c",205);
    }
    printf("%c\n", 187);
    printf("%c%32s%19c\n", 186,cabecera,186);
    printf("%c", 200);
    for(i=0; i<50; i++)
    {
        printf("%c",205);
    }
    printf("%c", 188);
    printf("\n");
    system("pause");
    system("cls");
    crearVariables();
}
void crearVariables(){
    nodoLiga * listaLigas = inicListaliga();
    listaLigas = cargarListaLigas(listaLigas);
    ejecutarMenu(listaLigas);
}
void ejecutarMenu (nodoLiga * listaLigas){
    int opcion=-1;
    printf ("Bienvenido al Simulador de Mercado de FIFA 20!\n A continuacion, debera elegir una opcion:");
    printf ("\n  1. Para ingresar como administrador.");
    printf ("\n  2. Para ingresar como usuario");
    printf ("\n  0. Para salir.");
    printf ("\n\n Ingrese la opcion deseada: ");
    fflush (stdin);
    scanf ("%d", &opcion);
    while (opcion<0 || opcion>2){
        printf ("\nSe ingreso una opcion incorrecta. Por favor, ingrese una opcion valida: ");
        fflush (stdin);
        scanf ("%d", &opcion);
    }
    switch (opcion){
        case 1:
            menuAdministrador(listaLigas);
            break;
        case 2:
            menuUsuario(listaLigas);
            break;
        default:
            printf("\nGracias por haber usado el Simulador de Mercado de FIFA 20. Nos vemos pronto!");
    }
}
