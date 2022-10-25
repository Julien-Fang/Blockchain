#ifndef EXO9_H
#define EXO9_H
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
#include "exo8.h"

void submit_vote(Protected* p);
void create_block(CellTree* tree, Key* author, int d);
void add_block(int d,char *name);
CellTree* read_tree();
Key* compute_winner_BT(CellTree* tree, CellKey* candidates, CellKey* voters, int sizeC,int sizeV);

#endif