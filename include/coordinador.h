//Archivo que contiene las cabeceras de las funciones del archivo coordinador.c
#ifndef COORDINADOR
#define COORDINADOR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int *coordinador(int hijos, char *input, char *cantidadCaracteres, char *cadena);
void generarSalida(int *pidHijos, int cantidadHijos, char *input, int cantidadCaracteres, char *cadena, int flag);
#endif
