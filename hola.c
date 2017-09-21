#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  printf("Hola mundo, soy un proceso hijo y leo desde el byte %lu hasta el byte %lu\n", strtol(argv[1], NULL, 10), strtol(argv[2], NULL, 10));
  return 0;
}
