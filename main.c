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
#include <openssl/sha.h>


void print_long_vector(long *result, int size) {
  printf("Vector: [");
  for (int i=0;i<size; i++) {
    printf("%lx \t", result[i]);
  }
  printf("]\n");
  }


int main(){
  srand(time(NULL));
 
  printf("-----Exercice 1-----\n\n");

  // exo 1.2
  printf("-----Exercice 1 Question 2-----\n\n");
  //time_2ms();

  // exo 1.5
  printf("-----Exercice 1 Question 5-----\n\n");
  time_mod(5000);
  printf("-----Exercice 2-----\n\n");
  
  // Generation de cle :
  long p=random_prime_number(3,7,5000);
  long q=random_prime_number(3,7,5000);

  while (p==q) {
    q=random_prime_number(3,7,5000);
  }
  long n,s,u;
    generate_key_values(p,q,&n,&s,&u);
  if (u<0) {
    long t= (p-1)*(q-1);
    u=u+t;
  }

  printf("cle publique = (%lx, %lx) \n",s,n);
  printf("cle privee = (%lx, %lx) \n", u,n);

  char message[10]="Hello";
  int len= strlen(message);
  long *crypted = encrypt(message,s,n);
  printf("Initial message: %s \n", message);
  printf("Encoded representation : \n");
  print_long_vector(crypted,len);

  // Dechiffrement
  char *decoded=decrypt(crypted,len,u,n);
  printf("Decoded: %s\n",decoded);

  printf("\n-----Exercice 3-----\n\n");

  //test de str_to_key et key_to_str
  Key* res= str_to_key("(554102,45460546054)");
  printf("TEST1 %lx %lx \n",res->val,res->n);
  char*t1=key_to_str(res);
  printf("TEST2 %s \n\n" ,t1);



  Key *pKey=malloc(sizeof(Key));
  Key *sKey=malloc(sizeof(Key));

  //utilisation de init_key
  init_key(pKey,45,102);
  printf("init_key : (%ld,%ld)\n",pKey->val,pKey->n);
  
  //utilisation de init_pair_keys
  init_pair_keys(pKey,sKey,3,7);
  printf("pKey: %lx, %lx \n",pKey->val,pKey->n);
  printf("sKey: %lx, %lx \n",sKey->val,sKey->n);

  char *chaine=key_to_str(pKey);
  printf("key_to_str: %s \n",chaine);

  Key*k = str_to_key(chaine);
  printf("str_to_key: %lx, %lx \n", k->val, k->n);

  Key *pKeyC=malloc(sizeof(Key));
  Key *sKeyC=malloc(sizeof(Key));
  init_pair_keys(pKeyC,sKeyC,3,7);

  char *mess=key_to_str(pKeyC);
  char*t2=key_to_str(pKey); 
  printf("%s vote pour %s \n", t2,mess); 

  
  
  //utilisation de sign
  Signature *sgn=sign(mess,sKey);
  
  printf("signature: ");
  print_long_vector(sgn->content,sgn->size);

  //utilisation de signature_to_str
  char*chaine1=signature_to_str(sgn); 
  printf("signature_to_str: %s \n", chaine1);

  //utilisation de str_to_signature
  Signature*sgn1=str_to_signature(chaine1);// pb
  printf("str_to_signature: ");
  print_long_vector(sgn1->content,sgn1->size);

  //utilisation de init_protected
  Protected *pr= init_protected(pKey,mess,sgn);

  //utilisation de verify
  if (verify(pr)) {
    printf("Signature valide \n");
  }
  else {
    printf("Signature non valide \n");
  }

  //utilisation de protected_to_str
  char*chaine2=protected_to_str(pr);
  printf("protected to str %s \n",chaine2);

  //utilisation de str_to_protected
  Protected* pr1=str_to_protected(chaine2); 
  char *chaine4=signature_to_str(pr1->sgn);
 
  char *chaine5=key_to_str(pr1->pKey);
  printf("str_to_protected : %s %s %s \n", chaine5, pr1->mess,chaine4);
  

  free(crypted);
  free(decoded);
  free(res);
  free(t1);
  free(pKey);
  free(sKey);
  free(chaine);
  free(k);
  free(pKeyC);
  free(sKeyC);
  free(mess);
  free(t2);
  free(sgn->content);
  free(sgn);
  free(chaine1);
  free(sgn1->content);
  free(sgn1);
  free(pr->mess);
  free(pr);
  free(chaine2);
  free(pr1->sgn->content);
  free(pr1->sgn);
  free(pr1->pKey);
  free(pr1->mess);
  free(pr1);
  free(chaine4);
  free(chaine5);
  
  printf("\n-----Exercice 4-----\n");
  generate_random_data(10,2); 


  printf("\n-----Exercice 5-----\n");
  printf("\n\nREAD PUBLIC KEYS\n\n");
  //utilisation de read_public_keys
  CellKey * vote = read_public_keys("keys.txt");
  //utilisation de print_list_keys
  print_list_keys(vote);
  printf("\n\nFIN READ PUBLIC KEYS\n\n");


  //utilisation de read_protected
  CellProtected *decla = read_protected("declarations.txt"); 
  print_list_keys_pr(decla);
  printf("\n-----Exercice 6------\n\n");
  CellKey * candidat = read_public_keys("candidates.txt");
  Key *gg=compute_winner(decla,candidat,vote,150,150);//1free

  free(gg); 
    
  delete_list_keys(&vote);
  delete_list_protected(&decla);
  delete_list_keys(&candidat);


  printf("\n-----Exercice 7------\n\n");

  Key *pKeyy=malloc(sizeof(Key));
  init_key(pKeyy,45,102);

  CellProtected *declaa = read_protected("declarations.txt");

  Block * b=(Block*)malloc(sizeof(Block));
  b->author=pKeyy;
  b->votes=declaa;
  b->hash=NULL;
  b->previous_hash=NULL;
  b->nonce=0;
  char *bloc= block_to_str(b);
  printf("block to str : %s \n", bloc);
  b->hash=hachage(bloc);
  free(bloc);
  //times_proof_of_work(b);
  delete_block(b);

  printf("\n-----Exercice 8------\n\n");

  Key *pKey1=malloc(sizeof(Key));
  init_key(pKey1,45,50);
  CellProtected *decla1 = read_protected("declarations.txt");
  Block * b1=(Block*)malloc(sizeof(Block));
  b1->author=pKey1;
  b1->votes=decla1;
  b1->hash=NULL;
  b1->previous_hash=NULL;
  b1->nonce=1;
  char *bts1= block_to_str(b1);
  b1->hash=hachage(bts1);
  CellTree* cel1=create_node(b1);

  Key *pKey2=malloc(sizeof(Key));
  init_key(pKey2,45,50);
  CellProtected *decla2 = read_protected("declarations.txt");
  Block * b2=(Block*)malloc(sizeof(Block));
  b2->author=pKey2;
  b2->votes=decla2;
  b2->hash=NULL;
  b2->previous_hash=NULL;
  b2->nonce=2;
  char*bts2=block_to_str(b2);
  b2->hash=hachage(bts2);
  CellTree* cel2=create_node(b2);


  //compute_proof_of_work(b1,3);
  printf("-----affichage de cel1-----\n");
  print_tree(cel1,0);
  printf("\n-----ajout d'un fils-----\n");
  add_child(cel1,cel2);
  print_tree(cel1,0);


  Key *pKey3=malloc(sizeof(Key));
  init_key(pKey3,45,50);
  CellProtected *decla3 = read_protected("declarations.txt");
  Block * b3=(Block*)malloc(sizeof(Block));
  b3->author=pKey3;
  b3->votes=decla3;
  b3->hash=NULL;
  b3->previous_hash=NULL;
  b3->nonce=3;
  char*bts3=block_to_str(b3);
  b3->hash=hachage(bts3);
  CellTree* cel3=create_node(b3);
  add_child(cel1,cel3);
  printf("\n-----L'arbre-----\n");
  print_tree(cel1,0);


  printf("\n-----highest child-----\n");
  CellTree * h= highest_child(cel1);
  print_tree(h,0);


  printf("\n-----Affichage du lastnode-----\n");
  CellTree*last=lastnode(cel1);
  print_tree(last,0);


  declaa=NULL; // cas avec une declaration NULL
  printf("\n-----print declaa-----\n");
  print_list_keys_pr(declaa);
  printf("\n-----print decla1-----\n");
  print_list_keys_pr(decla1);

  printf("\n-----Fusion de declaa et decla1-----\n");
  fusion(&declaa,&decla1);

  printf("\n-----Affichage de la fusion-----\n");
  print_list_keys_pr(declaa);


  printf("\n-----Fusion longue-----\n");
   CellProtected * ff =fusion_longue(cel1);
  print_list_keys_pr(ff);

  free(bts1);
  free(bts2);
  free(bts3);
  delete_tree(cel1);
  delete_list_protected(&ff);


  printf("----------Exercice 9 -----------\n");

  generate_random_data(1000,5);

  CellProtected *decla4=read_protected("declarations.txt");
  
  CellKey * lastvotants = read_public_keys("keys.txt");

  CellKey * lastcandidats = read_public_keys("candidates.txt");
 char bloc5[256];
  int i=0;
  // on cree le premier bloc
  Block * b5=(Block*)malloc(sizeof(Block));
  b5->author=decla4->data->pKey;
  b5->votes=decla4;
  b5->hash=NULL;
  b5->previous_hash=NULL;
  int nb=0;
  compute_proof_of_work(b5,2);
  // on initialise la racine de l'arbre
  CellTree* arbre=create_node(b5);
  // on parcourt les declarations
  while (decla4) { 
    while (decla4 && i<10) { // on soumet 10 votes dans un fichier

      submit_vote(decla4->data);
      i++;
      decla4=decla4->next;
      }
  i=0;

  if (decla4) {
    create_block(arbre,decla4->data->pKey,2); // creation du bloc 
    sprintf(bloc5,"bloc%d.txt",nb);
    add_block(2,bloc5); // ajout du bloc dans la blockchain
    nb++;
    }
  }

  CellTree *treee=read_tree(); // lecture 
  print_tree(treee,0); // affichage
  Key *clee =compute_winner_BT(treee,lastcandidats,lastvotants,1700,1700); // vainqueur !
 
  delete_tree(treee);
  free(clee);
  delete_list_protected(&decla4);
  delete_list_keys(&lastcandidats);
  delete_list_keys(&lastvotants);

  return 0;

}