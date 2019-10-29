#include "Liga.h"

void leerLiga (liga * nuevo){
    printf ("\n Ingrese el nombre de la liga: ");
    fflush (stdin);
    gets (nuevo->nombreLiga);
    printf (" Ingrese pais de la liga: ");
    fflush (stdin);
    gets (nuevo->paisLiga);
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
            lista = agregarFinalNodoLiga(lista,crearNodoLiga(aux));
        }
    }
    fclose(archi);
    return lista;
}

nodoLiga * crearNodoLiga(liga dato){
 char nombre[40];
 nodoLiga * nuevoNodo = (nodoLiga*) malloc(sizeof(nodoLiga));
 nuevoNodo->dato = dato;
 nuevoNodo->sig = NULL;
 nuevoNodo->listaEquipos = iniclistaEquipo();
 nuevoNodo->listaEquipos = cargarListaEquipo(nuevoNodo->listaEquipos,nombre);
 return nuevoNodo;
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

nodoLiga * buscarUltimoLiga(nodoLiga * lista)
{
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
    printf ("\nLista de ligas:");
    while (lista!=NULL){
        mostrarLiga(lista->dato);
        lista = lista->sig;
    }
}
