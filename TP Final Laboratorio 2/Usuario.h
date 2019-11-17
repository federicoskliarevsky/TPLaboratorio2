#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Jugador.h"
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
void mostrarClub (usuario);
void reemplazarArchivoUsuario(usuario);
nodoUsuario *  menuModificarClub(usuario*,nodoUsuario *);
nodoUsuario *  menuMiClub(nodoLiga *,nodoMercado *,usuario *,nodoUsuario *);
float calcularPromedio (int[]);
int resultadoPartido (float, float);
int menuJugarPartido(nodoLiga *, nodoMercado *, usuario, nodoUsuario *);
nodoUsuario * menuUsuario(nodoLiga *, nodoMercado *,usuario,nodoUsuario *);
void insertarOrdenado (int[], int, int);
void ordenarArregloMayorMenor (int[]);
int buscaEliminados (usuario *);
usuario verificarUsuario(nodoLiga *,nodoMercado *,nodoUsuario *);
nodoUsuario * LoguearUsuario();
int IngresarUsuario(usuario*);
nodoUsuario * agregarFinalNodoUsuario(nodoUsuario *,nodoUsuario *);
nodoUsuario * buscarUltimoUsuario(nodoUsuario *);
void menuMercado(nodoLiga *, nodoMercado *,usuario,nodoUsuario *);
void actualizaArchivoUsuarios (usuario);
void compraJugador (usuario *, nodoMercado*);
void ventaJugador (usuario *, nodoMercado*);
#endif // USUARIO_H_INCLUDED
