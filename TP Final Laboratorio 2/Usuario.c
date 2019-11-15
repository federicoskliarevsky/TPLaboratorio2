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


/// Devuelve -1 si el ID no es encontrado. Si lo encuentra, devuelve la posicion
int buscaIDArreglo (int arr[], int IDBuscado, int validos){
    int rta = -1;
    int i = 0;
    while (i<validos && rta==-1){
        if (arr[i]==IDBuscado){
            rta = i;
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
                        printf ("\n El jugador ha sido contratado por tu club con exito!");
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

///Menu de venta de  un jugador
void ventaJugador (usuario * cargado, nodoArbol * arbolMercado){
    system("cls");
    printf ("USUARIO: %s |  CLUB: %s |  %c: %d ", cargado->nombreUser, cargado->club.nombreClub, 36, cargado->club.monedas);
    int validos = buscarValidos(cargado->club.arregloID);
    if (validos > 0){
        int IDBuscado;
        printf ("\n Ingrese el ID del jugador a vender: ");
        fflush (stdin);
        scanf ("%d", &IDBuscado);
        jugador encontrado = buscaIDArch(IDBuscado);
        int posicionID = buscaIDArreglo(cargado->club.arregloID, IDBuscado, validos);
        if (posicionID!=-1){ /// Si no lo encuentra en el arreglo
            printf ("\n Jugador encontrado: ");
            mostrarJugador(encontrado);
            char control='s';
            printf ("\n\n Esta seguro de que desea venderlo?");
            printf ("\n Le quedaran al club %d monedas.", cargado->club.monedas + encontrado.precio);
            printf ("\n S para confirmar: ");
            fflush (stdin);
            scanf ("%c", &control);
            if (control=='s'){
                cargado->club.arregloID[posicionID] = -1; /// Se elimina el jugador vendido del arreglo del club
                cargado->club.monedas += encontrado.precio; /// Se suma el precio del jugador a las monedas del club
                ordenarArregloMayorMenor(cargado->club.arregloID); /// Ordenamos el arreglo para que quede el -1 al final
                actualizaArchivoUsuarios(*cargado);
                printf ("\n El jugador ha sido vendido con exito!");
            }
        } else {
            printf ("\n El jugador ingresado no se encontro en el club.");
        }
    } else {
        printf ("\n No hay jugadores en el club.");
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
               ventaJugador(&cargado, arbolMercado);
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

void insertarOrdenado (int arreglo[], int i, int dato){
    while (i>=0 && dato > arreglo[i]){
        arreglo[i+1] = arreglo[i];
        i --;
    }
    arreglo[i+1] = dato;
}

void ordenarArregloMayorMenor (int arreglo[]){
    for (int i=0; i<MAXJugadores-1; i++){
        insertarOrdenado (arreglo, i, arreglo[i+1]);
    }
}

int buscaEliminados (usuario * cargado){
    int rtaMonedas = (*cargado).club.monedas;
    jugador encontrado;
    int validos = buscarValidos((*cargado).club.arregloID);
    for (int i=0; i<validos; i++){
        encontrado = buscaIDArch((*cargado).club.arregloID[i]);
        if (encontrado.eliminado==1){
            rtaMonedas += encontrado.precio;
            printf ("\nEl jugador %s fue eliminado por el administrador. Se le devolveran %d monedas a tu club!\n", encontrado.nombreJugador, encontrado.precio);
            system ("pause");
            (*cargado).club.arregloID[i] = -1;
        }
    }
    ordenarArregloMayorMenor ((*cargado).club.arregloID);
    return rtaMonedas;
}

void mostrarClub (usuario recibido){
    system("cls");
    printf ("USUARIO: %s |  CLUB: %s |  %c: %d ", recibido.nombreUser, recibido.club.nombreClub, 36, recibido.club.monedas);
    printf ("\n\nInformacion del Club:");
    printf ("\n\n Nombre de usuario: ");
    puts (recibido.nombreUser);
    printf (" Nombre de Club: ");
    puts (recibido.club.nombreClub);
    printf (" Camiseta: ");
    puts (recibido.club.camiseta);
    printf (" Estadio: ");
    puts (recibido.club.estadio);
    printf (" Monedas: %d\n\n", recibido.club.monedas);
    system ("pause");
}

void menuMiClub(nodoLiga * listaLigas, nodoArbol * arbolMercado,usuario cargado,nodoUsuario * listaUsuarios){
    int opcion=-1;
    system("cls");
    printf ("USUARIO: %s |  CLUB: %s |  %c: %d ", cargado.nombreUser, cargado.club.nombreClub, 36, cargado.club.monedas);
    printf ("\n\nMenu Mi Club", cargado.nombreUser);
    printf ("\n  1. Listado de jugadores.");
    printf ("\n  2. Informacion del club.");
    printf ("\n  3. Modificacion de club.");
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
            menuMiClub(listaLigas, arbolMercado,cargado,listaUsuarios);
            break;
        case 2:
            printf ("\n Eligio la opcion Informacion del Club.\n");
            system ("pause");
            mostrarClub (cargado);
            system("cls");
            menuMiClub(listaLigas, arbolMercado,cargado,listaUsuarios);
            break;
        case 3:
            printf("\n Modificacion del Club.\n");
            ///menuModificarClub
            menuMercado(listaLigas,arbolMercado,cargado,listaUsuarios);
            break;
        default:
            system("cls");
    }
}

float calcularPromedio (int arr[]){
    float promedio=0;
    float suma=0;
    int valoracion;
    for (int i=0; i<MAXJugadores; i++){
        valoracion = buscaIDArch(arr[i]).calificacion;
        suma += (float)valoracion;
    }
    promedio = suma/MAXJugadores;
    return promedio;
}

int resultadoPartido (float promJug, float promRiv){
    float diferencia = promJug - promRiv;
    float x;
    int resultado;
    if (diferencia > 0){
        if (diferencia>20){
            diferencia = 20; ///Seteamos un tope de diferencia
        }
        time (NULL);
        x = rand.()%100;
        if (x<=50+diferencia){
            resultado = 1;
        } else {
            if (x>=95){
                resultado = 0;
            } else {
                resultado = -1;
            }
        }
    } else { ///No tomamos valor absoluto porque tomamos dos casos, segun quien tenga el mayor promedio
        diferencia = promRiv - promJug;
        if (diferencia>20){
            diferencia = 20; ///Seteamos un tope de diferencia
        }
        time (NULL);
        x = rand()%100;
        if (x<=50+diferencia){
            resultado = -1;
        } else {
            if (x>=95){
                resultado = 0;
            } else {
                resultado = 1;
            }
        }
    }
    return resultado;
}

int menuJugarPartido (nodoLiga * listaLigas, nodoArbol * arbolMercado, usuario cargado, nodoUsuario * listaUsuarios){
    int rtaMonedas = cargado.club.monedas;
    int validosJugador = buscarValidos(cargado.club.arregloID);
    system ("cls");
    printf ("USUARIO: %s |  CLUB: %s |  %c: %d ", cargado.nombreUser, cargado.club.nombreClub, 36, cargado.club.monedas);
    printf ("\n\n Menu Jugar Partido.");
    if (validosJugador == MAXJugadores){
        char nombreLiga[30];
        printf ("  Ingrese liga del equipo que desea enfrentar: ");
        fflush (stdin);
        gets (nombreLiga);
        nodoLiga * ligaAux = inicListaliga();
        ligaAux = buscarLiga(listaLigas, nombreLiga);
        if (ligaAux!=NULL){
            char nombreEquipo[30];
            printf ("\n  Liga encontrada. Ingrese el equipo que desea enfrentar: ");
            fflush (stdin);
            gets (nombreEquipo);
            nodoEquipo * equipoAux = iniclistaEquipo();
            equipoAux = buscarEquipo(ligaAux->dato.listaEquipos, nombreEquipo);
            if (equipoAux!=NULL){
                int validosRival = buscarValidos(equipoAux->dato.arregloID);
                if (validosRival == MAXJugadores){
                    printf ("Todo correcto. A jugar!\n\n");
                    system ("pause");
                    int resultado = resultadoPartido(calcularPromedio(cargado.club.arregloID), calcularPromedio(equipoAux->dato.arregloID));
                    switch (resultado){
                        case -1:
                            printf ("\nPerdiste chinchulin. A caasa petee.");
                            break;
                        case 0:
                            printf ("\nEmpataste, casi casi campeon.");
                            break;
                        case 1:
                            printf ("\nGanaste titan!!!");
                    }
                    ///case -1: pierde el jugador, se elige un resultado correcto y se asignan las monedas
                    ///case 0: empate, se elige un resultado correcto y se asignan las monedas
                    ///case 1: gana el jugador, se elige un resultado correcto y se asignan las monedas
                    ///end switch
                    ///actualizacion del archivo
                } else {
                    printf ("\n  Los jugadores del equipo rival no son suficientes. El administrador debe cargar %d mas.\n\n", MAXJugadores - validosRival);
                    system ("pause");
                }
            } else {
                printf ("\n  Equipo no encontrado.\n\n");
                system ("pause");
            }
        } else {
            printf ("\n  Liga no encontrada.\n\n");
            system ("pause");
        }
    } else {
        printf ("\n  Los jugadores en tu equipo no son suficientes. Contas con %d y necesitas %d.\n\n", validosJugador, MAXJugadores);
        system ("pause");
    }
    return rtaMonedas;
}

void menuUsuario(nodoLiga * listaLigas, nodoArbol * arbolMercado,usuario cargado,nodoUsuario * listaUsuarios){
    int opcion=-1;
    int validos = buscarValidos(cargado.club.arregloID);
    cargado.club.monedas = buscaEliminados (&cargado);
    actualizaArchivoUsuarios(cargado);
    system("cls");
    printf ("USUARIO: %s |  CLUB: %s |  %c: %d ", cargado.nombreUser, cargado.club.nombreClub, 36, cargado.club.monedas);
    printf ("\n\nBienvenido, %s!\n Que desea hacer?", cargado.nombreUser);
    printf ("\n  1. Jugar partido.");
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
            cargado.club.monedas = menuJugarPartido(listaLigas, arbolMercado, cargado, listaUsuarios);
            system("cls");
            menuUsuario(listaLigas, arbolMercado,cargado,listaUsuarios);
            break;
        case 2:
            menuMiClub(listaLigas,arbolMercado,cargado,listaUsuarios);
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
                printf(" No hay usuarios cargados");
                Sleep(1000);
                verificarUsuario(listaLigas,arbolMercado,listaUsuarios);
            }
            break;
        case 2:
            system("cls");
            nodoUsuario * nuevoUsuario = LoguearUsuario();
            if (nuevoUsuario!=NULL){
                listaUsuarios = agregarFinalNodoUsuario(listaUsuarios,nuevoUsuario);
            }
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
    printf(" Ingrese Nombre Usuario:");
    fflush(stdin);
    gets(nombre);
    printf(" Ingrese Password:");
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

///Busca el nombre de usuario en el archivo. Si lo encuentra, devuelve 1
int buscaUsuarioArch (char nombreBuscado[]){
    int encontrado = 0;
    FILE * archUsuarios;
    archUsuarios = fopen ("usuarios.dat", "rb");
    if (archUsuarios!=NULL){
        usuario aux;
        while (fread(&aux, sizeof(usuario), 1, archUsuarios)>0 && encontrado==0){
            if (strcmpi(aux.nombreUser, nombreBuscado)==0){
                encontrado = 1;
            }
        }
    }
    fclose(archUsuarios);
    return encontrado;
}

nodoUsuario * LoguearUsuario(){
    FILE * archUsuarios = fopen("usuarios.dat","ab");
    usuario a;
    nodoUsuario * rta = NULL;
    if(archUsuarios!=NULL){
        printf("Ingrese Nombre Usuario:");
        fflush(stdin);
        gets(a.nombreUser);
        int encontrado = buscaUsuarioArch(a.nombreUser);
        if (encontrado==0){
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
            rta = crearNodoUsuario(a);
        } else {
            printf ("\n  Nombre de usuario ya existente.\n\n");
            system ("pause");
        }
    }
    fclose(archUsuarios);
    return rta;
}
