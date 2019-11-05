#include "Liga.h"
/**Lee los datos de la estructura liga para luego cargarlos al archivo e inicializa la lista de equipos. Se invoca en la funcion
 "cargaArchLigas"**/
void leerLiga (liga * nuevo){
    printf ("\n Ingrese el nombre de la liga: ");
    fflush (stdin);
    gets (nuevo->nombreLiga);
    printf (" Ingrese pais de la liga: ");
    fflush (stdin);
    gets (nuevo->paisLiga);
    nuevo->listaEquipos=iniclistaEquipo();
}
///Printea todos los datos de la estructura liga
void mostrarLiga(liga aux){
    printf ("\n Liga: ");
    puts (aux.nombreLiga);
    printf (" Pais: ");
    puts (aux.paisLiga);
}

nodoLiga * inicListaliga(){
 return NULL;
}
/**Pasa los datos de las ligas cargados en el archivo a la lista de ligas**/
nodoLiga * cargarListaLigas(nodoLiga * lista){
    liga aux;
    FILE * archi = fopen("Ligas.dat","rb");
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(liga),1,archi)> 0)
        {
            nodoLiga * nuevo = crearNodoLiga(aux);
            lista = agregarFinalNodoLiga(lista,nuevo);
        }
    }
    fclose(archi);
    return lista;
}
/**Crea un nodo en la lista de ligas e inicializa el campo listaEquipos de la estructura liga.Se invoca en la funcion
"agregarLigaIndividual" y "cargarListaLigas"**/
nodoLiga * crearNodoLiga(liga dato){
 char nombre[40];
 strcpy(nombre,dato.nombreLiga);
 nodoLiga * nuevoNodo = (nodoLiga*) malloc(sizeof(nodoLiga));
 nuevoNodo->dato = dato;
 nuevoNodo->sig = NULL;
 nuevoNodo->dato.listaEquipos = iniclistaEquipo();
 nuevoNodo->dato.listaEquipos = cargarListaEquipo(nuevoNodo->dato.listaEquipos,nombre); ///Dentro de la funcion llamada se cargan los equipos del archivo a la lista de cada liga
 return nuevoNodo;
}

/**Funcion utilizada en "cargaArchJugadores" y "cargaArchEquipos" para saber si un jugador o equipo cargado pertenecen a una
 liga**/
nodoLiga * buscarLiga(nodoLiga * lista, char nombreBuscado[]){
    while (lista!=NULL && strcmpi(lista->dato.nombreLiga, nombreBuscado)!=0){
        lista = lista->sig;
    }
    return lista;
}

/**Lee solamente los datos de una liga y los agrega al final de la lista de ligas.Se invoca en la "cargaArchEquipos"**/
nodoLiga * agregarLigaIndividual(nodoLiga * lista){
    FILE * archLigas;
    archLigas = fopen("Ligas.dat", "ab");
    liga aux;
    printf ("\n Lectura de datos de la nueva liga:");
    leerLiga(&aux);
    fwrite(&aux, sizeof(liga), 1, archLigas);
    lista = agregarFinalNodoLiga(lista, crearNodoLiga(aux));
    fclose(archLigas);
    return lista;
}
/**Se invoca en la funcion "cargarListaLigas","agregarLigaIndividual" y "cargaArchLigas" para ir agregando en orden de carga
 las ligas a la lista**/
nodoLiga * agregarFinalNodoLiga(nodoLiga * lista,nodoLiga * nuevoNodo){
  if(lista == NULL)
  {
   lista = nuevoNodo;
  }else
  {
   nodoLiga * ultimo = buscarUltimoLiga(lista);
   ultimo->sig = nuevoNodo;
  }
  return  lista;
}
/**Se invoca en la funcion "agregarFinalNodoLiga" para buscar el ultimo nodo y asi poder enlazar este con el nodo recien
cargado**/
nodoLiga * buscarUltimoLiga(nodoLiga * lista){
 nodoLiga * seg = lista;
 if(seg!=NULL)
 {
  while(seg->sig != NULL)
  {
   seg = seg->sig;
  }
 }
 return seg;
}

void muestraListaLigas (nodoLiga * lista){
    printf ("\n\nLista de ligas:");
    while (lista!=NULL){
        mostrarLiga(lista->dato);
        lista = lista->sig;
    }
}

void muestraTodosLosEquipos (nodoLiga * lista){
    while (lista!=NULL){
        if (lista->dato.listaEquipos!=NULL){
            muestraListaEquipos(lista->dato.listaEquipos);
        } else {
            printf ("La liga %s no tiene equipos cargados.\n", lista->dato.nombreLiga);
            Sleep(750);
        }
        printf ("\n");
        lista = lista->sig;
    }
}
