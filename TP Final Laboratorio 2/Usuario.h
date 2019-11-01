#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Jugador.h"
#include "Menu.h"
#include "Liga.h"

typedef struct{
    char nombre[30];
    int monedas;
    char estadio[30];
    char camiseta[30];
    nodoArbol * arbolJugadoresClub;
} miClub;

void menuUsuario(nodoLiga *);

#endif // USUARIO_H_INCLUDED
