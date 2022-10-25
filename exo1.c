#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "exo1.h"


int is_prime_naive(long p) { // fonction permettant de verifier si la valeur p est premier =1 ou non=0
  if (p%2==0) { 
    return 0;
  }
  for (int i=3;i<p;i++) {
    if (p%i==0) return 0;
  }
  return 1;
}



long modpow_naive(long a,long m,long n) { //complexité pire cas en n
  int res=1;
  if (a==n) {
    return 0;
  }
  for (int i=0;i<m;i++) {
    res*=a%n;
  }
  return res%n;
}



int modpow(long a,long m,long n) {
  if (m==0) {
    return 1;
   }
   if (m==1) {
     return a%n;
   }
   int tmp= modpow(a,m/2,n)%n;
   if(m%2==0 ) { 
     return (tmp*tmp)%n; 
   }
   else{ 
     return (tmp*tmp*a)%n; 
   }
}



int witness ( long a, long b, long d, long p) {
 long x = modpow (a,d,p);
 if(x == 1){
   return 0; }
 for( long i = 0; i< b; i++){
   if(x == p -1){
     return 0;
    }
  x = modpow (x,2,p);
 }
 return 1;
}



long rand_long ( long low , long up) // retourn un entier aléatoire etre low et up
{
  return rand () % (up - low +1)+ low;
 }



int is_prime_miller ( long p, int k) {//permet de savoir si p est premier (forte chance)
  if (p == 2) {
    return 1;
  }
  if (!( p & 1) || p <= 1) { //on verifie que p est impair et different de 1
    return 0;
  }
 //on determine b et d :
  long b = 0;
  long d = p - 1;
  while (!( d & 1)){ //tant que d n’est pas impair
   d = d/2;
   b=b+1;
  }
 // On genere k valeurs pour a, et on teste si c’est un temoin :
  long a;
  int i;
  for(i = 0; i < k; i++){
    a = rand_long (2, p -1);
  if( witness (a,b,d,p)){
    return 0;
   }
 }
 return 1;
}



long random_prime_number(int low_size, int up_size, int k) {
  long low=1;
  for(int i=0 ; i<low_size ; i++ ){//on genere une valeur équivaut a 2^(low_size-1)
    low*=2;
  }
  long up=1;
  for(int i=0; i<up_size+1 ; i++){// on genere une valeur équivaut a 2^(low_size)
    up*=2;
  }
  long r=rand_long(low,up-1);//recupere une valeur aléatoire entre 2^(low_size-1) et 2^(low_size)-1

  while((is_prime_miller(r,k)!=1)){//tant que r n'est pas premier, il continue de générer des valeurs
    r=rand_long(low,up-1);
  }
    return r;
}



void time_2ms() {
  clock_t temps_i1;
  clock_t temps_f1;
  double temps_cpu1=0;
  double temps_res;
  long z=0;
  int i=295000;
  while (temps_cpu1<0.002) {
    temps_i1=clock();
    z=is_prime_naive(i);
    temps_f1=clock();
    temps_res=temps_cpu1;
    if (z) {
    temps_cpu1=((double) (temps_f1-temps_i1))/CLOCKS_PER_SEC;
      }
    i+=1;

   }
   printf("%f %d \n", temps_res,i-1);
}



void time_mod(int m) {

  clock_t temps_i1;
  clock_t temps_f1;
  clock_t temps_i2;
  clock_t temps_f2;

  double temps_cpu1;
  double temps_cpu2;

    FILE*f = fopen("mod.txt","w");
  int a=25445504;
  int n=15544;
  for(int i=1; i<m ; i++){

    i*=10;
    temps_i1=clock();
    int tmp1=modpow_naive(a,i,n);
    temps_f1=clock();
    temps_cpu1=(double) (temps_f1-temps_i1)/CLOCKS_PER_SEC;

    temps_i2=clock();
    int tmp2 =modpow(a,i,n);   
    temps_f2=clock();
    temps_cpu2=(double) (temps_f2-temps_i2)/CLOCKS_PER_SEC;
    
    fprintf(f,"%d %f %f \n",i, temps_cpu1,temps_cpu2);
  }
  fclose(f);
}

