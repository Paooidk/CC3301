#include <stdlib.h>
#include <string.h>

#include "comprimir.h"

typedef unsigned int uint;
uint comprimir(uint a[], int nbits) {
  uint x = 0; //creo una variable que inicie en cero
  uint mascara = (1u << (nbits-1) << 1) - 1; //genero una mascara
  uint bits = (sizeof(uint) << 3); //tamaño de un entero sin signo, el << 3 representa el *8
  uint res = 0; //variable auxiliar que parte en cero para realizar la resta
  while (bits >= nbits){ //hacemos un while para representar una división pero usando resta
    bits = bits - nbits; //a los bits le restamos los nbits
    res++; //iteramos sobre res
   }
   
  uint k = 0; //variable auxiliar iniciada en cero para llevar a cabo la función comprimir
  while (k < res){ 
    x = (x << (nbits-1) << 1) | (a[k] & mascara); //los voy agregando a la máscara
    k++; //avanzo
   }
   return x; //retorno lo solicitado
}
