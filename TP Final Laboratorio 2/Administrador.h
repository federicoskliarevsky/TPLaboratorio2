#ifndef ADMINISTRADOR_H_INCLUDED
#define ADMINISTRADOR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Menu.h"
#include "Jugador.h"
#include "Equipo.h"
#include "Liga.h"
#define password "a"

nodoLiga * menuArchJugadores(nodoLiga *);
nodoLiga * menuArchEquipos(nodoLiga *);
void menuArchLigas(nodoLiga *);
nodoLiga * cargaArchJugadores(nodoLiga *);
void muestraArchJugadores();
nodoLiga * cargaArchEquipos(nodoLiga *);
void muestraArchEquipos();
nodoLiga * cargaArchLigas(nodoLiga *);
void muestraArchLigas();
nodoLiga * ingresoAdmin(nodoLiga *);
nodoLiga * menuAdministrador(nodoLiga *);

#endif // ADMINISTRADOR_H_INCLUDED
