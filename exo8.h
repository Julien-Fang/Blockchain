#ifndef EXO8_H
#define EXO8_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "exo1.h"
#include "exo2.h"
#include "exo3.h"
#include "exo4.h"
#include "exo5.h"
#include "exo7.h"


typedef struct block_tree_cell {
  Block* block;
  struct block_tree_cell* father;
  struct block_tree_cell* firstChild;
  struct block_tree_cell* nextBro;
int height;
}CellTree;


CellTree* create_node(Block* b);
int update_height(CellTree *father, CellTree* child);
void add_child(CellTree *father,CellTree* child);
void print_tree(CellTree* tree,int e);
void delete_node(CellTree *node);
void delete_tree(CellTree *tree);
CellTree* highest_child(CellTree* cell);
CellTree * lastnode(CellTree*tree);
void fusion(CellProtected **ds1, CellProtected **ds2);
CellProtected* fusion_longue(CellTree *tree);



#endif