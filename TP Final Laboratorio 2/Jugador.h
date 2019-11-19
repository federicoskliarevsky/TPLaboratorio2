#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define MAXJugadores 11 ///TENER EN CUENTA QUE SI SE MODIFICA HAY QUE CAMBIAR TODOS LOS ARCHIVOS.

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
    int datoID;
    struct nodoMercado * sig;
} nodoMercado;

jugador buscarJugadorArchivo(jugador);
void crearArregloID (int[]);
int leerJugador (jugador *);
void mostrarJugador (jugador);
nodoMercado * iniclistaMercado();
nodoMercado* crearNodoMercado(int);
nodoMercado* agregarFinalNodoMercado(nodoMercado*,int);
nodoMercado * buscarUltimoMercado(nodoMercado *);
void cargarArregloJugador(int[],char[]);
void MostrarMercado(nodoMercado *, int);
int buscarJugador (nodoMercado*,int);
jugador buscaIDArch(int);
int buscarValidos(int[], int);
void mostrarArregloID (int[], int);
#endif // JUGADOR_H_INCLUDED
