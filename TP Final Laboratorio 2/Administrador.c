#include "Administrador.h"

/** Carga jugadores a su correpondiente archivo y arregloID.Si el nombre de liga o equipo ingresado en los datos del jugador no se
encuentra en la lista de ligas o equipos se pedira al administrador que cargue la liga o el equipo no encontrado.Si el id del
jugador ingresado ya existe no se podra cargar ni al archivo ni al arreglo**/
nodoLiga * cargaArchJugadores(nodoLiga * listaLigas,nodoMercado * listaMercado){
    jugador aux;
    char control='s';
    FILE * archJug;
    system("Cls");
    printf ("Ingreso al menu cargar archivo de jugadores.");
    while (control=='s'){
        printf ("\n Lectura de datos de jugador:");
        if (leerJugador(&aux)==-1){ ///Si el jugador ingresado no se encuentra en el archivo
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
            listaLigasAuxiliar = buscarLiga(listaLigas, aux.nombreLiga); ///Actualizamos las listas con los datos cargados
            if (listaLigasAuxiliar!=NULL){
                listaEquiposAuxiliar = buscarEquipo(listaLigasAuxiliar->dato.listaEquipos, aux.nombreEquipo);
            }
            if (listaLigasAuxiliar!=NULL && listaEquiposAuxiliar!=NULL){
                int validos = buscarValidos(listaEquiposAuxiliar->dato.arregloID, 1);
                if (validos<MAXJugadores){
                    archJug = fopen("Jugadores.dat", "ab");
                    if (archJug!=NULL){
                        fwrite(&aux, sizeof(jugador), 1, archJug);
                        fclose(archJug);
                    } else {
                        printf ("\n  Error de apertura en el archivo Jugadores.dat");
                    }
                    listaEquiposAuxiliar->dato.arregloID[validos] = aux.ID ;
                    actualizaArchEquipos (aux);
                    listaMercado =agregarFinalNodoMercado(listaMercado,aux.ID);
                } else {
                    printf ("El jugador %s no pudo ser cargado al equipo %s porque ya tiene %d jugadores.\n", aux.nombreJugador, aux.nombreEquipo, MAXJugadores);
                    printf ("Si desea, puede modificar uno de los jugadores del equipo desde el menu Modificacion.\n");
                    system ("pause");
                }
                system ("cls");
            } else {
                printf (" El jugador %s no pudo ser cargado porque la liga o el equipo cargados no coinciden con los creados.\n", aux.nombreJugador);
            }
        } else {
            printf ("\n Jugador ya ingresado.");
        }
        printf ("\n Desea ingresar otro jugador? (s para continuar): ");
        fflush (stdin);
        scanf ("%c", &control);
    }
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

nodoLiga * bajaJugador (nodoLiga * listaLigas){
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
            jugador jugAux;
            strcpy(jugAux.nombreEquipo, nombreEquipo);
            strcpy(jugAux.nombreJugador, nombreJugador);
            strcpy(jugAux.nombreLiga, nombreLiga);
            jugador jugEncontrado = buscarJugadorArchivo(jugAux);
            if (jugEncontrado.ID != -1){
                if (jugEncontrado.eliminado==0){
                    char opcion;
                    printf ("\n  Jugador encontrado. Datos: ");
                    mostrarJugador(jugEncontrado);
                    printf ("\n  Esta seguro de que desea eliminarlo? (s para confirmar): ");
                    fflush (stdin);
                    scanf ("%c", &opcion);
                    if (opcion=='s'){
                        FILE * archJugadores = fopen("Jugadores.dat", "r+b"); ///Baja el jugador en el arch jugadores
                        if (archJugadores!=NULL){
                            jugador jugadorAux;
                            int encontrado = 0;
                            while (fread(&jugadorAux, sizeof(jugador), 1, archJugadores)>0 && encontrado == 0){
                                if (jugadorAux.ID == jugEncontrado.ID){
                                    fseek(archJugadores, sizeof(jugador)*(-1), SEEK_CUR);
                                    jugadorAux.eliminado=1;
                                    fwrite(&jugadorAux, sizeof(jugador), 1, archJugadores);
                                    fclose(archJugadores);
                                    encontrado = 1;
                                }
                            }
                            fclose(archJugadores);
                        }
                        printf ("\n  Jugador dado de baja con exito.\n");
                        system ("pause");
                    }
                } else {
                    printf ("\n  El jugador ya estaba dado de baja.\n");
                    system ("pause");
                }
            } else {
                printf ("\n  Jugador no encontrado.\n");
                system ("pause");
            }
        } else {
            printf ("\n  Equipo no encontrado.\n");
            system ("pause");
        }
    } else {
        printf ("\n  Liga no encontrada.\n");
        system ("pause");
    }
    return listaLigas;
}

nodoLiga * altaJugador (nodoLiga * listaLigas){
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
            jugador jugAux;
            strcpy(jugAux.nombreEquipo, nombreEquipo);
            strcpy(jugAux.nombreJugador, nombreJugador);
            strcpy(jugAux.nombreLiga, nombreLiga);
            jugador jugEncontrado = buscarJugadorArchivo(jugAux);
            if (jugEncontrado.ID != -1){
                if (jugEncontrado.eliminado==1){
                    char opcion;
                    printf ("\n  Jugador encontrado. Datos: ");
                    mostrarJugador(jugEncontrado);
                    printf ("\n  Esta seguro de que desea darlo de alta? (s para confirmar): ");
                    fflush (stdin);
                    scanf ("%c", &opcion);
                    if (opcion=='s'){
                        FILE * archJugadores = fopen("Jugadores.dat", "r+b"); ///Da de alta el jugador en el arch jugadores
                        if (archJugadores!=NULL){
                            jugador jugadorAux;
                            int encontrado = 0;
                            while (fread(&jugadorAux, sizeof(jugador), 1, archJugadores)>0 && encontrado == 0){
                                if (jugadorAux.ID == jugEncontrado.ID){
                                    fseek(archJugadores, sizeof(jugador)*(-1), SEEK_CUR);
                                    jugadorAux.eliminado=0;
                                    fwrite(&jugadorAux, sizeof(jugador), 1, archJugadores);
                                    fclose(archJugadores);
                                    encontrado = 1;
                                }
                            }
                            fclose(archJugadores);
                        }
                        printf ("\n  Jugador dado de alta con exito.");
                        system ("pause");
                    }
                } else {
                    printf ("\n  El jugador ya estaba dado de alta.");
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

nodoLiga * modificarJugador (nodoLiga * listaLigas){///falta cambiar la funcion para el arreglo
    char nombreLiga[30];
    printf ("Ingreso al menu modificacion de jugador.\n");
    printf ("  Ingrese liga del jugador a dar de modificacion: ");
    fflush (stdin);
    gets (nombreLiga);
    nodoLiga * ligaAux = inicListaliga();
    ligaAux = buscarLiga(listaLigas, nombreLiga);
    if (ligaAux!=NULL){
        char nombreEquipo[30];
        printf ("\n  Liga encontrada. Ingrese equipo del jugador a modificar: ");
        fflush (stdin);
        gets (nombreEquipo);
        nodoEquipo * equipoAux = iniclistaEquipo();
        equipoAux = buscarEquipo(ligaAux->dato.listaEquipos, nombreEquipo);
        if (equipoAux!=NULL){
            char nombreJugador[30];
            printf ("\n  Equipo encontrado. Ingrese el nombre del jugador a modificar: ");
            fflush (stdin);
            gets (nombreJugador);
            jugador jugAux;
            strcpy(jugAux.nombreEquipo, nombreEquipo);
            strcpy(jugAux.nombreJugador, nombreJugador);
            strcpy(jugAux.nombreLiga, nombreLiga);
            jugador jugEncontrado = buscarJugadorArchivo(jugAux);
            if (jugEncontrado.ID != -1){
                if (jugEncontrado.eliminado==0){
                    char opcion;
                    printf ("\n\n  Jugador encontrado. Datos: \n ");
                    mostrarJugador(jugEncontrado);
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
                            strcpy (nombreViejo,jugEncontrado.nombreJugador); ///Para buscar correctamente al llamar modificar archivo
                            printf ("\n Ingrese el nuevo nombre del jugador: ");
                            fflush (stdin);
                            gets (jugEncontrado.nombreJugador);
                            reemplazarArchivoJugadores(jugEncontrado, nombreViejo);
                            break;
                        case 2:
                            system("cls");
                            printf ("\n Ingrese la nueva nacionalidad del jugador: ");
                            fflush (stdin);
                            gets (jugEncontrado.nacionalidad);
                            reemplazarArchivoJugadores(jugEncontrado, jugEncontrado.nombreJugador);
                            break;
                        case 3:
                            system("cls");
                            printf ("\n Ingrese la nueva calificacion del jugador: ");
                            fflush (stdin);
                            scanf ("%d", &jugEncontrado.calificacion);
                            while (jugEncontrado.calificacion<1 || jugEncontrado.calificacion>99){
                                printf ("\n Ingrese una calificacion valida (entre 0 y 99): ");
                                scanf ("%d", &jugEncontrado.calificacion);
                            }
                            reemplazarArchivoJugadores(jugEncontrado, jugEncontrado.nombreJugador);
                            break;
                        case 4:
                            system("cls");
                            printf ("\n Ingrese el nuevo precio del jugador: ");
                            fflush (stdin);
                            scanf ("%d", &jugEncontrado.precio);
                            while (jugEncontrado.precio<100 || jugEncontrado.precio>4999999){
                                printf ("\n Ingrese un precio valido (entre 100 y 5.000.000): ");
                                scanf ("%d", &jugEncontrado.precio);
                            }
                            reemplazarArchivoJugadores(jugEncontrado, jugEncontrado.nombreJugador);
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

nodoLiga * modificaArchJugadores(nodoLiga * listaLigas,nodoMercado * listaMercado){
    printf ("Bienvenido al menu modificacion de jugadores.\n Opciones disponibles:");
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
            listaLigas = bajaJugador(listaLigas);
            break;
        case 2:
            system("cls");
            listaLigas = altaJugador(listaLigas);
            break;
        case 3:
            system ("cls");
            listaLigas = modificarJugador(listaLigas);
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
            printf ("\n No se encontro la liga %s. A continuacion debera crearla: ", aux.nombreLiga);
            listaLigas = agregarLigaIndividual(listaLigas); ///Crea la liga y la agrega al final de la lista
            listaLigasAuxiliar = buscarLiga(listaLigas, aux.nombreLiga); ///Actualizo el dato para que no salga igual a NULL
        }
        if (listaLigasAuxiliar!=NULL){
            fwrite(&aux, sizeof(equipo), 1, archEquipos);
            listaLigasAuxiliar->dato.listaEquipos = agregarFinalNodoEquipo(listaLigasAuxiliar->dato.listaEquipos, crearNodoEquipo(aux)); ///Se agrega el equipo a la lista de la liga que corresponde
        } else {
            printf ("\n La liga agregada no coincide con la del equipo leido. El equipo no pudo ser cargado.");
        }
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
    printf ("Ingreso al menu mostrar archivo de equipos.");
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

///Segun la opcion elegida por el administrador carga jugadores al archivo, modifica la informacion de los ya cargados o muestra
///el contenido que hay en ellos
nodoLiga * menuArchJugadores(nodoLiga * listaLigas,nodoMercado * listaMercado){
    int opc;
    system("cls");
    printf ("Bienvenido al menu archivo de jugadores.\n Opciones disponibles:");
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
            listaLigas = cargaArchJugadores(listaLigas,listaMercado);
            break;
        case 2:
            system("cls");
            muestraArchJugadores();
            break;
        case 3:
            system ("cls");
            listaLigas = modificaArchJugadores(listaLigas, listaMercado);
    }
    return listaLigas;
}

///Segun la opcion elegida por el administrador carga equipos al archivo y lista, o muestra el contenido que hay en ellos
nodoLiga * menuArchEquipos(nodoLiga * listaLigas){
    int opc;
    system("cls");
    printf ("Bienvenido al menu archivo de equipos.\n Opciones disponibles:");
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
nodoLiga * menuArchLigas(nodoLiga * listaLigas){
    int opc;
    system("cls");
    printf ("Bienvenido al menu archivo de ligas.\n Opciones disponibles:");
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
    return listaLigas;
}

///Funcion recursiva que devuelve la suma de las calificaciones de los jugadores no eliminados del mercado
float sumaMercado (nodoMercado * listaMercado){
    float rta=0;
    if (listaMercado!=NULL){
        jugador aux = buscaIDArch(listaMercado->datoID);
        if (aux.eliminado==0){
            rta = aux.calificacion;
        }
        rta += sumaMercado(listaMercado->sig);
    }
    return rta;
}

///Funcion recursiva que devuelve la cantidad de nodos con información de los jugadores no eliminados del mercado
float cantidadMercado (nodoMercado * listaMercado){
    int rta=0;
    if (listaMercado!=NULL){
        if (buscaIDArch(listaMercado->datoID).eliminado==0){
            rta = 1;
        }
        rta += cantidadMercado(listaMercado->sig);
    }
    return rta;
}

///Funcion que devuelve el promedio de las calificaciones de los jugadores no eliminados del mercado
float promedioMercado (nodoMercado * listaMercado){
    float promedio=0;
    if (listaMercado!=NULL){
        promedio = (float)(sumaMercado(listaMercado)/cantidadMercado(listaMercado));
    }
    return promedio;
}

///Inserta un entero (lo usamos para la calificación) ordenado en un arreglo, de menor a mayor
void insertar (int a[], int u, int dato){
    int i=u;
    while (i>=0 && dato<a[i]){
        a[i+1] = a[i];
        i--;
    }
    a[i+1]=dato;
}

///Devuelve la mediana de las calificaciones de los jugadores no eliminados del mercado. Si no hay datos, devuelve 0.
float medianaMercado (nodoMercado * listaMercado){
    float rta = 0;
    if (listaMercado!=NULL){
        int validos = cantidadMercado(listaMercado);
        if (validos>0){
            int arreglo[validos];
            for (int i=0; i<validos; i++){
                while (listaMercado!=NULL && buscaIDArch(listaMercado->datoID).eliminado==1){
                    listaMercado = listaMercado->sig;
                }
                if (listaMercado!=NULL){
                    insertar (arreglo, i, buscaIDArch(listaMercado->datoID).calificacion);
                }
            }
            if ((validos%2)!=0){
                rta = (arreglo[validos/2]+arreglo[(validos/2)+1])/2;
            } else {
                rta = arreglo[validos/2];
            }
        }
    }
    return rta;
}


///Devuelve el ID del jugador no eliminado con la mayor calificacion (si hay dos o mas con la misma, igual devuelve uno solo).
int mayorCalificacion (nodoMercado * listaMercado){
    int rta=-1;
    if (listaMercado!=NULL){
        rta = listaMercado->datoID;
        listaMercado = listaMercado->sig;
        while (listaMercado!=NULL){
            if ((buscaIDArch(listaMercado->datoID).eliminado== 0) && (buscaIDArch(rta).calificacion < buscaIDArch(listaMercado->datoID).calificacion)){
                rta = listaMercado->datoID;
            }
            listaMercado = listaMercado->sig;
        }
    }
    return rta;
}

///Devuelve el ID del jugador no eliminado con la menor calificacion (si hay dos o mas con la misma, igual devuelve uno solo).
int menorCalificacion (nodoMercado * listaMercado){
    int rta=-1;
    if (listaMercado!=NULL){
        rta = listaMercado->datoID;
        listaMercado = listaMercado->sig;
        while (listaMercado!=NULL){
            if (buscaIDArch(listaMercado->datoID).eliminado== 0 && buscaIDArch(rta).calificacion > buscaIDArch(listaMercado->datoID).calificacion){
                rta = listaMercado->datoID;
            }
            listaMercado = listaMercado->sig;
        }
    }
    return rta;
}

///Muestra a los jugadores con la mayor calificacion y con la menor calificacion (si hay dos o mas con la misma, igual muestra uno solo).
void mayorMenorMercado (nodoMercado * listaMercado){
    int ID = mayorCalificacion(listaMercado);
    jugador aux;
    if (ID!=-1){
        aux = buscaIDArch(ID);
        printf ("\n Jugador con mayor calificacion: %s (calificacion: %d).", aux.nombreJugador, aux.calificacion);
    }
    ID = menorCalificacion(listaMercado);
    if (ID!=-1){
        aux = buscaIDArch(ID);
        printf ("\n Jugador con menor calificacion: %s (calificacion:%d).", aux.nombreJugador, aux.calificacion);
    }
}

///Muestra la media, mediana y dispersion de las calificaciones de los jugadores en el mercado.
void estadisticasMercado (nodoMercado * listaMercado){
    system("cls");
    printf ("Menu estadisticas del Mercado. Estadisticas basadas en las calificaciones de los jugadores no eliminados:");
    if (listaMercado!=NULL){
        printf ("\n  Media: %.2f\n", promedioMercado(listaMercado));
        printf ("\n  Mediana: %.2f\n", medianaMercado(listaMercado));
        mayorMenorMercado (listaMercado);
    } else {
        printf ("\n No hay datos en el mercado.");
    }
    printf ("\n\n");
    system ("pause");
}

///Segun la opcion elegida por el administrador nos lleva al menu archivos de: jugadores, equpos o ligas.
nodoLiga * ingresoAdmin (nodoLiga * listaLigas, nodoMercado * listaMercado,nodoUsuario * listaUsuarios){
    int opcion;
    system("cls");
    printf ("Bienvenido, Administrador.\n Opciones disponibles:");
    printf ("\n  1. Para menu archivo de jugadores.");
    printf ("\n  2. Para menu archivo de equipos.");
    printf ("\n  3. Para menu archivo de ligas.");
    printf ("\n  4. Para mostrar lista de mercado.");
    printf ("\n  5. Para mostrar estadisticas de mercado.");
    printf ("\n  0. Para salir.");
    printf ("\n\n Ingrese la opcion deseada: ");
    fflush (stdin);
    scanf ("%d", &opcion);
    while (opcion<0 || opcion>5){
        printf ("\nSe ingreso una opcion incorrecta. Por favor, ingrese una opcion valida: ");
        fflush (stdin);
        scanf ("%d", &opcion);
    }
    switch (opcion){
        case 0:
            system("cls");
            ejecutarMenu(listaLigas,listaMercado,listaUsuarios);
            break;
        case 1:
            listaLigas = menuArchJugadores(listaLigas, listaMercado);
            listaLigas = ingresoAdmin(listaLigas, listaMercado,listaUsuarios);
            break;
        case 2:
            listaLigas = menuArchEquipos(listaLigas);
            listaLigas = ingresoAdmin(listaLigas, listaMercado,listaUsuarios);
            break;
        case 3:
            listaLigas = menuArchLigas(listaLigas);
            listaLigas = ingresoAdmin(listaLigas, listaMercado,listaUsuarios);
            break;
        case 4:
            printf ("\n  Lista Mercado:");
            MostrarMercado(listaMercado, 0);
            printf ("\n\n");
            system ("pause");
            listaLigas = ingresoAdmin(listaLigas, listaMercado ,listaUsuarios);
            break;
        case 5:
            estadisticasMercado (listaMercado);
            listaLigas = ingresoAdmin(listaLigas, listaMercado,listaUsuarios);
            break;
    }
    return listaLigas;
}

/**Pide al administrador la contraseña. Si este ingresa una opcion incorrecta da dos intentos mas para que pueda ingresar
 la correcta,si vuelve a fallar en los dos intentos el programa termina.Si el administrador ingresa la contraseña correcta
 se invoca a la funcion "ingresoAdmin"**/
nodoLiga * menuAdministrador(nodoLiga * listaLigas,nodoMercado * listaMercado,nodoUsuario * listaUsuarios){
    char pass[20];
    system("cls");
    printf ("Ingreso al Menu Administrador.");
    printf ("\n Ingrese la contrase%ca: ", 164);
    fflush (stdin);
    gets (pass);
    if (strcmp (pass, password)==0){
        listaLigas = ingresoAdmin (listaLigas,listaMercado,listaUsuarios);
    } else {
        int intentos=2;
        printf (" Password incorrecta. Intentos restantes: %d.", intentos);
        int seguirIntentando=1;
        while (intentos>0 && seguirIntentando==1){
            printf ("\n Ingrese la contrase%ca: ", 164);
            fflush (stdin);
            gets (pass);
            if (strcmp (pass, password)==0){
                seguirIntentando=0;
                listaLigas = ingresoAdmin (listaLigas,listaMercado,listaUsuarios);
            } else {
                intentos--;
                printf (" Password incorrecta.");
                if (intentos>0){
                    printf (" Intentos restantes: %d.", intentos);
                } else {
                    printf (" No le quedan mas intentos.\n");
                    system ("pause");
                    system("cls");
                    ejecutarMenu(listaLigas,listaMercado,listaUsuarios);
                }
            }
        }
    }
    return listaLigas;
}
