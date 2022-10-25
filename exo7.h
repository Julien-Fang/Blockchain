#ifndef EXO7_H
#define EXO7_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "exo1.h"
#include "exo2.h"
#include "exo3.h"
#include "exo4.h"
#include "exo5.h"

typedef struct block {
  Key *author;
  CellProtected* votes;
  unsigned char* hash;
  unsigned char* previous_hash;
  int nonce;
}Block;


void ecrire_block(Block *b, char *file);
Block *lire_block(char *fic);
char* block_to_str(Block *block);
int verify_block(Block *block, int d);
unsigned char * hachage(const char *chaine);
void compute_proof_of_work(Block *b, int d);
void times_proof_of_work(Block *b);
void delete_block(Block *b );

#endif