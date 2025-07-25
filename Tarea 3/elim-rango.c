#include <stdio.h>
#include <stdlib.h>

#include "elim-rango.h"

void eliminarRango(Nodo **phead, double y, double z) {
  Nodo *aux = NULL; //Creamos un puntero auxiliar para ir revisando los nodos anteriores al actual
  while (*phead != NULL && (*phead) -> x <= z){
        if ((*phead) -> x >= y){
           Nodo *temp = *phead;
           *phead = (*phead) -> prox;
           free (temp);
           if (aux != NULL) {
              aux -> prox = *phead;
           }
        }
        else {
             aux = *phead;
             phead = &((*phead) -> prox);
       }
     }

}
