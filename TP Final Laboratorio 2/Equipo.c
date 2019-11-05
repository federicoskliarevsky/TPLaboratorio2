#include "Equipo.h"

/**Lee los campos de la estructura equipo para luego cargarlos al archivo e inicializa el campo "arbolJugadoresEquipo".
Se invoca en la foncion "cargaArchEquipos"**/
void leerEquipo (equipo * nuevo){
    printf ("\n Ingrese el nombre del equipo: ");
    fflush (stdin);
    gets (nuevo->nombreEquipo);
    printf (" Ingrese liga del equipo: ");
    fflush (stdin);
    gets (nuevo->nombreLiga);
    printf (" Ingrese anio de creacion (mayor a 0): ");
    fflush (stdin);
    scanf ("%d", &(nuevo->anioCreacion));
    while (nuevo->anioCreacion<1800 || nuevo->anioCreacion>2019){
        printf (" Ingrese un anio valido: ");
        scanf ("%d", &(nuevo->anioCreacion));
    }
    nuevo->arbolJugadoresEquipo = NULL;
}
/**Printea los campos de la estructura equipo. Si el equipo tiene cargado jugadores da la opcion de ver los jugadores que tiene
el equipo,caso contrario muestra un mensaje informando que el equipo esta sin jugadores*/
void mostrarEquipo (equipo aux){
    printf ("\n Equipo: ");
    puts (aux.nombreEquipo);
    printf (" Liga: ");
    puts (aux.nombreLiga);
    printf (" Anio de creacion: %d", aux.anioCreacion);
    if (aux.arbolJugadoresEquipo!=NULL){
        char control;
        printf ("\n Desea ver jugadores? (s para confirmar): ");
        fflush (stdin);
        scanf ("%c", &control);
        if (control=='s'){
            printf ("\n Muestra jugadores (ordenados por valoracion): ");
            mostrarInOrder(aux.arbolJugadoresEquipo);
        }
    } else {
        printf ("\n Equipo sin jugadores.");
    }
}

nodoEquipo * iniclistaEquipo(){
return NULL;
}
/**Pasa los datos de los equipos cargados en el archivo a la lista de equipos**/
nodoEquipo * cargarListaEquipo(nodoEquipo * lista,char nombre[]){
    equipo aux;
    nodoEquipo * a;
    FILE * archi = fopen("Equipos.dat","rb");
    if(archi!=NULL)
    {
     while(fread(&aux,sizeof(equipo),1,archi) > 0)
     {
      if(strcmpi(aux.nombreLiga,nombre) == 0)
      {
       lista = agregarFinalNodoEquipo(lista,crearNodoEquipo(aux)); ///Dentro de la funcion llamada se cargan los jugadores del archivo al arbol del equipo
      }
     }
    }
    fclose(archi);
    return lista;
}
/**Crea un nodo en la lista de equipos.Se invoca en la funcion "cargarListaEquipo"**/
nodoEquipo * crearNodoEquipo(equipo dato){
char nombre[30];
strcpy(nombre,dato.nombreEquipo);
nodoEquipo * nuevoNodo =(nodoEquipo*) malloc (sizeof(nodoEquipo));
nuevoNodo->dato = dato;
nuevoNodo->sig = NULL;
nuevoNodo->dato.arbolJugadoresEquipo = inicArbol();
nuevoNodo->dato.arbolJugadoresEquipo = cargarArbolJugador(nuevoNodo->dato.arbolJugadoresEquipo,nombre); ///Carga desde el archivo
return nuevoNodo;
}
/**Se invoca en la funcion "cargarListaEquipo" para ir agregando en orden de carga los equipos a la lista**/
nodoEquipo * agregarFinalNodoEquipo(nodoEquipo * lista, nodoEquipo * nuevoNodo){
    if(lista==NULL)
    {
     lista = nuevoNodo;
    }else
    {
     nodoEquipo * ultimo = buscarUltimoEquipo(lista);
     ultimo->sig = nuevoNodo;
    }
    return lista;
}
/**Se invoca en la funcion "agregarFinalNodoEquipo" para buscar el ultimo nodo y asi poder enlazar este con el nodo recien
cargado**/
nodoEquipo * buscarUltimoEquipo(nodoEquipo * lista){
 nodoEquipo * seg = lista;
 if(seg!=NULL)
 {
  while(seg->sig != NULL)
  {
   seg = seg->sig;
  }
 }
 return seg;
}

void muestraListaEquipos (nodoEquipo * lista){
    printf ("\nLista de equipos  de la liga %s:\n", lista->dato.nombreLiga);
    while (lista!=NULL){
        mostrarEquipo(lista->dato);
        printf ("\n");
        lista = lista->sig;
    }
}

nodoEquipo * buscarEquipo(nodoEquipo * lista, char nombreBuscado[]){
    while (lista!=NULL && strcmpi(lista->dato.nombreEquipo, nombreBuscado)!=0){
        lista = lista->sig;
    }
    return lista;
}
