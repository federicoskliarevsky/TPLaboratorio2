#include "Administrador.h"

void ingresoAdmin (){
    int opcion=-1;
    system("cls");
    printf ("Bienvenido, Administrador.\n A continuacion, debera elegir una opcion:");
    printf ("\n  1. Para modificar un jugador.");
    printf ("\n  2. Segunda Opcion");
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
            printf ("\n Menu Modificar Jugador\n");
            system ("pause");
            ///menuModificarJugador();
            system("cls");
            ejecutarMenu();
            break;
        case 2:
            printf ("\n Menu Segunda Opcion\n");
            system ("pause");
            ///menuSegundaOpcion();
            system("cls");
            ejecutarMenu();
            break;
        default:
            system("cls");
            ejecutarMenu();
    }
}

void menuAdministrador(){
    char pass[20];
    system("cls");
    printf ("Ingreso al Menu Administrador.");
    printf ("\n Ingrese password: ");
    fflush (stdin);
    gets (pass);
    if (strcmp (pass, password)==0){
        ingresoAdmin ();
    } else {
        int intentos=2;
        printf (" Password incorrecta. Intentos restantes: %d", intentos);
        int seguirIntentando=1;
        while (intentos>0 && seguirIntentando==1){
            printf ("\n Ingrese password: ");
            fflush (stdin);
            gets (pass);
            if (strcmp (pass, password)==0){
                seguirIntentando=0;
                ingresoAdmin ();
            } else {
                intentos--;
                printf (" Password incorrecta.");
                if (intentos>0){
                    printf (" Intentos restantes: %d", intentos);
                } else {
                    printf (" No le quedan mas intentos.");
                }
            }
        }
    }

}
