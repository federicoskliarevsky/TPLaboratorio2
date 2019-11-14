#ifndef ADMINISTRADOR_H_INCLUDED
#define ADMINISTRADOR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Menu.h"
#include "Jugador.h"
#include "Equipo.h"
#include "Usuario.h"
#include "Liga.h"
#define password "a"

nodoLiga * bajaJugador (nodoLiga *, nodoArbol **);
nodoLiga * altaJugador (nodoLiga *, nodoArbol **);
void reemplazarArchivoJugadores (jugador, char[]);
nodoLiga * modificarJugador (nodoLiga *, nodoArbol **);
nodoLiga * menuArchJugadores(nodoLiga *, nodoArbol**);
nodoLiga * menuArchEquipos(nodoLiga *);
nodoLiga * menuArchLigas(nodoLiga *);
nodoLiga * cargaArchJugadores(nodoLiga *, nodoArbol **);
void muestraArchJugadores();
nodoLiga * modificaArchJugadores (nodoLiga *, nodoArbol **);
nodoLiga * cargaArchEquipos(nodoLiga *);
void muestraArchEquipos();
nodoLiga * cargaArchLigas(nodoLiga *);
void muestraArchLigas();
nodoLiga * ingresoAdmin(nodoLiga *,nodoArbol**,nodoUsuario*);
nodoLiga * menuAdministrador(nodoLiga *,nodoArbol**,nodoUsuario*);

#endif // ADMINISTRADOR_H_INCLUDED
