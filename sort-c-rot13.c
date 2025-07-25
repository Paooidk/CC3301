#include <string.h>

int strCmp(char *s1, char *s2) {
    char c1;
    char c2;

    for (;;) {
      c1= *s1;
      c2= *s2;

      if (c1==0)
        break;
        
     //modificación, se agregan las condiciones para descifrar primero las letras y luego compararlas
     
      if ('a' <= c1 && c1 <= 'm') {
           c1 += 13;
       } else if ('n' <= c1 && c1 <= 'z') {
           c1 -= 13;
       }

       if ('a' <= c2 && c2 <= 'm') {
           c2 += 13;
       } else if ('n' <= c2 && c2 <= 'z') {
           c2 -= 13;
       }
     
     //fin de las modificaciones

      if (c1!=c2)
        break;

      s1++;
      s2++;
    }

    return c1 - c2;
}

void sort(char **a, int n) {
  char **ult= &a[n-1];
  char **p= a;
  while (p<ult) {
    int t1= strCmp(p[0], p[1]);
    if (t1 <= 0)
      p++;
    else {
      char *tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= a;
    }
  }
}
