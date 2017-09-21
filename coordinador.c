#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

void coordinador(int hijos, char *input, char *cantidadCaracteres, char *cadena){
    int i, status;
    pid_t pid;
    FILE *archivo = fopen(input, "r");
    if(!archivo){
        perror("Problema al abrir el archivo de entrada");
        exit(-1);
    }
    //Se calcula el tamaño del archivo y se asigna la cantidad de líneas que tendrá que comparar cada proceso hijo
    fseek(archivo, 0, SEEK_END);
    int tamanoTotal = ftell(archivo);
    int totalLineas = tamanoTotal / strtol(cantidadCaracteres, NULL, 10);
    int lineasPorHijo = totalLineas / hijos;
    int lineasSobrantes;
    fclose(archivo);

    //Posición inicial y final donde cada proceso hijo realizará la comparación.
    int inicio, fin;
    char inicioStr[20], finStr[20];

    /*Se crean los hijos y se les asigna la ejecución de un programa comparador.
    Al terminar este procedimiento, el proceso padre (el programa organizador) contará con N hijos.*/
    for(i = 0; i < hijos; i++){
        if((pid = fork()) > 0){ //Caso del padre
            //Se espera a que termine la ejecución del hijo creado.
            wait(&status);
        } else if(pid == -1){ //Caso de que exista un error en la creación de procesos
            perror("Error al crear un hijo");
            exit(-1);
        } else { //Caso del hijo. Ejecuta el programa comparador.
            //Se verifica el caso en que el último proceso hijo deba comparar más líneas del archivo que el resto
            if(i == hijos - 1){
                //Caso en el cual un proceso hijo deberá comparar más líneas que el resto
                if((lineasSobrantes = totalLineas % hijos) > 0){
                    inicio = (i * lineasPorHijo) * (strtol(cantidadCaracteres, NULL, 10) + 1);
                    fin = ((i + 1) * lineasPorHijo + lineasSobrantes) * (strtol(cantidadCaracteres, NULL, 10) + 1) - 1;
                } else {
                    inicio = (i * lineasPorHijo) * (strtol(cantidadCaracteres, NULL, 10) + 1);
                    fin = ((i + 1) * lineasPorHijo) * (strtol(cantidadCaracteres, NULL, 10) + 1) - 1;
                }
            } else {
                inicio = (i * lineasPorHijo) * (strtol(cantidadCaracteres, NULL, 10) + 1);
                fin = ((i + 1) * lineasPorHijo) * (strtol(cantidadCaracteres, NULL, 10) + 1) - 1;
            }
            //Se transforman los valores obtenidos a String para poder pasarlos como parámetro al proceso hijo
            sprintf(inicioStr, "%d", inicio);
            sprintf(finStr, "%d", fin);
            //Parámetros enviados al proceso comparador.
            char *argv[] = {"holaMundo", inicioStr, finStr, input, cantidadCaracteres, cadena, NULL};
            //Se ejecuta el proceso hijo con los parámetros indicados
            execv(argv[0], argv);
        }
    }
}

//Programa organizador de comparadores. Consiste en el programa que crea los procesos hijos.
int main(int argc, char *argv[]) {
    char parametro;
    char *i; //Nombre archivo de entrada
    char *n; //Cantidad de procesos comparadores (hijos)
    char *c; //Cantidad de carácteres en una línea del archivo
    char *p; //Cadena a buscar
    char *d; //Flag que indica si se deebe mostrar por pantalla el resultado

    int cantidadHijos; //Cantidad de hijos del proceso padre

    while((parametro = getopt(argc, argv, "i:n:c:p:d:")) != -1){
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
            d = optarg;
            break;
          case '?':
            if(optopt == 'i' || optopt == 'n' || optopt == 'c' || optopt == 'p' || optopt == 'd')
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
    coordinador(cantidadHijos, i, c, p);
    return 0;
}
