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
    }
    return rta.ID;
}

///retorna la ultima ID del jugador cargado
int buscarIDultimo(){
 int id=-1;
 jugador a;
 FILE * archi =fopen("Jugadores.dat","rb");
 if(archi!=NULL)
 {
  fseek(archi,-1*sizeof(jugador),SEEK_END);
  fread(&a,sizeof(jugador),1,archi);
  id = a.ID;
 }
 fclose(archi);
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
    } else {
        printf ("\n\n El jugador %s esta dado de baja (eliminado=1).", aux.nombreJugador);
    }
}

nodoArbol * inicArbol(){
    return NULL;
}

nodoArbol* crearNodoArbolJug(int ID){
    nodoArbol* aux=(nodoArbol*)malloc(sizeof(nodoArbol));
    aux->datoID=ID;
    aux->der=NULL;
    aux->izq=NULL;
    return aux;
}

/**Inserta los datos del jugador cargado en el arbol segun su campo de calificacion**/
nodoArbol* insertarArbol(nodoArbol* a,int ID){
    if(a==NULL){
        a=crearNodoArbolJug(ID);
    }else{
        if(a->datoID>=ID){
            a->izq=insertarArbol(a->izq,ID);
        }else{
            a->der=insertarArbol(a->der,ID);
        }
    }

    return a;
}
/**Pasa los datos de los jugadores cargados del archivo al arreglo de jugadores**/
void cargarArregloJugador(int arregloID[],char nombreEquipo[]){
    FILE* archi=fopen("Jugadores.dat","rb");
    if(archi!=NULL){
        jugador aux;
        while(fread(&aux,sizeof(jugador),1,archi)>0){
            if(strcmpi(aux.nombreEquipo,nombreEquipo) == 0){
                arregloID[buscarValido(arregloID)] = aux.ID;
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
        while(fread(&aux,sizeof(jugador),1,arch)>0 && encontrado == 0){
            if(ID == aux.ID){
                encontrado = 1;
            }
        }
    }
    return aux; ///Siempre va a encontrarlo, porque los ID se cargan en el archivo y no se modifican
}

///Muestra el contenido del arbol de jugadores **/
nodoArbol* mostrarInOrder(nodoArbol* a){
    if(a!=NULL){
        mostrarInOrder(a->der);
        mostrarJugador(buscaIDArch(a->datoID));
        mostrarInOrder(a->izq);
    }
}
///Carga todos los jugadores del archivo al arbol del mercado
nodoArbol * crearArbolMercado (nodoArbol * arbol){
    FILE * archJugadores = fopen("Jugadores.dat", "rb");
    if (archJugadores!=NULL){
        jugador aux;
        while (fread(&aux, sizeof(jugador), 1, archJugadores)>0){
            arbol=insertarArbol(arbol, aux.ID);
        }
    }
    fclose(archJugadores);
    return arbol;
}

///Busca jugador en el arbol
int buscarJugador(nodoArbol * arbol,int ID){
    int rta=0;
    if (arbol!=NULL){
        if (arbol->datoID > ID){
            rta = buscarJugador(arbol->izq, ID);
        } else{
            if (arbol->datoID < ID){
                rta = buscarJugador(arbol->der, ID);
            } else {
                rta=1;
            }
        }
    }
    return rta;
}

int buscarValidos(int arregloID[]){
int i= 0;
while(arregloID[i] == -1 && i<MAXJugadores){
 i++;
}
return i;
}

void mostrarArregloID (int arreglo[], int validos){
    for (int i=0; i<validos; i++){
        mostrarJugador(buscaIDArch(arreglo[i]));
    }
}

