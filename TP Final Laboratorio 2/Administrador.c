#include "Administrador.h"

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
}

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
