#include "Jugador.h"
///Lee los datos de la estructura jugador para luego cargarlos al archivo. Se invoca en la foncion "cargaArchJugadores"
void leerJugador(jugador * nuevo){
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
    printf (" Ingrese precio (mayor a 0): ");
    fflush (stdin);
    scanf ("%d", &(nuevo->precio));
    while (nuevo->precio<0){
        printf ("\n Ingrese un precio valido: ");
        scanf ("%d", &(nuevo->precio));
    }
}
///Printea todos los datos de la estructura jugador
void mostrarJugador(jugador aux){
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
        mostrarInOrder(a->izq);
        mostrarJugador(a->dato);
        mostrarInOrder(a->der);
    }
}
