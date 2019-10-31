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

void menuArchJugadores();
void menuArchEquipos(nodoLiga *);
void menuArchLigas(nodoLiga *);
void cargaArchJugadores();
void muestraArchJugadores();
void cargaArchEquipos(nodoLiga *);
void muestraArchEquipos();
void cargaArchLigas();
void muestraArchLigas();
void ingresoAdmin(nodoLiga *);
void menuAdministrador(nodoLiga *);

#endif // ADMINISTRADOR_H_INCLUDED
