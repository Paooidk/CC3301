#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reemplazar.h"

char *reemplazo(char *s, char c, char *pal) {
 //Creamos variables auxiliares
 char *x = s;
 int z = 0;
 // Se recorre el string una vez
 while (*x != '\0') {
  if (*x == c) {
  z++;
  }
  x++;
 }
 // Se calcula el largo del string con strlen
 int sL = strlen(s);
 int palL = strlen(pal);
 int reslen = sL - z + z * palL;
 char *res = malloc(reslen + 1); //solicitamos memoria con malloc
 char *ss = s;
 char *r = res;
 // Se recorre S
 while (*ss != '\0') {
 // Si no es c, se copia el caracter
 if (*ss != c) {
    *r = *ss;
    r++;
   }
 // Si lo es, se copia pal
  else {
   char *pa = pal;
   while (*pa != '\0') {
    *r = *pa;
    r++;
    pa++;
   }
  }
  ss++;
 }
 *r = '\0'; //para terminar el string
 return res;
}


//Segunda función
void reemplazar(char *s, char c, char *pal) {
 //variables auxiliares
 char *x = s;
 int z = 0;
 // Al igual que para la función anterior, se recorre el string
 while (*x != '\0') {
   if (*x == c) {
   z++;
   }
   x++;
 }
 // Se calcula el largo con strlen
 int sL = strlen(s);
 int palL = strlen(pal);
 int reslen = sL - z + z * palL;
 if (palL <= 1) {
   char *ss = s;
   char *res = s;
   while (*ss != '\0') {
    if (*ss == c) {
     if (palL == 1) {
      *res = *pal;
      res++;
      } 
     }
      else {
       *res = *ss;
       res++;
      }
      ss++;
    }
  *res='\0';
  }
 else {
   char *ss = s + sL;
   char *res = s + reslen;
   *res = '\0';
   ss--;
   res--;
   while (ss >= s) {
    if (*ss == c) {
     char *pa = pal + palL - 1;
     while (pa >= pal) {
      *res = *pa;
      pa--;
      res--;
     }
    }
    else {
     *res = *ss;
     res--;
    }
    ss--;
   }
 }
 }
