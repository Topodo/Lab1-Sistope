#include "comparador.h"
char salto = '\n';

//Entrada: Numero de proceso, Cadena a comparar, Respuesta
//Salida: Nada
//Procedimiento: Concatena las palabras, y escribe en el archivo si encontro o no la cadena.
void escribir(char* num, char* cadena, int resultado){
    //Se concatenan las palabras
    char* nombre = (char*)malloc(sizeof(char)*(4+strlen(num)+strlen(cadena)));
    nombre[0] = 'r';
    nombre[1] = 'p';
    nombre[2] = '_';
    int i = 0;
    while(i<strlen(cadena)){
        nombre[3+i] = cadena[i];
        i++;
    }
    nombre[3+i] = '_';
    int j = 0;
    while(j<strlen(num)){
        nombre[4+i+j] = num[j];
        j++;
    }
    strcat(nombre, ".txt");
    //Se abre el archivo y se escribe la respuesta
    FILE* arc = fopen(nombre, "a");
    if(resultado == 0){
        fprintf(arc, "%s\n", "SI");
    }
    else{
        fprintf(arc, "%s\n", "NO");
    }
    fclose(arc);
}

//Entrada: Posicion inicial de escritura, Cantidad de lineas a leer, Cadena a encontrar
//Salida: 0 Si, 1 No
//Proceso: Lee el archivo, y compara segun la cadena pedida
int leerTexto(int pos, int pos2, char* cadena, char* proc, char* input){
    int a = 0;
    FILE* arc = fopen(input, "r");
    char c;
    fseek(arc, pos, SEEK_SET);
    int cont = 0, actual, resultado = 1;
    while(!feof(arc)){
        if(c == salto){
            escribir(proc, cadena, resultado);
            resultado = 1;
            cont ++;
        }
        if(cont == pos2){
            break;
        }
        if(c == cadena[0]){
            actual = ftell(arc);
            int i = 1;
            while(i< strlen(cadena)){
                if(fgetc(arc) == cadena[i]){
                    i++;
                }
                else{
                    fseek(arc, actual, SEEK_SET);
                    break;
                }
          }
          if(strlen(cadena)-i == 0){
              resultado = 0;
              fseek(arc, actual, SEEK_SET);
            }
        }
        c = fgetc(arc);
    }
    fclose(arc);
    return resultado;
}

int transformar(char* num){
    int i = strlen(num);
    int acum=0, multi = 1;
    while(i>0){
        int aux = (num[i-1]-48)*multi;
        acum = acum + aux;
        multi = multi*10;
        i--;
    }
    return acum;
}
