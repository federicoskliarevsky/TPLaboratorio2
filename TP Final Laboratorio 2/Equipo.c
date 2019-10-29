#include "Equipo.h"

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
    while (nuevo->anioCreacion<0 || nuevo->anioCreacion>2019){
        printf (" Ingrese un anio valido: ");
        scanf ("%d", &(nuevo->anioCreacion));
    }
    nuevo->arbolJugadoresEquipo = NULL;
}

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
            printf ("\n Muestra jugadores: "); ///REEMPLAZAR POR FUNCION MUESTRA ARBOL
        }
    } else {
        printf ("\n Equipo sin jugadores.");
    }
}

nodoEquipo * iniclistaEquipo(){
return NULL;
}

nodoEquipo * cargarListaEquipo(nodoEquipo * lista,char nombre[]){
    equipo aux;
    nodoEquipo * a;
    FILE * archi = fopen("Equipos.dat","rb");
    if(archi!=NULL)
    {
     while(fread(&aux,sizeof(equipo),1,archi) > 0)
     {
      if(strcmp(aux.nombreLiga,nombre))
      {
       lista = agregarFinalNodoEquipo(lista,crearNodoEquipo(aux));
      }
     }
    }
    fclose(archi);
    return lista;
}
