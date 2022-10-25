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
#include "exo9.h"
#include <dirent.h>


void submit_vote(Protected *p) {
  FILE *f = fopen("Pending_votes.txt","a"); 
  if(f==NULL){printf("Fichier invalide\n"); return; }
  char *vote = protected_to_str(p);
  fprintf(f,"%s \n",vote); // on met le vote dans le fichier
  free(vote); // on desalloue la chaine de caractere
  fclose(f); 
}

void create_block(CellTree* tree,Key* author, int d) {
   if (tree==NULL ) {
    return ;
  }
  Block *res=(Block *) malloc(sizeof(Block)); // on alloue le bloc
  CellProtected *cp= read_protected("Pending_votes.txt"); // on recupere la liste chaine dans le fichier
  res->votes=cp;
  res->author=author;
  CellTree *tmp=lastnode(tree); // on prend la plus longue chaine
  res->previous_hash=(unsigned char *)strdup((char *)tmp->block->hash); // on prend la valeur hache du noeud
  res->hash=NULL;
  compute_proof_of_work(res,d); 
  CellTree *tre=create_node(res);
  add_child(tmp,tre);
  ecrire_block(res,"Pending_block.txt"); // on cree un fichier avec le bloc
  remove("Pending_votes.txt"); // on supprime le fichier
}


void add_block(int d,char *name) {
  Block *tmp = lire_block("Pending_block.txt");

 //if ( verify_block(tmp,d) ) {
    char chemin[256]="\0";
    strcat(chemin,"./Blockchain/");
    strcat(chemin,name);  
      
    ecrire_block(tmp,chemin); // on cree un bloc dans le dossier
     
 //}
   remove("Pending_block.txt");
}

CellTree* read_tree() {
  struct dirent *dir;
  DIR *d=opendir("./Blockchain/");
  CellTree *tmp = NULL;
  Block *block=NULL;
  int n=0;
  int i=0;
  // on compte le nombre de fichiers dans le dossier
  if (d){ 
    while ((dir =readdir(d)) != NULL) {
      if ( strcmp (dir->d_name ,".")!=0 && strcmp (dir->d_name ,"..") !=0) { 
        n++;
      }
    }
    closedir(d);
  }

  CellTree *tree[n];
  for (int i=0; i<n; i++)  {
    tree[i] = NULL;
  }
  d=opendir("./Blockchain/");
  char path[1024];

  // on cree un noeud de l'arbre pour chaque bloc et on le stock dans tree
  if (d) {  
    while ((dir =readdir(d)) != NULL) {
      if ( strcmp (dir ->d_name ,".")!=0 && strcmp (dir ->d_name ,"..") !=0) {
        path[0] = '\0';
        strcat(path,"./Blockchain/");
        strcat(path,dir->d_name);
        block = lire_block(path);
        tmp = create_node(block);
        tree[i]=tmp;
        i++;
      }
    }
    closedir(d);
    
  }
  // on cherche les fils tree[j] de tree[i] grace a la valeur haché et on ajoute chaque fils tree[j] a la liste des fils du noeud tree[i]
  for (int b=0;b<n;b++) {
    for (int j=0;j<n;j++) {
      if (j!=b && strcmp((char *)tree[b]->block->hash,(char *)tree[j]->block->previous_hash)== 0) {
        add_child(tree[b],tree[j]);
    
        }
    }
  }
  // on parcourt le tableau pour trouver la racine de l'arbre qu'on retourne
  CellTree *res= (CellTree *) malloc(sizeof(CellTree));

  for (int z=0;z<n;z++) {
    if (tree[z]->father==NULL) {
      res=tree[z];
      break;
    }
  }
  return res;
}


Key* compute_winner_BT(CellTree* tree, CellKey* candidates, CellKey* voters, int sizeC,int sizeV) { 

  CellProtected *decla = fusion_longue(tree); // on extrait la liste des declarations

  supp_sgn(&decla); // on supprime les declarations non valides

  return compute_winner(decla,candidates,voters,sizeC,sizeV); // on calcul le vainqueur
}


  
