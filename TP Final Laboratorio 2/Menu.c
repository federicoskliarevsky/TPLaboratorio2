#include "Menu.h"

void ejecutarMenu (){
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
            menuAdministrador();
            break;
        case 2:
            menuUsuario();
            break;
        default:
            printf("\nGracias por haber usado el Simulador de Mercado de FIFA 20. Nos vemos pronto!");
    }
}
