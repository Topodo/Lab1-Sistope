#include "coordinador.h"

//Programa organizador de comparadores. Consiste en el programa que crea los procesos hijos.
int main(int argc, char *argv[]) {
    char parametro;
    char *i; //Nombre archivo de entrada
    char *n; //Cantidad de procesos comparadores (hijos)
    char *c; //Cantidad de carácteres en una línea del archivo
    char *p; //Cadena a buscar
    int d = 0; //Flag que indica si se deebe mostrar por pantalla el resultado

    int cantidadHijos; //Cantidad de hijos del proceso padre
    int cantidadCaracteres; //Cantidad de carácteres por línea de archivo

    while((parametro = getopt(argc, argv, "i:n:c:p:d")) != -1){
        switch (parametro) {
          case 'i':
            i = optarg;
            break;
          case 'n':
            n = optarg;
            break;
          case 'c':
            c = optarg;
            break;
          case 'p':
            p = optarg;
            break;
          case 'd':
            d = 1;
            break;
          case '?':
            if(optopt == 'i' || optopt == 'n' || optopt == 'c' || optopt == 'p')
              printf("Opcion -%c requiere un argumento.\n", optopt);
            else if(isprint(optopt))
              printf("Opcion desconocida '-%c'.\n", optopt);
            else
              printf("Opcion con caracter desconocido ''\\x%x'.\n", optopt);
            return 1;
          default:
            abort();
        }
    }
    //Se convierte a entero el parámetro obtenido con la cantidad de procesos hijos.
    cantidadHijos = strtol(n, NULL, 10);
    cantidadCaracteres = strtol(c, NULL, 10);
    int *pidHijos = coordinador(cantidadHijos, i, c, p);
    generarSalida(pidHijos, cantidadHijos, i, cantidadCaracteres, p, d);
    return 0;
}
