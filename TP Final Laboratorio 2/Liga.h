#ifndef LIGA_H_INCLUDED
#define LIGA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Equipo.h"

typedef struct{
    char paisLiga[20];
    char nombreLiga[30];
    nodoEquipo * listaEquipos;
} liga;

typedef struct{
    liga dato;
    struct nodoLiga * sig;
} nodoLiga;

void leerLiga (liga *);
void mostrarLiga (liga);
nodoLiga * buscarLiga(nodoLiga *, char[]);
nodoLiga * agregarLigaIndividual(nodoLiga *);
nodoLiga * inicListaliga();
nodoLiga * cargarListaLigas(nodoLiga *);
nodoLiga * crearNodoLiga(liga);
nodoLiga * agregarFinalNodoLiga(nodoLiga *, nodoLiga *);
nodoLiga * buscarUltimoLiga(nodoLiga *);
void muestraListaLigas (nodoLiga *);
void muestraTodosLosEquipos (nodoLiga *);

#endif // LIGA_H_INCLUDED
