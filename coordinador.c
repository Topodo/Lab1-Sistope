#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>

void coordinador(int hijos, char *input, int cantidadCaracteres, char *cadena){
  int i, status;
  pid_t pid;
  char *argv[] = {"holaMundo", "-l", NULL};
  /*Se crean los hijos y se les asigna la ejecución de un programa comparador.
  Al terminar este procedimiento, el proceso padre (el programa organizador) contará con N hijos.*/
  for(i = 0; i < hijos; i++){
    if((pid = fork()) != 0){ //Caso del padre
      printf("Soy el padre de pid %d\n", getpid());
      wait(&status);
    }
    else{ //Caso del hijo. Ejecuta el proceso "holaMundo".
      execv(argv[0], argv);
      exit(0);
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
  int cantidadCaracteres; //Cantidad de carácteres en una línea del archivo

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
  cantidadCaracteres = strtol(c, NULL, 10);
  coordinador(cantidadHijos, i, cantidadCaracteres, p);
  return 0;
}
