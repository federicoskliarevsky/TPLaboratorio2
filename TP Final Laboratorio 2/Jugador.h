#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nombreJugador[30];
    char nombreEquipo[30];
    char nombreLiga[30];
    char nacionalidad[20];
    int calificacion; ///Entre 1 y 99
    int precio; ///Mayor a 0. Se puso entero por correspondencia con el juego real
    int eliminado; ///1 si esta eliminado, 0 si no. Se crea en 0
    int ID; ///ID unico a cada jugador
} jugador;

typedef struct {
    jugador dato;
    struct nodoArbol * izq;
    struct nodoArbol * der;
} nodoArbol;

int buscarJugadorArchivo(jugador);
int leerJugador (jugador *);
void mostrarJugador (jugador);
nodoArbol * inicArbol();
nodoArbol* crearNodoArbolJug(jugador);
nodoArbol* insertarArbol(nodoArbol*,jugador);
nodoArbol* cargarArbolJugador(nodoArbol* ,char[]);
nodoArbol* mostrarInOrder(nodoArbol*);
nodoArbol* crearArbolMercado (nodoArbol*);
nodoArbol* buscarJugador (nodoArbol*, char[]);
#endif // JUGADOR_H_INCLUDED
