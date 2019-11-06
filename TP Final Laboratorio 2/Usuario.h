#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Jugador.h"
#include "Menu.h"
#include "Liga.h"

typedef struct{
    char nombreClub[30];
    int monedas;
    char estadio[30];
    char camiseta[30];
    nodoArbol * arbolJugadoresClub;
} miClub;

typedef struct{
  char nombreUser[30];
  char pass[30];
  miClub club;
}usuario;

typedef struct{
  usuario user;
  struct nodoUsuario * sig;
}nodoUsuario;

void menuUsuario(nodoLiga *, nodoArbol *);
void verificarUsuario(nodoLiga *,nodoArbol *);
void LoguearUsuario();
int IngresarUsuario();
#endif // USUARIO_H_INCLUDED
