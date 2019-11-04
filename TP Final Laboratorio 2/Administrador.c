#include "Administrador.h"
/** Carga jugadores a su correpondiente archivo y arbol.Si el nombre de liga o equipo ingresado en los datos del jugador no se
encuentra en la lista de ligas o equipos se pedira al administrador que cargue la liga o el equipo no encontrado.Caso contrario
el jugador ingresado se cargara directamente al arbol y archivo**/

nodoLiga * cargaArchJugadores(nodoLiga * listaLigas){
    FILE * archJug;
    archJug = fopen("Jugadores.dat", "ab");
    jugador aux;
    char control='s';
    system("Cls");
    printf ("Ingreso al menu cargar archivo de jugadores.");
    while (control=='s'){
        printf ("\n Lectura de datos de jugador:");
        leerJugador(&aux);
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
        system ("cls");
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
///Segun la opcion elegida por el administrador carga jugadores al archivo y arbol, o muestra el contenido que hay en ellos
nodoLiga * menuArchJugadores(nodoLiga * listaLigas){
    int opc;
    system("cls");
    printf ("Bienvenido al menu archivo de jugadores.\n A continuacion, debera elegir una opcion:");
    printf ("\n  1. Para cargar archivo de jugadores.");
    printf ("\n  2. Para mostrar archivo de jugadores.");
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
            listaLigas = cargaArchJugadores(listaLigas);
            break;
        case 2:
            system("cls");
            muestraArchJugadores();
            break;
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
nodoLiga * ingresoAdmin (nodoLiga * listaLigas){
    int opcion;
    system("cls");
    printf ("Bienvenido, Administrador.\n A continuacion, debera elegir una opcion:");
    printf ("\n  1. Para menu archivo de jugadores.");
    printf ("\n  2. Para menu archivo de equipos.");
    printf ("\n  3. Para menu archivo de ligas.");
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
        case 0:
            system("cls");
            ejecutarMenu(listaLigas);
            break;
        case 1:
            listaLigas = menuArchJugadores(listaLigas);
            listaLigas = ingresoAdmin(listaLigas);
            break;
        case 2:
            listaLigas = menuArchEquipos(listaLigas);
            listaLigas = ingresoAdmin(listaLigas);
            break;
        case 3:
            menuArchLigas(listaLigas);
            listaLigas = ingresoAdmin(listaLigas);
            break;
    }
    return listaLigas;
}
/**Pide al administrador la contraseña. Si este ingresa una opcion incorrecta da dos intentos mas para que pueda ingresar
 la correcta,si vuelve a fallar en los dos intentos el programa termina.Si el administrador ingresa la contraseña correcta
 se invoca a la funcion "ingresoAdmin"**/
nodoLiga * menuAdministrador(nodoLiga * listaLigas){
    char pass[20];
    system("cls");
    printf ("Ingreso al Menu Administrador.");
    printf ("\n Ingrese password: ");
    fflush (stdin);
    gets (pass);
    if (strcmp (pass, password)==0){
        listaLigas = ingresoAdmin (listaLigas);
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
                listaLigas = ingresoAdmin (listaLigas);
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
