#ifndef EXO1_H
#define EXO1_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long random_prime_number(int low_size, int up_size, int k);
long rand_long ( long low , long up);
int witness ( long a, long b, long d, long p);
int modpow(long a,long m,long n);
long modpow_naive(long a,long m,long n);
int is_prime_miller ( long p, int k);
int is_prime_naive(long p);
void time_2ms();
void time_mod(int m);
#endif
