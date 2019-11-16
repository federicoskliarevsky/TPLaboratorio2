#include "Jugador.h"

jugador buscarJugadorArchivo(jugador buscado){
    FILE * archJug;
    jugador encontrado;
    encontrado.ID = -1;
    archJug = fopen("Jugadores.dat", "rb");
    jugador aux;
    while (fread(&aux, sizeof(jugador), 1, archJug)>0 && encontrado.ID==-1){
        if (strcmpi(aux.nombreLiga, buscado.nombreLiga)==0 && strcmpi(aux.nombreEquipo, buscado.nombreEquipo)==0 && strcmpi(aux.nombreJugador, buscado.nombreJugador)==0){
            encontrado = aux;
        }
    }
    fclose(archJug);
    return encontrado;
}

void crearArregloID (int arregloID[]){
    for (int i=0; i<MAXJugadores; i++){
        arregloID[i]=-1;
   }
}

///Lee los datos de la estructura jugador para luego cargarlos al archivo. Devuelve -1 si el leido es nuevo en el arch. Se invoca en la foncion "cargaArchJugadores"
int leerJugador(jugador * nuevo){
    printf ("\n Ingrese el nombre del jugador: ");
    fflush (stdin);
    gets (nuevo->nombreJugador);
    printf (" Ingrese nombre del equipo: ");
    fflush (stdin);
    gets (nuevo->nombreEquipo);
    printf (" Ingrese nombre de liga: ");
    fflush (stdin);
    gets (nuevo->nombreLiga);
    printf (" Ingrese nacionalidad: ");
    fflush (stdin);
    gets (nuevo->nacionalidad);
    printf (" Ingrese calificacion (entre 1 y 99): ");
    fflush (stdin);
    scanf ("%d", &(nuevo->calificacion));
    while (nuevo->calificacion<1 || nuevo->calificacion>99){
        printf ("\n Ingrese una calificacion valida: ");
        scanf ("%d", &(nuevo->calificacion));
    }
    printf (" Ingrese precio (entre 100 y 5.000.000): ");
    fflush (stdin);
    scanf ("%d", &(nuevo->precio));
    while (nuevo->precio<0 || nuevo->precio>4999999){
        printf ("\n Ingrese un precio valido: ");
        scanf ("%d", &(nuevo->precio));
    }
    nuevo->eliminado = 0;
    jugador rta = buscarJugadorArchivo(*nuevo);
    if(rta.ID==-1) ///Si el jugador no esta
    {
        nuevo->ID = buscarIDultimo()+1;
        printf (" ID asignado: %d.\n\n", nuevo->ID);
        system("pause");
    }
    return rta.ID;
}

///retorna la ultima ID del jugador cargado
int buscarIDultimo(){
    int id=-1;
    jugador a;
    FILE * archi =fopen("Jugadores.dat","rb");
    if(archi!=NULL){
        fseek(archi,-1*sizeof(jugador),SEEK_END);
        if (fread(&a,sizeof(jugador),1,archi)>0){
            id = a.ID;
        }
    }
    fclose(archi);
    ///printf ("Se devolvera el ID %d", id);
    return id;
}

///Printea todos los datos de la estructura jugador
void mostrarJugador(jugador aux){
    if (aux.eliminado==0){
        printf ("\n\n Jugador: ");
        puts (aux.nombreJugador);
        printf (" Equipo: ");
        puts (aux.nombreEquipo);
        printf (" Liga: ");
        puts (aux.nombreLiga);
        printf (" Nacionalidad: ");
        puts (aux.nacionalidad);
        printf (" Calificacion: %d", aux.calificacion);
        printf ("\n Precio: %d", aux.precio);
        printf ("\n ID: %d", aux.ID);
    } else {
        printf ("\n\n El jugador %s esta dado de baja (eliminado=1).", aux.nombreJugador);
    }
}

nodoMercado * iniclistaMercado(){
    return NULL;
}

nodoMercado * crearNodoMercado(int ID){
    nodoMercado * aux=(nodoMercado*) malloc(sizeof(nodoMercado));
    aux->datoID = ID;
    aux->sig = NULL;
    return aux;
}

/**Inserta los datos del jugador cargado en el arbol segun su campo de calificacion**/
nodoMercado * agregarFinalNodoMercado(nodoMercado * lista,int ID){
    nodoMercado * a = crearNodoMercado(ID);
    if(lista==NULL){
        lista = a;
    }else{
        nodoMercado * ultimo = buscarUltimoMercado(lista);
        ultimo->sig = a;
    }

    return lista;
}

nodoMercado * buscarUltimoMercado(nodoMercado * lista){
 nodoMercado * seg = lista;
 if(seg!=NULL)
 {
  while(seg->sig != NULL)
  {
   seg = seg->sig;
  }
 }
 return seg;
}


/**Pasa los datos de los jugadores cargados del archivo al arreglo de jugadores**/
void cargarArregloJugador(int arregloID[],char nombreEquipo[]){
    FILE* archi=fopen("Jugadores.dat","rb");
    if(archi!=NULL){
        jugador aux;
        while(fread(&aux,sizeof(jugador),1,archi)>0){
            if(strcmpi(aux.nombreEquipo,nombreEquipo) == 0){
                arregloID[buscarValidos(arregloID)] = aux.ID;
            }
    }
    }
    fclose(archi);
}

jugador buscaIDArch(int ID){
    FILE * arch = fopen("Jugadores.dat","rb");
    jugador aux;
    if(arch!=NULL){
        int encontrado = 0;
        while(encontrado == 0 && fread(&aux,sizeof(jugador),1,arch)>0){
            if(ID == aux.ID){
                encontrado = 1;
            }
        }
    }
    return aux; ///Siempre va a encontrarlo, porque los ID se cargan en el archivo y no se modifican
}


///Carga todos los jugadores del archivo al arbol del mercado
nodoMercado * cargarListaMercado (nodoMercado * lista){
    FILE * archJugadores = fopen("Jugadores.dat", "rb");
    if (archJugadores!=NULL){
        jugador aux;
        while (fread(&aux, sizeof(jugador), 1, archJugadores)>0){
            lista = agregarFinalNodoMercado(lista,aux.ID);
        }
    }
    fclose(archJugadores);
    return lista;
}

///Busca jugador en la lista
int buscarJugador(nodoMercado * lista,int ID){
    int rta=0;
    while(lista!=NULL){
        if (lista->datoID == ID){
            rta = 1;
        }
        lista = lista ->sig;
        }
   return rta;
}

int buscarValidos(int arregloID[]){
    int j=0;
    for (int i=0; i<MAXJugadores; i++){
        if (arregloID[i]!=-1){
            j++;
        }
    }
    return j;
}

void mostrarArregloID (int arreglo[], int validos){
    for (int i=0; i<validos; i++){
        mostrarJugador(buscaIDArch(arreglo[i]));
    }
}

