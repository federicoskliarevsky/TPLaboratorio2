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

nodoLiga * bajaJugador (nodoLiga *);
nodoLiga * altaJugador (nodoLiga *);
void reemplazarArchivoJugadores (jugador, char[]);
nodoLiga * modificarJugador (nodoLiga *);
nodoLiga * menuArchJugadores(nodoLiga *,nodoMercado *);
nodoLiga * menuArchEquipos(nodoLiga *);
nodoLiga * menuArchLigas(nodoLiga *);
nodoLiga * cargaArchJugadores(nodoLiga *,nodoMercado *);
void muestraArchJugadores();
nodoLiga * modificaArchJugadores (nodoLiga *,nodoMercado *);
nodoLiga * cargaArchEquipos(nodoLiga *);
void muestraArchEquipos();
nodoLiga * cargaArchLigas(nodoLiga *);
void muestraArchLigas();
nodoLiga * ingresoAdmin(nodoLiga *,nodoMercado*,nodoUsuario*);
nodoLiga * menuAdministrador(nodoLiga *,nodoMercado*,nodoUsuario*);

#endif // ADMINISTRADOR_H_INCLUDED
