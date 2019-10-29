#ifndef LIGA_H_INCLUDED
#define LIGA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Equipo.h"

typedef struct{
    char paisLiga[20];
    char nombreLiga[30];
} liga;

typedef struct{
    liga dato;
    nodoEquipo * listaEquipos;
    struct nodoLiga * sig;
} nodoLiga;

void leerLiga (liga *);
void mostrarLiga (liga);
nodoLiga * inicListaliga();
nodoLiga * cargarListaLigas(nodoLiga *);
nodoLiga * crearNodoLiga(liga);
nodoLiga * agregarFinalNodoLiga(nodoLiga *, nodoLiga *);
nodoLiga * buscarUltimoLiga(nodoLiga *);
void muestraListaLigas (nodoLiga *);
#endif // LIGA_H_INCLUDED
