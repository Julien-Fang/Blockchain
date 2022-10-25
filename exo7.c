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
#include <openssl/sha.h>

void ecrire_block(Block *b, char *file){
    FILE *f=fopen(file,"w");//ouverture du fichier en mode ecriture
    if(f==NULL){
      printf("Erreur d'ecriture\n");
      return ;
    }
    CellProtected *cp=b->votes;
    char *cle=key_to_str(b->author);
    char *tmp;
    fprintf(f,"%s %s %s %d\n",cle,b->hash,b->previous_hash,b->nonce);//ecriture dans le fichier
    while (cp!=NULL){//ajout des declarations dans le file
      tmp=protected_to_str(cp->data);
      fprintf(f,"%s\n",tmp);
      free(tmp);
      cp=cp->next;
    }
    free(cle);
    fclose(f);
}



Block *lire_block(char *fic) {
  FILE *f = fopen(fic,"r");//ouverture du fichier en mode lecture
  if (f ==NULL) {
    printf("Erreur de lecture\n");
    return NULL;
  }
  Block *res= (Block *) malloc(sizeof(Block));//allocation d'un block
  res->votes=NULL;
  char cle[512];
  char buffer[512];
  res->hash=(unsigned char *)malloc(sizeof(unsigned char)*256);
  res->previous_hash=(unsigned char *)malloc(sizeof(unsigned char)*256);
  if (fgets(buffer,512,f)) {
    if (sscanf(buffer,"%s %s %s %d",cle,res->hash,res->previous_hash,&(res->nonce))==4) {
      while (fgets(buffer,512,f)) {
        insererp(&res->votes,str_to_protected(buffer));
     }
      res->author=str_to_key(cle);
      fclose(f);
    }
  }
return res;
}




char* block_to_str(Block *block) {

  CellProtected *tmp = block->votes;
  char* ctmp=(char*)malloc(sizeof(char)*512);
  ctmp[0]='\0';

  while (tmp) { //tant qu'il y a des declarations
    ctmp=realloc(ctmp,strlen(ctmp)+512*sizeof(char));//re allocation pour rajouter une declaration
    char* ptmp =protected_to_str(tmp->data);
    strcat(ctmp,ptmp);
    tmp=tmp->next;
    free(ptmp);
  }
  char *cle = key_to_str(block->author);
  //re allocation en prenant en compte la taille de la chaine des declarations  
  char *res= (char *) malloc(strlen(ctmp)+512*sizeof(char));
  
  sprintf(res," %s %s %s %d",cle,ctmp,block->previous_hash,block->nonce);//ajoute tous les informations dans res
  free(cle);
  free(ctmp);
  return res;
}




unsigned char * hachage(const char *chaine) {
  
  unsigned char *tmp = SHA256((unsigned char*) chaine,strlen(chaine),0);
  unsigned char *res=(unsigned char*)malloc(sizeof(unsigned char)*strlen((char*) tmp)+256);
  if(res==NULL){
    return NULL;
  }
  char l[128];
  res[0]='\0';
  int i;
  for (i=0;i<SHA256_DIGEST_LENGTH;i++)  {
    sprintf(l,"%02x", tmp[i]);
    strcat((char*) res,l);
  }
  return res; 
}



int verify_block(Block *block, int d) {
    char *bstr=block_to_str(block);
    char tabz[d+1];
    for(int i=0 ; i<d;i++){
      tabz[i]='0';
    }
    tabz[d]='\0';
    unsigned char *hash = hachage(bstr);
    hash[d]='\0';
    if (strcmp((char *)hash,tabz)==0){ 
        return 1;
    }
    return 0;
}





void compute_proof_of_work(Block *b, int d){
  b->nonce=0;
  char* data1=(char*)malloc(sizeof(char)*512); 
  int nbzero=0;
  unsigned char*hash_block;
  while( nbzero<d ){ //tant que nous n'avons pas autant de d zeros
    free(data1);
    nbzero=0;
    data1=block_to_str(b);
    hash_block = hachage(data1); // obtenir la valeur haché de la chaine
    while( hash_block[nbzero]=='0' && nbzero<d){
      nbzero++;
    }
    if(nbzero<d){
      b->nonce+=1;
    }
  }
  free(b->hash);
  free(data1);
  b->hash=hash_block;
}





void times_proof_of_work(Block *b){
  clock_t temps_i;
  clock_t temps_f;
  
  double temps_cpu=0;
  int d=0;
  FILE *f1 =fopen("temps_moyen.txt","w");

  while (temps_cpu<1.1) {
    temps_i=clock();
    compute_proof_of_work(b,d);
    temps_f=clock();
    temps_cpu=((double) (temps_f-temps_i))/CLOCKS_PER_SEC;
    fprintf(f1,"%d %f \n",d ,temps_cpu);
    d++;
  }
}




  


void delete_block(Block *b ) {
  free(b->previous_hash);
  free(b->hash);
  free(b->author);
  delete_list_protected(&b->votes);
  free(b);
}
