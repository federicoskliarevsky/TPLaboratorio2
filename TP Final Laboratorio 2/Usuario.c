#include "Usuario.h"

void menuUsuario(nodoLiga * listaLigas, nodoArbol * arbolMercado){
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
            ejecutarMenu(listaLigas, arbolMercado);
            break;
        case 2:
            printf ("\n Menu Mi Club\n");
            system ("pause");
            ///menuMiClub();
            system("cls");
            ejecutarMenu(listaLigas, arbolMercado);
            break;
        default:
            system("cls");
            ejecutarMenu(listaLigas, arbolMercado);
    }
}

void verificarUsuario(nodoLiga * listaLigas,nodoArbol *  arbolMercado){
    int opcion = -1;
    system("cls");
    printf("Menu de Usuario:\n");
    printf ("\n  1.Ingresar Usuario");
    printf ("\n  2.Loguear Usuario");
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
            system("cls");
            int res = 0;
            while(res == 0)
            {
            system("cls");
            res = IngresarUsuario();
            }
            menuUsuario(listaLigas,arbolMercado);
            break;
        case 2:
            system("cls");
            LoguearUsuario();
            system("cls");
            verificarUsuario(listaLigas,arbolMercado);
            break;
        default:
            system("cls");
            ejecutarMenu(listaLigas, arbolMercado);
    }

}

int IngresarUsuario(){
  FILE * archUsuarios = fopen("usuarios.dat","rb");
  usuario a;
  char nombre[30];
  char pass[30];
  int res = 0;
  if(archUsuarios!=NULL)
  {
    printf("Ingrese Nombre Usuario:");
    fflush(stdin);
    gets(nombre);
    printf("ingrese Password:");
    fflush(stdin);
    gets(pass);
    while(fread(&a,sizeof(usuario),1,archUsuarios)>0 && res == 0)
    {
     if(strcmpi(a.nombreUser,nombre)==0 && strcmpi(a.pass,pass)==0)
     {
      res = 1;
     }
    }
  }
   fclose(archUsuarios);
   return res;
}

void LoguearUsuario(){
  FILE * archUsuarios = fopen("usuarios.dat","ab");
  if(archUsuarios!=NULL)
  {
   usuario a;
   printf("Ingrese Nombre Usuario:");
   fflush(stdin);
   gets(a.nombreUser);
   printf("ingrese Password:");
   fflush(stdin);
   gets(a.pass);
   printf("Ingrese nombre de club:");
   fflush(stdin);
   gets(a.club.nombreClub);
   printf("Ingrese camiseta de club:");
   fflush(stdin);
   gets(a.club.camiseta);
   printf("Ingrese estadio de club:");
   fflush(stdin);
   gets(a.club.estadio);
   a.club.arbolJugadoresClub = inicArbol();
   a.club.monedas = 2000000;
   fwrite(&a,sizeof(usuario),1,archUsuarios);
  }
  fclose(archUsuarios);
}
