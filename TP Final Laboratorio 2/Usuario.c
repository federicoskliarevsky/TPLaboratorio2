#include "Usuario.h"

void menuUsuario(nodoLiga * listaLigas){
    int opcion=-1;
    system("cls");
    printf ("Bienvenido, Usuario!\n Que desea hacer?");
    printf ("\n  1. Listado de jugadores.");
    printf ("\n  2. Ir a Mi Club");
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
            printf ("\n Listado de jugadores.\n");
            system ("pause");
            ///menuListarTodos();
            system("cls");
            ejecutarMenu(listaLigas);
            break;
        case 2:
            printf ("\n Menu Mi Club\n");
            system ("pause");
            ///menuMiClub();
            system("cls");
            ejecutarMenu(listaLigas);
            break;
        default:
            system("cls");
            ejecutarMenu(listaLigas);
    }
}
