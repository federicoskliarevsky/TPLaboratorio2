#ifndef EQUIPO_H_INCLUDED
#define EQUIPO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Jugador.h"

typedef struct {
    char nombreEquipo[30];
    char nombreLiga[30];
    int anioCreacion;
    nodoArbol * arbolJugadoresEquipo;
} equipo;

typedef struct {
    equipo dato;
    struct nodoEquipo * sig;
} nodoEquipo;

void leerEquipo (equipo *);
void mostrarEquipo (equipo);
nodoEquipo * iniclistaEquipo();
nodoEquipo * cargarListaEquipo(nodoEquipo *, char[]);
nodoEquipo * agregarFinalNodoEquipo(nodoEquipo * ,nodoEquipo *);
nodoEquipo * crearNodoEquipo(equipo);
nodoEquipo * buscarUltimoEquipo(nodoEquipo *);
nodoEquipo * buscarEquipo(nodoEquipo *, char[]);
void muestraListaEquipos (nodoEquipo *);
#endif // EQUIPO_H_INCLUDED
