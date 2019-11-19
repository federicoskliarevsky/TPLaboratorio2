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
void compraJugador (usuario * cargado,nodoMercado * listaMercado){
    system("cls");
    printf ("USUARIO: %s |  CLUB: %s |  %c: %d ", cargado->nombreUser, cargado->club.nombreClub, 36, cargado->club.monedas);
    int validos = buscarValidos(cargado->club.arregloID);
    if (validos <MAXJugadores){
        int IDBuscado;
        printf ("\n\nIngrese el ID del jugador a comprar: ");
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
        printf ("\n\nNo hay espacio para otro jugador, ya hay %d cargados en el club. Por favor, venda uno.", validos);
    }
    printf ("\n\n");
    system ("pause");
}

///Menu de venta de  un jugador
void ventaJugador (usuario * cargado,nodoMercado * listaMercado){
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
        if (posicionID!=-1){ /// Si lo encuentra en el arreglo
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

void menuMercado(nodoLiga * listaLigas,nodoMercado * listaMercado,usuario cargado,nodoUsuario * listaUsuarios){
 int opcion=-1;
    system("cls");
    printf ("USUARIO: %s |  CLUB: %s |  %c: %d ", cargado.nombreUser, cargado.club.nombreClub, 36, cargado.club.monedas);
    printf ("\n\nMenu Mercado.\n Opciones disponibles:");
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
               compraJugador(&cargado,listaMercado);
               menuMercado(listaLigas,listaMercado,cargado,listaUsuarios);
               break;
           case 2:
               ventaJugador(&cargado,listaMercado);
               menuMercado(listaLigas,listaMercado,cargado,listaUsuarios);
               break;
           case 3:
               system("cls");
               printf ("\n  Lista Mercado:");
               MostrarMercado(listaMercado);
               printf ("\n");
               system("pause");
               menuMercado(listaLigas,listaMercado,cargado,listaUsuarios);
               break;
           default:
               system("cls");
               menuUsuario(listaLigas,listaMercado,cargado,listaUsuarios);
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
    printf ("\n\n Nombre de usuario: %s.\n", recibido.nombreUser);
    printf (" Nombre de Club: %s.\n", recibido.club.nombreClub);
    printf (" Camiseta: %s.\n", recibido.club.camiseta);
    printf (" Estadio: %s.\n", recibido.club.estadio);
    printf (" Monedas: %c %d.\n\n", 36, recibido.club.monedas);
    system ("pause");
}

///ESTA FUNCION ES PARA MODIFICAR EL ARCHIVO CON LO QUE SE ENCUENTRA EN EL CLUB
void reemplazarArchivoUsuario(usuario modificado){
  FILE * archUsuarios = fopen("usuarios.dat","r+b");
  if(archUsuarios != NULL){
    usuario usuarioaux;
    int encontrado = 0;
    while((fread(&usuarioaux,sizeof(usuario),1,archUsuarios)>0) && (encontrado == 0)){
      if(strcmpi(usuarioaux.nombreUser,modificado.nombreUser) == 0){
        fseek(archUsuarios,sizeof(usuario)*(-1),SEEK_CUR);
        fwrite(&modificado,sizeof(usuario),1,archUsuarios);
        fclose(archUsuarios);
        encontrado = 1;
      }
    }
    fclose(archUsuarios);
  }
}


nodoUsuario *  menuModificarClub(usuario *  recibido,nodoUsuario * listaUsuarios){
    int opcion = -1,dinero = 0;
    char hack[30];
    system("cls");
    printf ("USUARIO: %s |  CLUB: %s |  %c: %d ", recibido->nombreUser, recibido->club.nombreClub, 36, recibido->club.monedas);
    printf ("\n\nMenu Modificar Mi Club", recibido->nombreUser);
    printf ("\n  1. Modificar nombre del Club.");
    printf ("\n  2. Modificar estadio.");
    printf ("\n  3. Modificar camiseta.");
    printf ("\n  0. Para salir.");
    printf("\n\nIngrese la opcion deseada: ");
    fflush(stdin);
    scanf("%d",&opcion);
    while (opcion<0 || opcion>3 && opcion !=55){
        printf ("\nSe ingreso una opcion incorrecta. Por favor, ingrese una opcion valida: ");
        fflush (stdin);
        scanf ("%d", &opcion);
    }
    switch(opcion){
        case 1:
            system("cls");
            printf("\nIngrese el nuevo nombre del Club: ");
            fflush(stdin);
            gets(recibido->club.nombreClub);
            reemplazarArchivoUsuario(*recibido);
            printf("\nCambio de Nombre de Club a %s con exito.",recibido->club.nombreClub);
            Sleep(2000);
            break;
        case 2:
            system("cls");
            printf("\nIngrese el nuevo estadio: ");
            fflush(stdin);
            gets(recibido->club.estadio);
            reemplazarArchivoUsuario(*recibido);
            printf("\nCambio de estadio a %s con exito.",recibido->club.estadio);
            Sleep(2000);
            break;
        case 3:
            system("cls");
            printf("Ingrese la nueva camiseta: ");
            fflush(stdin);
            gets(recibido->club.camiseta);
            reemplazarArchivoUsuario(*recibido);
            printf("\nCambio de camiseta a %s con exito.",recibido->club.camiseta);
            Sleep(2000);
            break;
        case 55:
            system("cls");
            printf("Menu hack.\n");
            printf("  Ingrese hack: ");
            fflush(stdin);
            gets(hack);
            if(strcmpi(hack,"klapaucius")==0){
                printf("  Ingrese dinero a cargar: ");
                scanf("%d",&dinero);
                Sleep(1000);
                if (dinero + recibido->club.monedas >=0){
                    recibido->club.monedas += dinero;
                    reemplazarArchivoUsuario(*recibido);
                } else {
                    printf("\n  No es posible descontar %d monedas.", dinero*-1);
                    Sleep(3000);
                }
            } else {
                printf("\n  El hack %s no existe.", hack);
                Sleep(3000);
            }
            break;
        default:
            reemplazarArchivoUsuario(*recibido);
            system("cls");

    }
    return listaUsuarios;
}

nodoUsuario *  menuMiClub(nodoLiga * listaLigas,nodoMercado * listaMercado,usuario * cargado,nodoUsuario * listaUsuarios){
    int opcion=-1;
    system("cls");
    printf ("USUARIO: %s |  CLUB: %s |  %c: %d ", cargado->nombreUser, cargado->club.nombreClub, 36, cargado->club.monedas);
    printf ("\n\nMenu Mi Club", cargado->nombreUser);
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
            int validos = buscarValidos(cargado->club.arregloID);
            if (validos>0){
                mostrarArregloID(cargado->club.arregloID,validos);
                printf ("\n\n Fin de muestra de jugadores.\n\n");
                system ("pause");
            } else {
                printf ("\n No hay jugadores cargados.");
                Sleep(1000);
            }
            system("cls");
            listaUsuarios = menuMiClub(listaLigas,listaMercado,cargado,listaUsuarios);
            break;
        case 2:
            mostrarClub (*cargado);
            system("cls");
            listaUsuarios = menuMiClub(listaLigas,listaMercado,cargado,listaUsuarios);
            break;
        case 3:
            printf("\n Modificacion del Club.\n");
            listaUsuarios = menuModificarClub(cargado,listaUsuarios);
            listaUsuarios = menuMiClub(listaLigas,listaMercado,cargado,listaUsuarios);
            break;
        default:
            system("cls");
    }
    return listaUsuarios;
}

///Promedio de un equipo
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

///Recibe los promedios de calificaciones del equipo del usuario y del equipo del rival. Segun la diferencia, tenemos dos casos:
///que el usuario tenga más promedio: la probabilidad es de 50+la diferencia. Si la prob es mayor a 70, se limita a 70.
///que el rival tenga más promedio: ídem anterior.
///Luego se hace un random de 0 a 100. Según dónde caiga será el resultado del partido, siempre que caiga entre 95 y 100 será empate.
///Tomamos los dos casos como separados por cómo se le asignan valores a la variable resultado: -1 por perder, 0 por empatar, 1 por ganar
int resultadoPartido (float promJug, float promRiv){
    float diferencia = promJug - promRiv;
    float x;
    int resultado;
    if (diferencia > 0){
        if (diferencia>20){
            diferencia = 20; ///Seteamos un tope de diferencia del 70%
        }
        srand(time(NULL));
        x = (float) (rand()%100)+1;
        if (x<=50+diferencia){
            resultado = 1;
        } else {
            if (x>=95){
                resultado = 0;
            } else {
                resultado = -1;
            }
        }
    } else { ///No tomamos valor absoluto porque tomamos dos casos, según quién tenga el mayor promedio
        diferencia = promRiv - promJug;
        if (diferencia>20){
            diferencia = 20; ///Seteamos un tope de diferencia del 70%
        }
        srand(time(NULL));
        x = (float) (rand()%100)+1;
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

///Recibe el valor del resultado (-1, 0 o 1). Calcula los goles, como máximo 5 por equipo, y calcula al azar los jugadores que los hicieron.
///Devuelve las monedas ganadas. Se podrá ganar un mínimo de 50 (perder 5-0) y un máximo de 400 (ganar 5-0).
int calcularMonedas (int resultado, usuario cargado, nodoEquipo * rival){
    int rtaMonedas = 0;
    int x = -1; ///Goles usuario
    int y = -1; ///Goles rival
    int jugX=-1; ///Variable para calcular posiciones de jugadores en los arreglos
    printf ("\n\n      SIMULANDO PARTIDO    ");
    for (int i=0; i<15; i++){
        Sleep(200);
        printf ("%c  ", 178);
    }
    srand(time(NULL));
    switch (resultado){
        case -1:                    /// Usuario pierde
            while (y<=0){           /// Le asignamos a Y un random mayor a 0 y menor a 6
                y = (rand()%5)+1;
            }
            if (y==1){              /// Le asignamos a x un valor menor a Y
                x = 0;
            } else {
                while (x>=y || x<0){
                    x = (rand()%5)+1;
                }
            }
            printf("\n\n       %c", 201);
            for(int i=0; i<10; i++){
                printf("%c",205);
                Sleep(20);
            }
            printf ("%c", 187);
            printf ("\n       %c DERROTA. %c\n", 186, 186);
            printf("       %c", 200);
            for(int i=0; i<10; i++){
                printf("%c",205);
                Sleep(20);
            }
            printf ("%c", 188);
            printf ("\n        Resultado del partido: %s %d - %s %d.\n\n", cargado.club.nombreClub, x, rival->dato.nombreEquipo, y);
            rtaMonedas += 150 + x*30 - y*20; ///150 monedas por perder, 30 por gol a favor y -20 por gol en contra. Rango de ganancias: [50,170]
            if (x>0){
                printf ("\n        Goles de tu equipo %s:\n", cargado.club.nombreClub);
                for (int i=0; i<x; i++){
                    jugX = -1;
                    while (jugX<0 || jugX>10){
                        jugX = (rand()%10)+1;
                    }
                    Sleep (200);
                    printf ("\n         Gol de %s.\n", buscaIDArch(cargado.club.arregloID[jugX]).nombreJugador);
                }
            } else {
                printf ("\n        Tu equipo %s no hizo goles.\n", cargado.club.nombreClub);
            }
            printf ("\n\n        Goles del equipo rival %s:\n", rival->dato.nombreEquipo);
            for (int i=0; i<y; i++){
                jugX = -1;
                while (jugX<0 || jugX>10){
                    jugX = (rand()%10)+1;
                }
                Sleep (200);
                printf ("\n         Gol de %s.\n", buscaIDArch(rival->dato.arregloID[jugX]).nombreJugador);
            }
            printf ("\n\n         Informe de monedas:");
            printf ("\n          Monedas por la derrota: %c 150.", 36);
            printf ("\n          Monedas por goles a favor: %c %d.", 36, x*30);
            printf ("\n          Monedas por goles en contra: - %c %d.", 36, y*20);
            printf ("\n\n         Total de monedas ganadas en el partido: %c %d.", 36, rtaMonedas);
            break;
        case 0:                     /// Empate
            while (y<=0){           /// Le asignamos a Y un random mayor a 0 y menor a 6
                y = (rand()%5)+1;
            }
            x = y;                  /// Le asignamos a x un valor igual a Y
            printf("\n\n       %c", 201);
            for(int i=0; i<10; i++){
                printf("%c",205);
                Sleep(20);
            }
            printf ("%c", 187);
            printf ("\n       %c EMPATE.  %c\n", 186, 186);
            printf("       %c", 200);
            for(int i=0; i<10; i++){
                printf("%c",205);
                Sleep(20);
            }
            printf ("%c", 188);
            printf ("\n        Resultado del partido: %s %d - %s %d.\n\n", cargado.club.nombreClub, x, rival->dato.nombreEquipo, y);
            rtaMonedas += 200 + x*30 - y*20; ///200 monedas por empatar, 30 por gol a favor y -20 por gol en contra. Rango de ganancias: [200,250]
            if (x>0){
                printf ("\n        Goles de tu equipo %s:\n", cargado.club.nombreClub);
                for (int i=0; i<x; i++){
                    jugX = -1;
                    while (jugX<0 || jugX>10){
                        jugX = (rand()%10)+1;
                    }
                    Sleep (200);
                    printf ("\n         Gol de %s.\n", buscaIDArch(cargado.club.arregloID[jugX]).nombreJugador);
                }
                printf ("\n\n        Goles del equipo rival %s:\n", rival->dato.nombreEquipo);
                for (int i=0; i<y; i++){
                    jugX = -1;
                    while (jugX<0 || jugX>10){
                        jugX = (rand()%10)+1;
                    }
                    Sleep (200);
                    printf ("\n         Gol de %s.\n", buscaIDArch(rival->dato.arregloID[jugX]).nombreJugador);
                }
            } else {
                printf ("\n        Fue un partido sin goles.\n");
            }
            printf ("\n\n         Informe de monedas:");
            printf ("\n          Monedas por el empate: %c 200.", 36);
            printf ("\n          Monedas por goles a favor: %c %d.", 36, x*30);
            printf ("\n          Monedas por goles en contra: - %c %d.", 36, y*20);
            printf ("\n\n         Total de monedas ganadas en el partido: %c %d.", 36, rtaMonedas);
            break;
        case 1:                     /// Usuario gana
            while (x<=0){           /// Le asignamos a Y un random mayor a 0 y menor a 6
                x = (rand()%5)+1;
            }
            if (x==1){              /// Le asignamos a x un valor menor a Y
                y = 0;
            } else {
                while (y>=x || y<0){
                    y = (rand()%5)+1;
                }
            }
            printf("\n\n       %c", 201);
            for(int i=0; i<10; i++){
                printf("%c",205);
                Sleep(20);
            }
            printf ("%c", 187);
            printf ("\n       %c VICTORIA.%c\n", 186, 186);
            printf("       %c", 200);
            for(int i=0; i<10; i++){
                printf("%c",205);
                Sleep(20);
            }
            printf ("%c", 188);
            printf ("\n        Resultado del partido: %s %d - %s %d.\n\n", cargado.club.nombreClub, x, rival->dato.nombreEquipo, y);
            rtaMonedas += 250 + x*30 - y*20; ///250 monedas por ganar, 30 por gol a favor y -20 por gol en contra. Rango de ganancias: [320,400]
            printf ("\n        Goles de tu equipo %s:\n", cargado.club.nombreClub);
            for (int i=0; i<x; i++){
                jugX = -1;
                while (jugX<0 || jugX>10){
                    jugX = (rand()%10)+1;
                }
                Sleep (200);
                printf ("\n         Gol de %s.\n", buscaIDArch(cargado.club.arregloID[jugX]).nombreJugador);
            }
            if (y>0){
                printf ("\n\n        Goles del equipo rival %s:\n", rival->dato.nombreEquipo);
                for (int i=0; i<y; i++){
                    jugX = -1;
                    while (jugX<0 || jugX>10){
                        jugX = (rand()%10)+1;
                    }
                    Sleep (200);
                    printf ("\n         Gol de %s.\n", buscaIDArch(rival->dato.arregloID[jugX]).nombreJugador);
                }
            } else {
                printf ("\n        El equipo rival %s no hizo goles.\n", rival->dato.nombreEquipo);
            }
            printf ("\n\n         Informe de monedas:");
            printf ("\n          Monedas por la victoria: %c 250.", 36);
            printf ("\n          Monedas por goles a favor: %c %d.", 36, x*30);
            printf ("\n          Monedas por goles en contra: - %c %d.", 36, y*20);
            printf ("\n\n         Total de monedas ganadas en el partido: %c %d.", 36, rtaMonedas);
            break;
    }
    return rtaMonedas;
}

///Pide liga y equipo a enfrentar. Si los encuentra y los equipos cuentan con 11 jugadores, recibe las monedas ganadas y las cambia en el club.
int menuJugarPartido (nodoLiga * listaLigas,nodoMercado * listaMercado, usuario cargado, nodoUsuario * listaUsuarios){
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
                    printf ("\n   Todo correcto. A jugar!\n\n    ");
                    system ("pause");
                    int resultado = resultadoPartido(calcularPromedio(cargado.club.arregloID), calcularPromedio(equipoAux->dato.arregloID));
                    rtaMonedas += calcularMonedas (resultado, cargado, equipoAux); /// Resultado: -1 si pierde el jugador, 0 si hay empate, 1 si gana el jugador
                    actualizaArchivoUsuarios(cargado); ///Actualizamos las monedas en el archivo de usuarios
                    printf ("\n\n         ");
                    system ("pause");
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

nodoUsuario *  menuUsuario(nodoLiga * listaLigas,nodoMercado *  listaMercado,usuario cargado,nodoUsuario * listaUsuarios){
    int opcion=-1;
    int validos = buscarValidos(cargado.club.arregloID);
    cargado.club.monedas = buscaEliminados (&cargado);
    actualizaArchivoUsuarios(cargado);
    system("cls");
    printf ("USUARIO: %s |  CLUB: %s |  %c: %d ", cargado.nombreUser, cargado.club.nombreClub, 36, cargado.club.monedas);
    printf ("\n\nBienvenido, %s!\n Opciones disponibles:", cargado.nombreUser);
    printf ("\n  1. Jugar partido.");
    printf ("\n  2. Ir a Mi Club.");
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
            cargado.club.monedas = menuJugarPartido(listaLigas,listaMercado, cargado, listaUsuarios);
            system("cls");
            listaUsuarios = menuUsuario(listaLigas,listaMercado,cargado,listaUsuarios);
            break;
        case 2:
            listaUsuarios = menuMiClub(listaLigas,listaMercado,&cargado,listaUsuarios);
            system("cls");
            listaUsuarios = menuUsuario(listaLigas,listaMercado,cargado,listaUsuarios);
            break;
        case 3:
            menuMercado(listaLigas,listaMercado,cargado,listaUsuarios);
            break;
        default:
            system("cls");
            verificarUsuario(listaLigas,listaMercado,listaUsuarios);
    }
}

usuario verificarUsuario(nodoLiga * listaLigas,nodoMercado *  listaMercado,nodoUsuario * listaUsuarios){
    int opcion = -1;
    usuario cargado;
    system("cls");
    printf("Menu de Usuario:\n Opciones disponibles:");
    printf ("\n  1. Log in de Usuario.");
    printf ("\n  2. Crear Usuario.");
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
                    if (res==0){
                        printf ("  El usuario o la contrase%ca ingresados son incorrectos.", 164);
                        if (intento>0){
                            printf (" Intentos restantes: %d.\n\n", intento);
                            system ("pause");
                        } else {
                            printf ("  No le quedan mas intentos.\n\n");
                            system ("pause");
                            system("cls");
                        }
                    }
                }
                if(intento == 0){
                    verificarUsuario(listaLigas,listaMercado,listaUsuarios);
                }
                if (res==1){
                    menuUsuario(listaLigas,listaMercado,cargado,listaUsuarios);
                }
            } else {
                system("cls");
                printf("No hay usuarios cargados.");
                Sleep(1000);
                verificarUsuario(listaLigas,listaMercado,listaUsuarios);
            }
            break;
        case 2:
            system("cls");
            nodoUsuario * nuevoUsuario = LoguearUsuario();
            if (nuevoUsuario!=NULL){
                listaUsuarios = agregarFinalNodoUsuario(listaUsuarios,nuevoUsuario);
            }
            system("cls");
            verificarUsuario(listaLigas,listaMercado,listaUsuarios);
            break;
        default:
            system("cls");
            ejecutarMenu(listaLigas,listaMercado);
    }
    return cargado;
}

int IngresarUsuario(usuario* aux){
    FILE * archUsuarios = fopen("usuarios.dat","rb");
    usuario a;
    char nombre[30];
    char pass[30];
    int res = 0;
    if(archUsuarios!=NULL){
        printf(" Ingrese nombre de usuario: ");
        fflush(stdin);
        gets(nombre);
        printf(" Ingrese contrase%ca: ", 164);
        fflush(stdin);
        gets(pass);
        while(fread(&a,sizeof(usuario),1,archUsuarios)>0 && res == 0){
            if(strcmpi(a.nombreUser,nombre)==0 && strcmpi(a.pass,pass)==0){
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
