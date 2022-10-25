#ifndef EXO3_H
#define EXO3_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


typedef struct key{
  long val;
  long n;
} Key;

typedef struct signature {
  long *content;
  int size;
  
}Signature;

typedef struct protectedd {
  Key *pKey;
  Signature *sgn;
  char *mess;
}Protected;


void init_key(Key* key , long val, long n);
void init_pair_keys(Key* pKey, Key* sKey, long low_size,long up_size);
char* key_to_str(Key *key);
Key* str_to_key(char *str);
Signature* init_signature(long * content, int size);
Signature *sign(char *mess,Key* sKey);
char* signature_to_str(Signature* sgn);
Signature * str_to_signature(char *str);
Protected* init_protected(Key* pkey, char *mess, Signature * sgn);
int verify(Protected* pr);
char* protected_to_str(Protected *pr);
Protected *str_to_protected(char *str);
void delete_pr(Protected *p);

#endif