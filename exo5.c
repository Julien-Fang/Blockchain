#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "exo1.h"
#include "exo2.h"
#include "exo3.h"
#include "exo4.h"
#include "exo5.h"


CellKey * create_cell_key(Key *key) {
  CellKey * res = (CellKey *) malloc(sizeof(CellKey)); // on alloue
  if(res==NULL){
    return NULL;
  }
  res->data= malloc(sizeof(Key)); // on alloue la cle
  init_key(res->data,key->val,key->n);//initialisation de res->data
  res->next=NULL;
  return res;
}



void inserer(CellKey** ckey, Key* key) {
  CellKey* tmp = create_cell_key(key); // on cree une cle
  tmp->next = *ckey;
  *ckey = tmp; //ajout en en-tete du nouveau element
}



CellKey* read_public_keys(char* fic) {
  FILE * f=fopen(fic,"r");
  if (f==NULL) { // s'il y a probleme de fichier
    printf("Probleme ouverture fichier");
  return NULL;
  }
  CellKey *res=NULL;
  char buffer[256];
  Key *key=(Key *) malloc(sizeof(Key));
  if (strcmp(fic,"candidates.txt")==0 || strcmp(fic,"keys.txt")==0) {
    while (fgets(buffer,256,f)!=NULL) { 
      if (sscanf(buffer,"(%lx,%lx)",&(key->val),&(key->n))==2) { 
        inserer(&res,key); // on insere la cle cree dans res
      }
      else {
        printf("Format de ligne incorrect");
        return NULL;
      } 
    }  
  }
  free(key);
  fclose(f);
  return res;
}



void print_list_keys(CellKey* LCK) {//affichage d'un CellKey
  CellKey*tmp = LCK;
  while (tmp!=NULL) {
    printf("(%lx,%lx)\n", tmp->data->val,tmp->data->n);
    tmp=tmp->next;
  }
}



void delete_cell_key(CellKey * c) {
  if (c==NULL) {  
    return;
  }
  free(c->data); // on desalloue la cle
  free(c); // on desalloue la cellule
}



void delete_list_keys(CellKey** c) {//supprime un CellKey
  if (*c==NULL) {
    return ;
  }
  CellKey* tmp = *c;
  while (tmp) {
    (*c)=(*c)->next;
    delete_cell_key(tmp);  
    tmp=*c;
  }
}



CellProtected* create_cell_protected(Protected *pr) {
  CellProtected* res = (CellProtected *) malloc(sizeof(CellProtected));
  if(res==NULL){
    return NULL;
  }
  res->data=pr;
  res->next=NULL;
  return res;
}



void insererp(CellProtected **ckey, Protected *pr) {//insertion en en-tete
  CellProtected *res = create_cell_protected(pr);
  res->next=*ckey;
  *ckey=res;}



CellProtected* read_protected(char* fic) {
  FILE * f=fopen(fic,"r");
  if (f==NULL) { // s'il y a probleme de fichier
  printf("Probleme ouverture fichier");
  return NULL;
  }
  CellProtected *res=NULL;
  char buffer[256];

  Protected *p;
  while (fgets(buffer,256,f)!=NULL) { 
    p=str_to_protected(buffer);
    insererp(&res,p); // on insere le protected dans res
      
    }  
  fclose(f);
  return res;
}



void print_list_keys_pr(CellProtected* LCK) {
  char*c1;
  char *c2;
  char*tmp;
  CellProtected*cour = LCK;
  while (cour!=NULL ) {
    c2=key_to_str(cour->data->pKey);
    c1 = strdup(cour->data->mess);
    tmp= signature_to_str(cour->data->sgn);
    printf("%s %s %s \n",c2,c1 ,tmp);
    cour=cour->next;
    free(tmp);
    free(c1);
    free(c2);
  }
}



void delete_cell_protected(CellProtected *cp) {
  if (cp==NULL) {
    return;
  }
  free(cp->data->sgn->content); // on desalloue le tableau de long
  free(cp->data->sgn); // on desalloue la signature
  free(cp->data->mess); // on desalloue le message
  free(cp->data->pKey); // on desalloue la cle
  free(cp->data);  // on desalloue le protected
  free(cp); // on desalloue la cellule
}



void delete_list_protected(CellProtected ** cp){
  if (cp != NULL){
    CellProtected * tmp;
    while (*cp){
      tmp = (*cp)->next;
      delete_cell_protected(*cp);
      *cp = tmp;
    }
  }
}
  