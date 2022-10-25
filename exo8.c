#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "exo1.h"
#include "exo2.h"
#include "exo3.h"
#include "exo4.h"
#include "exo5.h"
#include "exo6.h"
#include "exo7.h"
#include "exo8.h"

//creation d'un CellTree a partir d'un Block
CellTree* create_node(Block* b) {
  CellTree *res = (CellTree *) malloc(sizeof(CellTree));
  res->block=b;
  res->father=NULL;
  res->firstChild=NULL;
  res->nextBro=NULL;
  res->height=0;
  return res;
}



//mise a jour de la hauteur
int update_height(CellTree *father, CellTree* child) {
 if (father->height<child->height+1) {
    father->height = child->height+1;
    return 1;
  } 
  return 0;
}



void add_child(CellTree *father,CellTree* child) {
  CellTree * cour1=father->firstChild;
  child->father=father;
  if( cour1==NULL){//si le pere n'a pas de firstChild
    father->firstChild=child;
  }
  else{//si le pere a un firstChild
    CellTree *cour=father->firstChild;
    while(cour->nextBro != NULL){//on parcours jusqu'a etre la fin des frères du firstChild
      cour=cour->nextBro;
    }
    cour->nextBro=child;

  }
  update_height(father,child);//mise à jour de leur hauteur
  
  CellTree*cour2=father;
  while(cour2 !=NULL && cour2->father!=NULL){ //mise a jour de la hauteur des ascendants
    update_height(cour2->father,cour2);
    cour2=cour2->father;
  }
}

void print_tree(CellTree*tree, int e){//tjrs debuter e à 0 
  if(tree==NULL){
    return;
  }

  for(int i=0; i<e; i++){
    printf("  ");
  }

  printf("[%d %s]\n", tree->height, tree->block->hash);
  CellTree * tmp=tree->firstChild;
  while(tmp!=NULL){
    print_tree(tmp,e+1);
    tmp=tmp->nextBro;
  }
}




void delete_node(CellTree *node) {
  //suppression d'un noeud
  if(node!=NULL){
  delete_block(node->block); 
  free(node);
  }
}




void delete_tree(CellTree * tree){
  //suppression d'un CellTree de maniere recursive
  if(tree!=NULL){
    delete_tree(tree->nextBro);
    delete_tree(tree->firstChild);
    delete_node(tree);
  }
}




CellTree* highest_child(CellTree* cell) {
  //renvoie le CellTree ayant la plus grande hauteur
  if(cell==NULL){return NULL;}

  CellTree *c=cell->firstChild;
  CellTree *cour= c;
  while(cour!=NULL){//parcours les nextbro du firstChild du pere
    if(cour->height>=c->height){
      c=cour;
    }
    cour=cour->nextBro;
  }
return c;
}



CellTree * lastnode(CellTree*tree){
  if(tree->firstChild!=NULL){//tant qu'il y a un firstChild
      return lastnode(highest_child(tree));//parcours recursive à l'aide de la fonction highest_child
  }
  else{ 
    return tree;//renvoie lorsqu'il n y a plus de firstChild
  }
}





void fusion(CellProtected **ds1, CellProtected **ds2){
  if(*ds1!=NULL && ds2!=NULL){
    CellProtected *cour1= *ds1; 
    while(cour1->next!=NULL){//parcours jusqu'a etre a la fin de ds1
      cour1=cour1->next;
    }
    cour1->next=*ds2;
    *ds2=NULL;
  }
  if(*ds1==NULL){
    *ds1=(*ds2)->next;
    *ds2=NULL;
  }
}




CellProtected* fusion_longue(CellTree *tree){
  //creation d'un nouveau CellProtected étant la plus longue
  CellProtected *res = NULL;
  CellTree*cour=tree;
  while(cour!=NULL){
    fusion(&res,&cour->block->votes);//ajout des declarations dans res
    cour=highest_child(cour);//recuperer le CellTree le plus long
  }
  return res;
}

