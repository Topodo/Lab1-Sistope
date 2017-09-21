#include "comparador.h"

void main(int argc, char* argv[]){
    int pos = transformar(argv[1]);
    int pos2 = transformar(argv[2]);
    int a = 0;
    char* cadena = (char*)malloc(sizeof(char)*strlen(argv[3]));
    while(a<strlen(argv[3])){
        cadena[a] = argv[3][a];
        a++;
    }
    int resultado = leerTexto(pos, pos2, cadena, argv[4], argv[5]);
}
