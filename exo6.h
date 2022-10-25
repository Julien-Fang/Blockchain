#ifndef EXO6_H
#define EXO6_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "exo1.h"
#include "exo2.h"
#include "exo3.h"
#include "exo4.h"
#include "exo5.h"

typedef struct hashcell {
  Key *key;
  int val;
} HashCell;

typedef struct hashtable{
  HashCell** tab;
  int size;
} HashTable;


void supp_sgn(CellProtected **c);
HashCell* create_hashcell(Key *key);
int hash_function(Key *key , int size);
int find_position(HashTable* t, Key* key);
HashTable* create_hashtable(CellKey* keys, int size); 
void delete_hashtable(HashTable* t);
Key* compute_winner(CellProtected* decl, CellKey* candidates,CellKey*voters,int sizeC,int sizeV);
int occurence_key(Key *key,CellKey *list);
#endif