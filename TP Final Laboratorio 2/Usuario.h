#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Jugador.h"
///#include "Menu.h"
#include "Liga.h"

typedef struct{
    char nombreClub[30];
    int monedas;
    char estadio[30];
    char camiseta[30];
    int  arregloID[MAXJugadores];
} miClub;

typedef struct{
  char nombreUser[30];
  char pass[30];
  miClub club;
}usuario;

typedef struct{
  usuario dato;
  struct nodoUsuario * sig;
}nodoUsuario;

nodoUsuario * crearNodoUsuario(usuario);
nodoUsuario * cargarListaUsuarios(nodoUsuario *);
nodoUsuario * inicListaUsuarios();
void menuUsuario(nodoLiga *, nodoArbol *,usuario,nodoUsuario *);
usuario verificarUsuario(nodoLiga *,nodoArbol *,nodoUsuario *);
nodoUsuario * LoguearUsuario();
int IngresarUsuario(usuario*);
nodoUsuario * agregarFinalNodoUsuario(nodoUsuario *,nodoUsuario *);
nodoUsuario * buscarUltimoUsuario(nodoUsuario *);
void menuMercado();

#endif // USUARIO_H_INCLUDED
