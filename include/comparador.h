//Archivo que contiene las cabeceras de las funciones del programa comparador.c
#ifndef COMPARADOR
#define COMPARADOR
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void escribir(char* num, char* cadena, int resultado);
int leerTexto(int pos, int pos2, char* cadena, char* proc, char* input);
int transformar(char* num);
#endif
