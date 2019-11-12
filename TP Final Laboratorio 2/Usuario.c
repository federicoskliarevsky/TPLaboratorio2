#include "Usuario.h"

nodoUsuario * inicListaUsuarios (){
    return NULL;
}

nodoUsuario * crearNodoUsuario(usuario dato){
    nodoUsuario * nuevoNodo = (nodoUsuario*) malloc(sizeof(nodoUsuario));
    nuevoNodo->dato = dato;
    nuevoNodo->sig = NULL;
    return nuevoNodo;
}

nodoUsuario * cargarListaUsuarios(nodoUsuario * listaUsuarios){
    usuario aux;
    FILE * archi = fopen("usuarios.dat","rb");
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(usuario),1,archi)> 0)
        {
            nodoUsuario * nuevo = crearNodoUsuario(aux);
            listaUsuarios = agregarFinalNodoUsuario(listaUsuarios,nuevo);
        }
    }
    fclose(archi);
    return listaUsuarios;
}

nodoUsuario *  agregarFinalNodoUsuario(nodoUsuario * listaUsuarios,nodoUsuario * nuevo){
 if(listaUsuarios==NULL)
 {
  listaUsuarios = nuevo;
 }else
 {
  nodoUsuario * ultimo = buscarUltimoUsuario(listaUsuarios);
  ultimo->sig = nuevo;
 }
 return listaUsuarios;
}

nodoUsuario * buscarUltimoUsuario(nodoUsuario * listaUsuarios){
 nodoUsuario* seg=listaUsuarios;
 while(seg->sig!=NULL){
    seg=seg->sig;
 }
 return seg;
}


/// Devuelve -1 si el ID no es encontrado
int buscaIDArreglo (int arr[], int IDBuscado, int validos){
    int rta = -1;
    int i = 0;
    while (i<validos && rta==-1){
        if (arr[i]==IDBuscado){
            rta = arr[i];
        }
        i++;
    }
    return rta;
}

///Menu de compra de  un jugador
void compraJugador (usuario * cargado, nodoArbol * arbolMercado){
    system("cls");
    printf ("USUARIO: %s |  CLUB: %s |  %c: %d ", cargado->nombreUser, cargado->club.nombreClub, 36, cargado->club.monedas);
    int validos = buscarValidos(cargado->club.arregloID);
    if (validos <MAXJugadores){
        int IDBuscado;
        printf ("\n Ingrese el ID del jugador a comprar: ");
        fflush (stdin);
        scanf ("%d", &IDBuscado);
        jugador encontrado = buscaIDArch(IDBuscado);
        if (encontrado.ID == IDBuscado && encontrado.eliminado==0){
            printf ("\n Jugador encontrado: ");
            mostrarJugador(encontrado);
            if (buscaIDArreglo(cargado->club.arregloID, IDBuscado, validos)==-1){ /// Si no lo encuentra en el arreglo
                if (encontrado.precio <= cargado->club.monedas){
                    char control='s';
                    printf ("\n\n Esta seguro de que desea comprarlo?");
                    printf ("\n Le quedaran al club %d monedas.", cargado->club.monedas- encontrado.precio);
                    printf ("\n S para confirmar: ");
                    fflush (stdin);
                    scanf ("%c", &control);
                    if (control=='s'){
                        cargado->club.arregloID[validos] = IDBuscado; /// Se agrega el nuevo jugador al arreglo del club
                        /** validos++; Por ahora no hace falta */
                        cargado->club.monedas -= encontrado.precio; /// Se resta el precio del jugador a las monedas del club
                        actualizaArchivoUsuarios(*cargado);
                    }
                } else {
                    printf ("\n\n Monedas insuficientes. Faltan %d monedas.", encontrado.precio - cargado->club.monedas);
                }
            } else {
                printf ("\n El jugador %s (ID %d) ya es parte de tu club.", encontrado.nombreJugador, encontrado.ID);
            }
        } else {
            printf ("\n El jugador ingresado no se encontro.");
        }
    } else {
        printf ("\n No hay espacio para otro jugador, ya hay %d cargados en el club. Por favor, venda uno.");
    }
    printf ("\n\n");
    system ("pause");
}

void menuMercado(nodoLiga * listaLigas, nodoArbol * arbolMercado,usuario cargado,nodoUsuario * listaUsuarios){
 int opcion=-1;
    system("cls");
    printf ("USUARIO: %s |  CLUB: %s |  %c: %d ", cargado.nombreUser, cargado.club.nombreClub, 36, cargado.club.monedas);
    printf ("\n\nBienvenido al Menu Mercado. Que desea hacer?");
    printf ("\n  1. Comprar jugadores.");
    printf ("\n  2. Vender jugador");
    printf ("\n  3. Ver el mercado.");
    printf ("\n  0. Para salir.");
    printf ("\n\n Ingrese la opcion deseada: ");
    fflush (stdin);
    scanf ("%d", &opcion);
    while (opcion<0 || opcion>3){
        printf ("\nSe ingreso una opcion incorrecta. Por favor, ingrese una opcion valida: ");
        fflush (stdin);
        scanf ("%d", &opcion);
    }
    switch(opcion){
           case 1:
               compraJugador(&cargado, arbolMercado);
               menuMercado(listaLigas,arbolMercado,cargado,listaUsuarios);
               break;
           case 2:
               ///ventaJugador();
               menuMercado(listaLigas,arbolMercado,cargado,listaUsuarios);
               break;
           case 3:
               system("cls");
               printf ("\n  Arbol Mercado:");
               mostrarInOrder(arbolMercado);
               printf ("\n");
               system("pause");
               menuMercado(listaLigas,arbolMercado,cargado,listaUsuarios);
               break;
           default:
               system("cls");
               menuUsuario(listaLigas,arbolMercado,cargado,listaUsuarios);
            }
}

void actualizaArchivoUsuarios (usuario recibido){
    FILE * archUsuarios;
    archUsuarios = fopen("usuarios.dat", "r+b");
    usuario aux;
    int encontrado=0;
    if (archUsuarios!=NULL){
        while (fread(&aux, sizeof(usuario), 1, archUsuarios)>0 && encontrado==0){
            if (strcmpi(aux.nombreUser, recibido.nombreUser)==0){
                fseek(archUsuarios, sizeof(usuario)*(-1), SEEK_CUR);
                fwrite(&recibido, sizeof(usuario), 1, archUsuarios);
                fclose(archUsuarios);
                encontrado = 1;
            }
        }
    } else {
        printf ("\n Archivo no abierto.");
    }
    fclose(archUsuarios);
}

void menuUsuario(nodoLiga * listaLigas, nodoArbol * arbolMercado,usuario cargado,nodoUsuario * listaUsuarios){
    int opcion=-1;
    system("cls");
    printf ("USUARIO: %s |  CLUB: %s |  %c: %d ", cargado.nombreUser, cargado.club.nombreClub, 36, cargado.club.monedas);
    printf ("\n\nBienvenido, %s!\n Que desea hacer?", cargado.nombreUser);
    printf ("\n  1. Listado de jugadores.");
    printf ("\n  2. Ir a Mi Club");
    printf ("\n  3. Ir a Mercado.");
    printf ("\n  0. Para salir.");
    printf ("\n\n Ingrese la opcion deseada: ");
    fflush (stdin);
    scanf ("%d", &opcion);
    while (opcion<0 || opcion>3){
        printf ("\nSe ingreso una opcion incorrecta. Por favor, ingrese una opcion valida: ");
        fflush (stdin);
        scanf ("%d", &opcion);
    }
    switch (opcion){
        case 1:
            printf ("\n Listado de jugadores.\n");
            Sleep(1000);
            int validos = buscarValidos(cargado.club.arregloID);
            if (validos>0){
                mostrarArregloID(cargado.club.arregloID,validos);
                printf ("\n\n Fin de muestra de jugadores.\n\n");
                system ("pause");
            } else {
                printf ("\n No hay jugadores cargados.");
                Sleep(1000);
            }
            system("cls");
            menuUsuario(listaLigas, arbolMercado,cargado,listaUsuarios);
            break;
        case 2:
            printf ("\n Menu Mi Club\n");
            system ("pause");
            ///menuMiClub();
            system("cls");
            menuUsuario(listaLigas, arbolMercado,cargado,listaUsuarios);
            break;
        case 3:
            printf("\n Ingreso al mercado ");
            Sleep(200);
            printf (". ");
            Sleep (200);
            printf (". ");
            Sleep (200);
            printf (". ");
            Sleep (200);
            menuMercado(listaLigas,arbolMercado,cargado,listaUsuarios);
            break;
        default:
            system("cls");
            verificarUsuario(listaLigas,arbolMercado,listaUsuarios);
    }
}

usuario verificarUsuario(nodoLiga * listaLigas,nodoArbol *  arbolMercado,nodoUsuario * listaUsuarios){
    int opcion = -1;
    usuario cargado;
    system("cls");
    printf("Menu de Usuario:\n");
    printf ("\n  1.Log in de Usuario");
    printf ("\n  2.Crear Usuario");
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
            if(listaUsuarios!=NULL){
                system("cls");
                int res = 0, intento = 3;
                while(res == 0 && intento != 0){
                    intento--;
                    system("cls");
                    res = IngresarUsuario(&cargado);
                }
                if(intento == 0){
                    verificarUsuario(listaLigas,arbolMercado,listaUsuarios);
                }
                if (res==1){
                    menuUsuario(listaLigas,arbolMercado,cargado,listaUsuarios);
                }
            } else {
                system("cls");
                printf("no hay usuarios cargados");
                Sleep(1000);
                verificarUsuario(listaLigas,arbolMercado,listaUsuarios);
            }
            break;
        case 2:
            system("cls");
            listaUsuarios = agregarFinalNodoUsuario(listaUsuarios,LoguearUsuario());
            system("cls");
            verificarUsuario(listaLigas,arbolMercado,listaUsuarios);
            break;
        default:
            system("cls");
            ejecutarMenu(listaLigas, arbolMercado);
    }
 return cargado;
}

int  IngresarUsuario(usuario* aux){
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
      *aux = a;
     }
    }
  }
   fclose(archUsuarios);
   return res;
}

nodoUsuario * LoguearUsuario(){
  FILE * archUsuarios = fopen("usuarios.dat","ab");
  usuario a;
  if(archUsuarios!=NULL)
  {
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
   a.club.monedas = 2000000;
   crearArregloID(a.club.arregloID);
   fwrite(&a,sizeof(usuario),1,archUsuarios);
  }
  fclose(archUsuarios);
  return crearNodoUsuario(a);
}
