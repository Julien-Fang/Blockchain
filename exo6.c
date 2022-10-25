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


void supp_sgn(CellProtected **cp)  {
  //supprime les votes non verifies
  if (!(*cp))
    return;
  CellProtected *tmp = *cp;
  CellProtected *prec = tmp;
  CellProtected *cour = tmp->next;
  if (!verify(tmp->data)==0) {
    *cp = tmp->next;
    delete_cell_protected(tmp);
  }
  while (cour){
    if (verify(cour->data)==0){
      prec->next = cour->next;
      delete_cell_protected(cour);    
    }
    else{
      prec = cour;
    }
      cour = prec->next;
  }
}



HashCell* create_hashcell(Key *key) {
  HashCell *res=(HashCell *) malloc(sizeof(HashCell)); // alloue la cellule de hachage
  if(res==NULL){
    return NULL;
  }
  res->key= key; 
  res->val=0;
  return res;
}



int hash_function(Key *key , int size) {
  return (key->val+key->n)%size; //retourne la position de la clef dans la table de hachage
}



int find_position(HashTable *t, Key *key)   {
    int ind = hash_function(key, t->size);
    int i=0;
    if (t->tab[ind]==  NULL) {
    return ind;
    }
    while(i < t->size)    {
      if (t->tab[(ind + i) % t->size] != NULL) {
        if (  (t->tab[(ind + i) % t->size]->key->val == key->val) && (t->tab[(ind + i) % t->size]->key->n == key->n)  ) {
          return (ind + i) % t->size;
        } 
      } 
      else{ 
        return (ind + i) % t->size;
      }
      i++;
    }
  return -1;  //indication d'erreur
}


HashTable* create_hashtable(CellKey* keys, int size) {
  HashTable* res = (HashTable *) malloc(sizeof(HashTable)); // on alloue la table de hachage
  if(res==NULL){
    return NULL;
  }

  res->tab= (HashCell **) malloc(sizeof(HashCell *)*size); 
  res->size=size;

  for (int i=0;i<size;i++) { // on met tout les elements a NULL
    res->tab[i]=NULL;
  }

  int pos;
  while (keys) { // on parcourt keys et on met chaque cellule dans la table de hachage crée
    pos=find_position(res,keys->data); 
    if(pos==-1){
      return res;
    }

    (res->tab)[pos] = create_hashcell(keys->data);

    keys=keys->next;
  }

  return res;
}


void delete_hashtable(HashTable* t) {
  for (int i=0;i<t->size; i++) {
    if (t->tab[i] != NULL)
      free(t->tab[i] ); // on libere toutes les cases de la table de hachage
  }
  free(t->tab); 
  free(t); 
}


Key* compute_winner(CellProtected* decl, CellKey* candidates,CellKey*voters,int sizeC,int sizeV) {
   HashTable * HC= create_hashtable(candidates,sizeC); // creation liste candidats
   HashTable * HV = create_hashtable(voters,sizeV); // creation liste votants

   int pv; // position votant
   int pc; // position candidat
   while (decl) { // parcours des declarations
    
     pv=find_position(HV,decl->data->pKey);
     if(pv!=-1){
      if (HV->tab[pv]!= NULL)   {

        if (HV->tab[pv]->val==0) { // si le votant n'a pas voté

          Key *ck=str_to_key(decl->data->mess);
          pc= find_position(HC,ck);
          if(pc!=-1){
            if(HC->tab[pc] != NULL) {  

              HV->tab[pv]->val = 1; // il a maintenant voté
              HC->tab[pc]->val++; // un vote de plus pour la valeur du candidat
            }
          free(ck); // on libere la clef
          }
        }
      }
     }
     decl=decl->next;
}
    Key *res=(Key *) malloc(sizeof(Key)); // la clef qu on va retourner
    int n=-1; // compteur du nombre de votes max par candidat

    for (int i=0; i<HC->size; i++)  {

      if (HC->tab[i] != NULL && n< HC->tab[i]->val ){ // si le candidat a plus de votes que l ancien

        init_key(res,HC->tab[i]->key->val,HC->tab[i]->key->n);
        n = HC->tab[i]->val;    
      }
    }
  char *g=key_to_str(res); //(pour afficher le gagnant et test)
  printf("Le grand gagnant est : %s avec comme nombre de votes : %d \n",g, n);
  delete_hashtable(HV); // on libere les deux tables de hachages
  delete_hashtable(HC);
  free(g);
  return res;
}
