#include "coordinador.h"

/*coordinador: Función que coordina a los procesos hijos
Entradas: La cantidad de hijos, el nombre del archivo de entrada, la cantidad de caracteres por línea y la cadena a buscar
Salidas: Un arreglo con los pid de los hijos
*/
int *coordinador(int hijos, char *input, char *cantidadCaracteres, char *cadena){
    int *pidHijos = (int *)malloc(sizeof(int) * hijos);
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

    //Posición inicial donde cada proceso hijo realizará la comparación.
    int inicio;
    char inicioStr[20], pidStr[20], lineasPorHijoStr[20];

    /*Se crean los hijos y se les asigna la ejecución de un programa comparador.
    Al terminar este procedimiento, el proceso padre (el programa organizador) contará con N hijos.*/
    for(i = 0; i < hijos; i++){
        if((pid = fork()) > 0){ //Caso del padre
            //Se almacena el pid del hijo en el arreglo
            pidHijos[i] = pid;
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
                    lineasPorHijo += lineasSobrantes;
                } else {
                    inicio = (i * lineasPorHijo) * (strtol(cantidadCaracteres, NULL, 10) + 1);
                }
            } else {
                inicio = (i * lineasPorHijo) * (strtol(cantidadCaracteres, NULL, 10) + 1);
            }
            //Se transforman los valores obtenidos a String para poder pasarlos como parámetro al proceso hijo
            sprintf(inicioStr, "%d", inicio);
            sprintf(pidStr, "%d", getpid());
            sprintf(lineasPorHijoStr, "%d", lineasPorHijo);
            //Parámetros enviados al proceso comparador.
            char *argv[] = {"comparador", inicioStr, lineasPorHijoStr, cadena, pidStr, input, NULL};
            //Se ejecuta el proceso hijo con los parámetros indicados
            execv(argv[0], argv);
        }
    }
    return pidHijos;
}

/*generarSalida: Función que escribe la salida del programa
Entradas: El arreglo con los pid de los hijos, el nombre del archivo de entrada, la cantidad de carácteres por línea, la cadena a buscar,
la cantidad de hijo y una flag que indica si se quiere mostrar por pantalla
Salidas: Ninguna*/
void generarSalida(int *pidHijos, int cantidadHijos, char *input, int cantidadCaracteres, char *cadena, int flag){
    char nombreSalida[] = "rc_";
    strcat(nombreSalida, cadena);
    strcat(nombreSalida, ".txt");
    FILE *archivoEntrada = fopen(input, "r");
    FILE *archivoSalida = fopen(nombreSalida, "w");
    FILE *resultadoParcial;
    //Se calcula el tamaño total del archivo y la cantidad de líneas de este
    fseek(archivoEntrada, 0, SEEK_END);
    int tamanoTotal = ftell(archivoEntrada);
    int totalLineas = tamanoTotal / cantidadCaracteres;
    fclose(archivoEntrada);
    archivoEntrada = fopen(input, "r");
    int linea, caracter;
    char letra;
    int i;
    char **resultados = (char**)malloc(sizeof(char *) * totalLineas);
    for(i = 0; i < totalLineas; i++){
        resultados[i] = (char*)malloc(sizeof(char) * 2);
    }
    //Se almacenan los resultados parciales
    int hijo;
    int cont = 0;
    int posResultado = cantidadCaracteres + 3;
    char nombreResultadoParcial[] = "rp_";
    char pidHijoStr[20];
    char resultado[2];
    for(hijo = 0; hijo < cantidadHijos; hijo++){
        strcat(nombreResultadoParcial, cadena);
        strcat(nombreResultadoParcial, "_");
        sprintf(pidHijoStr, "%d", pidHijos[hijo]);
        strcat(nombreResultadoParcial, pidHijoStr);
        strcat(nombreResultadoParcial, ".txt");
        //Se abre el archivo con los resultados parciales del proceso hijo con el pid buscado
        resultadoParcial = fopen(nombreResultadoParcial, "r");
        while(!feof(resultadoParcial)){
            fscanf(resultadoParcial, "%s\n", resultado);
            strcpy(resultados[cont], resultado);
            cont++;
        }
        strcpy(nombreResultadoParcial, "rp_");
    }
    //Se escribe el archivo de salida
    for(linea = 0; linea < totalLineas; linea++){
        for(caracter = 0; caracter <= cantidadCaracteres; caracter++){
            fscanf(archivoEntrada, "%c", &letra);
            if(letra != '\n'){
                if(flag){
                    printf("%c", letra);
                }
                fprintf(archivoSalida, "%c", letra);
            }
        }
        if(flag){
            printf("      %s\n", resultados[linea]);
        }
        fprintf(archivoSalida, "     ");
        fprintf(archivoSalida, "%s\n", resultados[linea]);
    }
    fclose(resultadoParcial);
    fclose(archivoSalida);
    fclose(archivoEntrada);
}
