#include "Jugador.h"

int buscarJugadorArchivo(jugador buscado){
    FILE * archJug;
    int encontrado = 0;
    archJug = fopen("Jugadores.dat", "rb");
    jugador aux;
    while (fread(&aux, sizeof(jugador), 1, archJug)>0 && encontrado==0){
        if (strcmpi(aux.nombreLiga, buscado.nombreLiga)==0 && strcmpi(aux.nombreEquipo, buscado.nombreEquipo)==0 && strcmpi(aux.nombreJugador, buscado.nombreJugador)==0){
            encontrado = 1;
        }
    }
    fclose(archJug);
    return encontrado;
}

///Lee los datos de la estructura jugador para luego cargarlos al archivo. Se invoca en la foncion "cargaArchJugadores"
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
    int rta = buscarJugadorArchivo(*nuevo);
    if(rta==0)
    {
    nuevo->ID = buscarIDultimo()+1;
    }
    return rta;
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

nodoArbol* crearNodoArbolJug(jugador info){
    nodoArbol* aux=(nodoArbol*)malloc(sizeof(nodoArbol));
    aux->dato=info;
    aux->der=NULL;
    aux->izq=NULL;
    return aux;
}

/**Inserta los datos del jugador cargado en el arbol segun su campo de calificacion**/
nodoArbol* insertarArbol(nodoArbol* a,jugador aux){
    if(a==NULL){
        a=crearNodoArbolJug(aux);
    }else{
        if(a->dato.calificacion>=aux.calificacion){
            a->izq=insertarArbol(a->izq,aux);
        }else{
            a->der=insertarArbol(a->der,aux);
        }
    }

    return a;
}
/**Pasa los datos de los jugadores cargados en el archivo a el arbol de jugadore**/
nodoArbol* cargarArbolJugador(nodoArbol* a,char nombreEquipo[]){
    FILE* archi=fopen("Jugadores.dat","rb");
    if(archi!=NULL){
        jugador aux;
        while(fread(&aux,sizeof(jugador),1,archi)>0){
            if(strcmpi(aux.nombreEquipo,nombreEquipo) == 0)
                a=insertarArbol(a,aux);
        }

        fclose(archi);
    }

    return a;
}

///Muestra el contenido del arbol de jugadores **/
nodoArbol* mostrarInOrder(nodoArbol* a){
    if(a!=NULL){
        mostrarInOrder(a->der);
        mostrarJugador(a->dato);
        mostrarInOrder(a->izq);
    }
}

///Carga todos los jugadores del archivo al arbol del mercado
nodoArbol * crearArbolMercado (nodoArbol * arbol){
    FILE * archJugadores = fopen("Jugadores.dat", "rb");
    if (archJugadores!=NULL){
        jugador aux;
        while (fread(&aux, sizeof(jugador), 1, archJugadores)>0){
            arbol=insertarArbol(arbol, aux);
        }
    }
    fclose(archJugadores);
    return arbol;
}

///Busca jugador en el arbol
nodoArbol * buscarJugador(nodoArbol * arbol, char nombreBuscado[]){
    nodoArbol * rta = inicArbol();
    if (arbol!=NULL){
        if (strcmpi(arbol->dato.nombreJugador, nombreBuscado)!=0){
            rta = buscarJugador(arbol->izq, nombreBuscado);
            if (rta==NULL){
                rta = buscarJugador(arbol->der, nombreBuscado);
            }
        } else {
            rta = arbol;
        }
    }
    return rta;
}
