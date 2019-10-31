#include "Liga.h"

void leerLiga (liga * nuevo){
    printf ("\n Ingrese el nombre de la liga: ");
    fflush (stdin);
    gets (nuevo->nombreLiga);
    printf (" Ingrese pais de la liga: ");
    fflush (stdin);
    gets (nuevo->paisLiga);
    nuevo->listaEquipos=iniclistaEquipo();
}

void mostrarLiga(liga aux){
    printf ("\n Liga: ");
    puts (aux.nombreLiga);
    printf (" Pais: ");
    puts (aux.paisLiga);
}

nodoLiga * inicListaliga(){
 return NULL;
}

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

nodoLiga * crearNodoLiga(liga dato){
 char nombre[40];
 strcpy(nombre,dato.nombreLiga);
 nodoLiga * nuevoNodo = (nodoLiga*) malloc(sizeof(nodoLiga));
 nuevoNodo->dato = dato;
 nuevoNodo->sig = NULL;
 nuevoNodo->dato.listaEquipos = iniclistaEquipo();
 nuevoNodo->dato.listaEquipos = cargarListaEquipo(nuevoNodo->dato.listaEquipos,nombre);
 return nuevoNodo;
}

nodoLiga * buscarLiga(nodoLiga * lista, char nombreBuscado[]){
    while (lista!=NULL && strcmpi(lista->dato.nombreLiga, nombreBuscado)!=0){
        lista = lista->sig;
    }
    return lista;
}

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
        muestraListaEquipos(lista->dato.listaEquipos);
        printf ("\n");
        lista = lista->sig;
    }
}
