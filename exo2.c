#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "exo1.h"
#include "exo2.h"


long extended_gcd ( long s , long t , long *u , long * v ) {
   if ( s == 0) {
     *u = 0;
     *v = 1;
     return t ;
  }
  long uPrim , vPrim ;
  long gcd = extended_gcd (t%s , s , &uPrim , &vPrim ) ;
  *u=vPrim-(t/s)*uPrim;
  *v=uPrim;
  return gcd;
  }



void generate_key_values(long p, long q, long *n, long *s, long *u){
  *n= p*q;
  long t =(p-1)*(q-1);
  long z = 0;
  long v;
  
  while(z!=1){
    *s= rand_long(2,t);
    z=extended_gcd(*s,t,u,&v);
  }  
}



long* encrypt(char* chaine, long s, long n){//retourne un tableau en cryptant a l'aide de la chaine et de la fonction modpow
  long* tab=(long*)malloc(sizeof(long)*strlen(chaine));
  long c;
  long m;
  for (int i=0; i<strlen(chaine);i++) {//parcours de la chaine
    m= (int) chaine[i];
    c=modpow(m,s,n);
    tab[i]=c;
  }
  return tab;
}



char* decrypt(long* crypted, int size, long u, long n){//decrypte le tableau d'entier long à l'aide de la fonction modpow, renvoie une chaine de charactere
  char*mot=(char*)malloc(sizeof(char)*(size+1));
  for (int i=0;i<size;i++) {  
    char m= modpow(crypted[i],u,n);
    *(mot+i)=m;  
  }
  mot[size]='\0';
   
  return mot;
}