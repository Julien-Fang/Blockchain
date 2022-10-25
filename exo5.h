#ifndef EXO5_H
#define EXO5_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "exo1.h"
#include "exo2.h"
#include "exo3.h"
#include "exo4.h"

typedef struct cellKey {
  Key* data;
  struct cellKey* next;
}CellKey;

typedef struct cellProtected {
  Protected *data;
  struct cellProtected* next;
}CellProtected;

CellKey* create_cell_key(Key *key);
void inserer(CellKey **ckey, Key *key);
CellKey* read_public_keys(char* fic);
void print_list_keys(CellKey* LCK);
void delete_cell_key(CellKey* c);
void delete_list_keys(CellKey** c);
CellProtected* create_cell_protected(Protected *pr);
void insererp(CellProtected **ckey, Protected *pr);
CellProtected* read_protected(char* fic);
void print_list_keys_pr(CellProtected* LCK);
void delete_cell_protected(CellProtected *cp);
void delete_list_protected(CellProtected **cp);

#endif
