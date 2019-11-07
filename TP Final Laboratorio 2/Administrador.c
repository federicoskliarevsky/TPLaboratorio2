#include "Administrador.h"
/** Carga jugadores a su correpondiente archivo y arbol.Si el nombre de liga o equipo ingresado en los datos del jugador no se
encuentra en la lista de ligas o equipos se pedira al administrador que cargue la liga o el equipo no encontrado.Caso contrario
el jugador ingresado se cargara directamente al arbol y archivo**/

nodoLiga * cargaArchJugadores(nodoLiga * listaLigas, nodoArbol ** arbolMercado){
    FILE * archJug;
    archJug = fopen("Jugadores.dat", "ab");
    jugador aux;
    char control='s';
    system("Cls");
    printf ("Ingreso al menu cargar archivo de jugadores.");
    while (control=='s'){
        printf ("\n Lectura de datos de jugador:");
        if (leerJugador(&aux)==0){
            nodoLiga * listaLigasAuxiliar = inicListaliga();
            nodoEquipo * listaEquiposAuxiliar = iniclistaEquipo();
            listaLigasAuxiliar = buscarLiga(listaLigas, aux.nombreLiga);
            if (listaLigasAuxiliar!=NULL){
                listaEquiposAuxiliar = buscarEquipo(listaLigasAuxiliar->dato.listaEquipos, aux.nombreEquipo);
            }
            if (listaLigasAuxiliar==NULL || listaEquiposAuxiliar==NULL){ ///Si no encontro la liga o si no encontro al equipo
                printf ("\n  La liga o el equipo ingresados no existen. A continuacion debera crearlos.");
                system ("pause");
                listaLigas = cargaArchEquipos(listaLigas); ///Usamos esta funcion para no crear una muy parecida que solo pida un equipo
            }
            fwrite(&aux, sizeof(jugador), 1, archJug);
            listaLigasAuxiliar = buscarLiga(listaLigas, aux.nombreLiga);
            listaEquiposAuxiliar = buscarEquipo(listaLigasAuxiliar->dato.listaEquipos, aux.nombreEquipo);
            listaEquiposAuxiliar->dato.arbolJugadoresEquipo = insertarArbol(listaEquiposAuxiliar->dato.arbolJugadoresEquipo, aux);
            *arbolMercado = insertarArbol(arbolMercado, aux);
            system ("cls");
        } else {
            printf ("\n Jugador ya ingresado.");
        }
        printf ("\n Desea ingresar otro jugador? (s para continuar): ");
            fflush (stdin);
            scanf ("%c", &control);
    }
    fclose(archJug);
    return listaLigas;
}


///Muestra todos los jugadores cargados exitosamente al archivo
void muestraArchJugadores (){
    FILE * archJug;
    archJug = fopen("Jugadores.dat", "rb");
    jugador aux;
    system("Cls");
    printf ("Ingreso al menu mostrar archivo de jugadores.");
    while (fread(&aux, sizeof(jugador), 1, archJug)>0){
        printf("\n");
        mostrarJugador(aux);
    }
    printf ("\n\n");
    system ("Pause");
    fclose(archJug);
}

nodoLiga * bajaJugador (nodoLiga * listaLigas, nodoArbol ** arbolMercado){
    char nombreLiga[30];
    printf ("Ingreso al menu baja de jugador.\n");
    printf ("  Ingrese liga del jugador a dar de baja: ");
    fflush (stdin);
    gets (nombreLiga);
    nodoLiga * ligaAux = inicListaliga();
    ligaAux = buscarLiga(listaLigas, nombreLiga);
    if (ligaAux!=NULL){
        char nombreEquipo[30];
        printf ("\n  Liga encontrada. Ingrese equipo del jugador a dar de baja: ");
        fflush (stdin);
        gets (nombreEquipo);
        nodoEquipo * equipoAux = iniclistaEquipo();
        equipoAux = buscarEquipo(ligaAux->dato.listaEquipos, nombreEquipo);
        if (equipoAux!=NULL){
            char nombreJugador[30];
            printf ("\n  Equipo encontrado. Ingrese el nombre del jugador a dar de baja: ");
            fflush (stdin);
            gets (nombreJugador);
            nodoArbol * arbolAux = inicArbol();
            arbolAux = buscarJugador (*arbolMercado, nombreJugador);
            if (arbolAux!=NULL){
                if (arbolAux->dato.eliminado==0){
                    char opcion;
                    printf ("\n  Jugador encontrado. Datos: ");
                    mostrarJugador(arbolAux->dato);
                    printf ("\n  Esta seguro de que desea eliminarlo? (s para confirmar): ");
                    fflush (stdin);
                    scanf ("%c", &opcion);
                    if (opcion=='s'){
                        arbolAux->dato.eliminado = 1; ///Baja el jugador en el arbolMercado
                        FILE * archJugadores = fopen("Jugadores.dat", "r+b"); ///Baja el jugador en el arch jugadores
                        if (archJugadores!=NULL){
                            jugador jugadorAux;
                            int encontrado = 0;
                            while (fread(&jugadorAux, sizeof(jugador), 1, archJugadores)>0 && encontrado == 0){
                                if (strcmpi(jugadorAux.nombreJugador, nombreJugador)==0){
                                    fseek(archJugadores, sizeof(jugador)*(-1), SEEK_CUR);
                                    jugadorAux.eliminado=1;
                                    fwrite(&jugadorAux, sizeof(jugador), 1, archJugadores);
                                    fclose(archJugadores);
                                    encontrado = 1;
                                }
                            }
                            fclose(archJugadores);
                        }
                        arbolAux = buscarJugador(equipoAux->dato.arbolJugadoresEquipo, nombreJugador); ///Cambiamos el valor del arbolMercado al jugador en el equipo
                        arbolAux->dato.eliminado = 1; ///Le asigna a arbolAux el jugador buscado dentro de la lista de ligas y lo baja
                        printf ("\n  Jugador dado de baja con exito.");
                        system ("pause");
                    }
                } else {
                    printf ("\n  El jugador ya estaba dado de baja.");
                    system ("pause");
                }
            } else {
                printf ("\n  Jugador no encontrado.");
                system ("pause");
            }
        } else {
            printf ("\n  Equipo no encontrado.");
            system ("pause");
        }
    } else {
        printf ("\n  Liga no encontrada.");
        system ("pause");
    }
    return listaLigas;
}

nodoLiga * altaJugador (nodoLiga * listaLigas, nodoArbol ** arbolMercado){
    char nombreLiga[30];
    printf ("Ingreso al menu alta de jugador.\n");
    printf ("  Ingrese liga del jugador a dar de alta: ");
    fflush (stdin);
    gets (nombreLiga);
    nodoLiga * ligaAux = inicListaliga();
    ligaAux = buscarLiga(listaLigas, nombreLiga);
    if (ligaAux!=NULL){
        char nombreEquipo[30];
        printf ("\n  Liga encontrada. Ingrese equipo del jugador a dar de alta: ");
        fflush (stdin);
        gets (nombreEquipo);
        nodoEquipo * equipoAux = iniclistaEquipo();
        equipoAux = buscarEquipo(ligaAux->dato.listaEquipos, nombreEquipo);
        if (equipoAux!=NULL){
            char nombreJugador[30];
            printf ("\n  Equipo encontrado. Ingrese el nombre del jugador a dar de alta: ");
            fflush (stdin);
            gets (nombreJugador);
            nodoArbol * arbolAux = inicArbol();
            arbolAux = buscarJugador (*arbolMercado, nombreJugador);
            if (arbolAux!=NULL){
                if (arbolAux->dato.eliminado==1){
                    char opcion;
                    printf ("\n  Jugador encontrado.");
                    printf ("\n  Esta seguro de que desea darlo de alta? (s para confirmar): ");
                    fflush (stdin);
                    scanf ("%c", &opcion);
                    if (opcion=='s'){
                        arbolAux->dato.eliminado = 0; ///Alta del jugador en el arbolMercado
                        FILE * archJugadores = fopen("Jugadores.dat", "r+b"); ///Alta del jugador en el arch jugadores
                        if (archJugadores!=NULL){
                            jugador jugadorAux;
                            int encontrado = 0;
                            while (fread(&jugadorAux, sizeof(jugador), 1, archJugadores)>0 && encontrado == 0){
                                if (strcmpi(jugadorAux.nombreJugador, nombreJugador)==0){
                                    fseek(archJugadores, sizeof(jugador)*(-1), SEEK_CUR);
                                    jugadorAux.eliminado=0;
                                    fwrite(&jugadorAux, sizeof(jugador), 1, archJugadores);
                                    fclose(archJugadores);
                                    encontrado = 1;
                                }
                            }
                            fclose(archJugadores);
                        }
                        arbolAux = buscarJugador(equipoAux->dato.arbolJugadoresEquipo, nombreJugador); ///Cambiamos el valor del arbolMercado al jugador en el equipo
                        arbolAux->dato.eliminado = 0; ///Le asigna a arbolAux el jugador buscado dentro de la lista de ligas y lo da de alta
                        printf ("\n  Jugador dado de alta con exito.");
                        system ("pause");
                    }
                } else {
                    printf ("\n  El jugador no estaba dado de baja.");
                    system ("pause");
                }
            } else {
                printf ("\n  Jugador no encontrado.");
                system ("pause");
            }
        } else {
            printf ("\n  Equipo no encontrado.");
            system ("pause");
        }
    } else {
        printf ("\n  Liga no encontrada.");
        system ("pause");
    }
    return listaLigas;
}

///Recibe un jugador y lo sobreescribe en el archivo
void reemplazarArchivoJugadores (jugador modificado, char nombreBuscado[]){
    FILE * archJugadores = fopen("Jugadores.dat", "r+b");
    if (archJugadores!=NULL){
        jugador jugadorAux;
        int encontrado = 0;
        while (fread(&jugadorAux, sizeof(jugador), 1, archJugadores)>0 && encontrado == 0){
            if (strcmpi(jugadorAux.nombreJugador, nombreBuscado)==0){
                fseek(archJugadores, sizeof(jugador)*(-1), SEEK_CUR);
                fwrite(&modificado, sizeof(jugador), 1, archJugadores);
                fclose(archJugadores);
                encontrado = 1;
            }
        }
        fclose(archJugadores);
    }
}

nodoLiga * modificarJugador (nodoLiga * listaLigas, nodoArbol ** arbolMercado){
    char nombreLiga[30];
    printf ("Ingreso al menu modificacion de jugador.\n");
    printf ("  Ingrese liga del jugador a dar de modificacion: ");
    fflush (stdin);
    gets (nombreLiga);
    nodoLiga * ligaAux = inicListaliga();
    ligaAux = buscarLiga(listaLigas, nombreLiga);
    if (ligaAux!=NULL){
        char nombreEquipo[30];
        printf ("\n  Liga encontrada. Ingrese equipo del jugador a dar de modificacion: ");
        fflush (stdin);
        gets (nombreEquipo);
        nodoEquipo * equipoAux = iniclistaEquipo();
        equipoAux = buscarEquipo(ligaAux->dato.listaEquipos, nombreEquipo);
        if (equipoAux!=NULL){
            char nombreJugador[30];
            printf ("\n  Equipo encontrado. Ingrese el nombre del jugador a dar de modificacion: ");
            fflush (stdin);
            gets (nombreJugador);
            nodoArbol * arbolAux = inicArbol();
            arbolAux = buscarJugador (*arbolMercado, nombreJugador);
            if (arbolAux!=NULL){
                if (arbolAux->dato.eliminado==0){
                    char opcion;
                    jugador jugadorAux;
                    jugadorAux = arbolAux->dato;
                    printf ("\n\n  Jugador encontrado. Datos: \n ");
                    mostrarJugador(arbolAux->dato);
                    printf ("\n\n  Que campo desea modificar?");
                    printf ("\n  1. Para modificar el nombre del jugador.");
                    printf ("\n  2. Para modificar la nacionalidad del jugador.");
                    printf ("\n  3. Para modificar la calificacion del jugador.");
                    printf ("\n  4. Para modificar el precio del jugador.");
                    printf ("\n  0. Para salir.");
                    printf("\n\n Ingrese la opcion deseada: ");
                    int opc;
                    fflush (stdin);
                    scanf ("%d", &opc);
                    while (opc<0 || opc>4){
                        printf ("\nSe ingreso una opcion incorrecta. Por favor, ingrese una opcion valida: ");
                        fflush (stdin);
                        scanf ("%d", &opc);
                    }
                    switch(opc){
                        case 0:
                            system("cls");
                            break;
                        case 1:
                            system("cls");
                            char nombreViejo[30];
                            strcpy (nombreViejo, arbolAux->dato.nombreJugador); ///Para buscar correctamente al llamar modificar archivo
                            printf ("\n Ingrese el nuevo nombre del jugador: ");
                            fflush (stdin);
                            gets (jugadorAux.nombreJugador);
                            strcpy(arbolAux->dato.nombreJugador, jugadorAux.nombreJugador);
                            arbolAux = buscarJugador(equipoAux->dato.arbolJugadoresEquipo, nombreJugador); ///Cambiamos el valor del arbolMercado al del jugador en el equipo
                            strcpy(arbolAux->dato.nombreJugador, jugadorAux.nombreJugador); ///Le asigna a arbolAux el jugador buscado dentro de la lista de ligas y lo modifica
                            reemplazarArchivoJugadores(jugadorAux, nombreViejo);
                            break;
                        case 2:
                            system("cls");
                            printf ("\n Ingrese la nueva nacionalidad del jugador: ");
                            fflush (stdin);
                            gets (jugadorAux.nacionalidad);
                            strcpy(arbolAux->dato.nacionalidad, jugadorAux.nacionalidad);
                            arbolAux = buscarJugador(equipoAux->dato.arbolJugadoresEquipo, nombreJugador); ///Cambiamos el valor del arbolMercado al del jugador en el equipo
                            strcpy(arbolAux->dato.nacionalidad, jugadorAux.nacionalidad); ///Le asigna a arbolAux el jugador buscado dentro de la lista de ligas y lo modifica
                            reemplazarArchivoJugadores(jugadorAux, jugadorAux.nombreJugador);
                            break;
                        case 3:
                            system("cls");
                            printf ("\n Ingrese la nueva calificacion del jugador: ");
                            fflush (stdin);
                            scanf ("%d", &jugadorAux.calificacion);
                            while (jugadorAux.calificacion<1 || jugadorAux.calificacion>99){
                                printf ("\n Ingrese una calificacion valida (entre 0 y 99): ");
                                scanf ("%d", &jugadorAux.calificacion);
                            }
                            arbolAux->dato.calificacion = jugadorAux.calificacion;
                            arbolAux = buscarJugador(equipoAux->dato.arbolJugadoresEquipo, nombreJugador); ///Cambiamos el valor del arbolMercado al del jugador en el equipo
                            arbolAux->dato.calificacion = jugadorAux.calificacion; ///Le asigna a arbolAux el jugador buscado dentro de la lista de ligas y lo modifica
                            reemplazarArchivoJugadores(jugadorAux, jugadorAux.nombreJugador);
                            break;
                        case 4:
                            system("cls");
                            printf ("\n Ingrese el nuevo precio del jugador: ");
                            fflush (stdin);
                            scanf ("%d", &jugadorAux.precio);
                            while (jugadorAux.precio<100 || jugadorAux.precio>4999999){
                                printf ("\n Ingrese un precio valido (entre 100 y 5.000.000): ");
                                scanf ("%d", &jugadorAux.precio);
                            }
                            arbolAux->dato.precio = jugadorAux.precio;
                            arbolAux = buscarJugador(equipoAux->dato.arbolJugadoresEquipo, nombreJugador); ///Cambiamos el valor del arbolMercado al del jugador en el equipo
                            arbolAux->dato.precio = jugadorAux.precio; ///Le asigna a arbolAux el jugador buscado dentro de la lista de ligas y lo modifica
                            reemplazarArchivoJugadores(jugadorAux, jugadorAux.nombreJugador);
                            break;
                    }
                } else {
                    printf ("\n  El jugador esta dado de baja. Para modificarlo, dirijase al menu alta.");
                    system ("pause");
                }
            } else {
                printf ("\n  Jugador no encontrado.");
                system ("pause");
            }
        } else {
            printf ("\n  Equipo no encontrado.");
            system ("pause");
        }
    } else {
        printf ("\n  Liga no encontrada.");
        system ("pause");
    }
    return listaLigas;
}

nodoLiga * modificaArchJugadores(nodoLiga * listaLigas, nodoArbol ** arbolMercado){
    printf ("Bienvenido al menu modificacion de jugadores.\n A continuacion, debera elegir una opcion:");
    printf ("\n  1. Para dar de baja un jugador.");
    printf ("\n  2. Para dar de alta un jugador.");
    printf ("\n  3. Para modificar un jugador.");
    printf ("\n  0. Para salir.");
    printf("\n\n Ingrese la opcion deseada: ");
    fflush (stdin);
    int opc;
    scanf ("%d", &opc);
    while (opc<0 || opc>3){
        printf ("\nSe ingreso una opcion incorrecta. Por favor, ingrese una opcion valida: ");
        fflush (stdin);
        scanf ("%d", &opc);
    }
    switch(opc){
        case 0:
            system("cls");
            break;
        case 1:
            system("cls");
            listaLigas = bajaJugador(listaLigas, arbolMercado);
            break;
        case 2:
            system("cls");
            listaLigas = altaJugador(listaLigas, arbolMercado);
            break;
        case 3:
            system ("cls");
            listaLigas = modificarJugador(listaLigas, arbolMercado);
            break;
    }
    return listaLigas;
}

/** Carga equipos a su correpondiente lista y archivo.Si no existe el nombre de la liga en los datos del equipo ingresado
se pedira al administrador que cargue la liga no encontrada a la lista de ligas.Caso contrario el equipo ingresado se cargara
directamente al archivo y a la lista**/
nodoLiga * cargaArchEquipos (nodoLiga * listaLigas){
    FILE * archEquipos;
    archEquipos = fopen("Equipos.dat", "ab");
    equipo aux;
    char control='s';
    system("Cls");
    printf ("Ingreso al menu cargar archivo de equipos.");
    while (control=='s'){
        printf ("\n Lectura de datos de equipo:");
        leerEquipo(&aux);
        nodoLiga * listaLigasAuxiliar = buscarLiga(listaLigas, aux.nombreLiga);
        if ((listaLigasAuxiliar)==NULL){
            printf ("\n No se encontro la liga %s. A continuacion debera crearla): ", aux.nombreLiga);
            listaLigas = agregarLigaIndividual(listaLigas); ///Crea la liga y la agrega al final de la lista
            listaLigasAuxiliar = buscarLiga(listaLigas, aux.nombreLiga); ///Actualizo el dato para que no salga igual a NULL
        }
        fwrite(&aux, sizeof(equipo), 1, archEquipos);
        listaLigasAuxiliar->dato.listaEquipos = agregarFinalNodoEquipo(listaLigasAuxiliar->dato.listaEquipos, crearNodoEquipo(aux)); ///Se agrega el equipo a la lista de la liga que corresponde
        printf ("\n Desea ingresar otro equipo? (s para continuar): ");
        fflush (stdin);
        scanf ("%c", &control);
    }
    fclose(archEquipos);
    return listaLigas;
}
///Muestra todos los equipos cargados exitosamente al archivo
void muestraArchEquipos(){
    FILE * archEquipos;
    archEquipos = fopen("Equipos.dat", "rb");
    equipo aux;
    system("Cls");
    printf ("Ingreso al menu mostrar archivo de equipos (el arbol de jugadores dentro del archivo no tiene jugadores).");
    while (fread(&aux, sizeof(equipo), 1, archEquipos)>0){
        printf("\n");
        mostrarEquipo(aux);
    }
    printf ("\n\n");
    system ("Pause");
    fclose(archEquipos);
}
///Carga ligas a su correpondiente lista y archivo.
nodoLiga * cargaArchLigas (nodoLiga * listaLigas){
    FILE * archLigas;
    archLigas = fopen("Ligas.dat", "ab");
    liga aux;
    char control='s';
    system("Cls");
    printf ("Ingreso al menu cargar archivo de ligas.");
    while (control=='s'){
        printf ("\n Lectura de datos de ligas:");
        leerLiga(&aux);
        fwrite(&aux, sizeof(liga), 1, archLigas);
        listaLigas = agregarFinalNodoLiga(listaLigas, crearNodoLiga(aux));
        printf ("\n Desea ingresar otra liga? (s para continuar): ");
        fflush (stdin);
        scanf ("%c", &control);
    }
    fclose(archLigas);
    return listaLigas;
}
///Muestra todos las ligas cargadas exitosamente al archivo
void muestraArchLigas(){
    FILE * archLigas;
    archLigas = fopen("Ligas.dat", "rb");
    liga aux;
    system("Cls");
    printf ("Ingreso al menu mostrar archivo de ligas.");
    while (fread(&aux, sizeof(liga), 1, archLigas)>0){
        printf("\n");
        mostrarLiga(aux);
    }
    printf ("\n\n");
    system ("Pause");
    fclose(archLigas);
}
///Segun la opcion elegida por el administrador carga jugadores al archivo y arbol, o muestra el contenido que hay en ellos
nodoLiga * menuArchJugadores(nodoLiga * listaLigas, nodoArbol ** arbolMercado){
    int opc;
    system("cls");
    printf ("Bienvenido al menu archivo de jugadores.\n A continuacion, debera elegir una opcion:");
    printf ("\n  1. Para cargar archivo de jugadores.");
    printf ("\n  2. Para mostrar archivo de jugadores.");
    printf ("\n  3. Para modificar archivo de jugadores.");
    printf ("\n  0. Para salir.");
    printf("\n\n Ingrese la opcion deseada: ");
    fflush (stdin);
    scanf ("%d", &opc);
    while (opc<0 || opc>3){
        printf ("\nSe ingreso una opcion incorrecta. Por favor, ingrese una opcion valida: ");
        fflush (stdin);
        scanf ("%d", &opc);
    }
    switch(opc){
        case 0:
            system("cls");
            break;
        case 1:
            system("cls");
            listaLigas = cargaArchJugadores(listaLigas, arbolMercado);
            break;
        case 2:
            system("cls");
            muestraArchJugadores();
            break;
        case 3:
            system ("cls");
            listaLigas = modificaArchJugadores(listaLigas, arbolMercado);
    }
    return listaLigas;
}
///Segun la opcion elegida por el administrador carga equipos al archivo y lista, o muestra el contenido que hay en ellos
nodoLiga * menuArchEquipos(nodoLiga * listaLigas){
    int opc;
    system("cls");
    printf ("Bienvenido al menu archivo de equipos.\n A continuacion, debera elegir una opcion:");
    printf ("\n  1. Para cargar archivo de equipos.");
    printf ("\n  2. Para mostrar archivo de equipos.");
    printf ("\n  0. Para salir.");
    printf("\n\n Ingrese la opcion deseada: ");
    fflush (stdin);
    scanf ("%d", &opc);
    while (opc<0 || opc>2){
        printf ("\nSe ingreso una opcion incorrecta. Por favor, ingrese una opcion valida: ");
        fflush (stdin);
        scanf ("%d", &opc);
    }
    switch(opc){
        case 0:
            system("cls");
            break;
        case 1:
            system("cls");
            listaLigas = cargaArchEquipos(listaLigas);
            break;
        case 2:
            system("cls");
            muestraArchEquipos();
            muestraTodosLosEquipos (listaLigas);
            system ("pause");
            break;
    }
    return listaLigas;
}
///Segun la opcion elegida por el administrador carga lisgas al archivo y lista, o muestra el contenido que hay en ellos
void menuArchLigas(nodoLiga * listaLigas){
    int opc;
    system("cls");
    printf ("Bienvenido al menu archivo de ligas.\n A continuacion, debera elegir una opcion:");
    printf ("\n  1. Para cargar archivo de ligas.");
    printf ("\n  2. Para mostrar archivo de ligas.");
    printf ("\n  0. Para salir.");
    printf("\n\n Ingrese la opcion deseada: ");
    fflush (stdin);
    scanf ("%d", &opc);
    while (opc<0 || opc>2){
        printf ("\nSe ingreso una opcion incorrecta. Por favor, ingrese una opcion valida: ");
        fflush (stdin);
        scanf ("%d", &opc);
    }
    switch(opc){
        case 0:
            system("cls");
            break;
        case 1:
            system("cls");
            listaLigas = cargaArchLigas(listaLigas);
            break;
        case 2:
            system("cls");
            muestraArchLigas();
            muestraListaLigas(listaLigas);
            system ("pause");
            break;
    }
}
///Segun la opcion elegida por el administrador nos lleva al menu archivos de: jugadores, equpos o ligas.
nodoLiga * ingresoAdmin (nodoLiga * listaLigas, nodoArbol ** arbolMercado,nodoUsuario * listaUsuarios){
    int opcion;
    system("cls");
    printf ("Bienvenido, Administrador.\n A continuacion, debera elegir una opcion:");
    printf ("\n  1. Para menu archivo de jugadores.");
    printf ("\n  2. Para menu archivo de equipos.");
    printf ("\n  3. Para menu archivo de ligas.");
    printf ("\n  4. Para mostrar arbol de mercado.");
    printf ("\n  0. Para salir.");
    printf ("\n\n Ingrese la opcion deseada: ");
    fflush (stdin);
    scanf ("%d", &opcion);
    while (opcion<0 || opcion>4){
        printf ("\nSe ingreso una opcion incorrecta. Por favor, ingrese una opcion valida: ");
        fflush (stdin);
        scanf ("%d", &opcion);
    }
    switch (opcion){
        case 0:
            system("cls");
            ejecutarMenu(listaLigas, *arbolMercado,listaUsuarios);
            break;
        case 1:
            listaLigas = menuArchJugadores(listaLigas, arbolMercado);
            listaLigas = ingresoAdmin(listaLigas, arbolMercado,listaUsuarios);
            break;
        case 2:
            listaLigas = menuArchEquipos(listaLigas);
            listaLigas = ingresoAdmin(listaLigas, arbolMercado,listaUsuarios);
            break;
        case 3:
            menuArchLigas(listaLigas);
            listaLigas = ingresoAdmin(listaLigas, arbolMercado,listaUsuarios);
            break;
        case 4:
            printf ("\n  Arbol Mercado:");
            mostrarInOrder(*arbolMercado);
            printf ("\n\n");
            system ("pause");
            listaLigas = ingresoAdmin(listaLigas, arbolMercado,listaUsuarios);
            break;
    }
    return listaLigas;
}
/**Pide al administrador la contraseña. Si este ingresa una opcion incorrecta da dos intentos mas para que pueda ingresar
 la correcta,si vuelve a fallar en los dos intentos el programa termina.Si el administrador ingresa la contraseña correcta
 se invoca a la funcion "ingresoAdmin"**/
nodoLiga * menuAdministrador(nodoLiga * listaLigas, nodoArbol ** arbolMercado,nodoUsuario * listaUsuarios){
    char pass[20];
    system("cls");
    printf ("Ingreso al Menu Administrador.");
    printf ("\n Ingrese password: ");
    fflush (stdin);
    gets (pass);
    if (strcmp (pass, password)==0){
        listaLigas = ingresoAdmin (listaLigas, arbolMercado,listaUsuarios);
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
                listaLigas = ingresoAdmin (listaLigas, arbolMercado,listaUsuarios);
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
