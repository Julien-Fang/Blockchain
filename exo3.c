#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "exo1.h"
#include "exo2.h"
#include "exo3.h"


void init_key(Key* key , long val, long n) {//initialise une clé, la clé a deja été allouée
  key->val=val;
  key->n=n;
}

void init_pair_keys(Key* pKey, Key* sKey, long low_size,long up_size) {
  
  long p=random_prime_number(low_size,up_size,5000);//genere un p premier
  long q=random_prime_number(low_size,up_size,5000);//genere un q premier

  while (p==q) {
    q=random_prime_number(low_size,up_size,5000);
  }
  long n,s,u;
    generate_key_values(p,q,&n,&s,&u);
  if (u<0) {
    long t= (p-1)*(q-1);
    u=u+t;
  }
  init_key(pKey,s,n);//initialise la clé public
  init_key(sKey,u,n);//initialise la clé secrete
}



char* key_to_str(Key *key) {//revoie une chaine de la clé
  char *buffer = (char *) malloc(sizeof(char)*512);
  sprintf(buffer,"(%lx,%lx)",key->val,key->n); 

  return buffer;
}



Key* str_to_key(char *str) {//renvoie une clé a l'aide de la chaine de type (x,y)
  Key *res= (Key *) malloc(sizeof(Key));
  sscanf(str,"(%lx,%lx)",&(res->val),&(res->n)); 
  return res;
}



Signature* init_signature(long * content, int size) {//renvoie une Signature
  Signature * s = (Signature *) malloc(sizeof(Signature));//allocation de s de type Signature
  if (s==NULL) {
    return NULL;
  }
  s->content = content;
  s->size=size;

  return s;
}



Signature *sign(char *mess,Key* sKey) {
  long * tmp =encrypt(mess,sKey->val,sKey->n);//creation d'un tableau de long en le cryptant
  Signature *res= init_signature(tmp,strlen(mess));

  return res;//retourne une signature grace a la fonction init_signature
}



char* signature_to_str(Signature* sgn) {
  char *result = malloc(100*sgn->size*sizeof(char));
  result[0]='#';
  int pos=1;
  char buffer[156];
  for (int i=0;i<sgn->size;i++) {
    sprintf(buffer,"%lx",sgn->content[i]);
    for (int j=0;j<strlen(buffer);j++) {
      result[pos]=buffer[j];
      pos=pos+1;
    }
    result[pos]='#';
    pos=pos+1;
  }
  result[pos]='\0';

  result=realloc(result,(pos+512)*sizeof(char));
  return result;
}




Signature * str_to_signature(char *str) {
  int len=strlen(str);
  long *content=(long *) malloc(sizeof(long)*len);
  int num=0;
  char buffer[256];
  int pos=0;
  for (int i=0;i<len;i++) {
    if (str[i]!= '#') {
      buffer[pos]=str[i];
      pos=pos+1;
    }else {
        if (pos!=0) {
          buffer[pos]='\0';
          sscanf(buffer,"%lx", &(content[num]));
          num=num+1;
          pos=0;
        }
    }
  }
  content=realloc(content,num*sizeof(long));

  return init_signature(content,num);
}



Protected* init_protected(Key* pKey, char *mess, Signature * sgn) {// initialisation de protected
  Protected * res= (Protected *) malloc(sizeof(Protected));
  res->pKey=pKey;
  res->mess=strdup(mess);//permet d'allouer et de copier mess
  res->sgn=sgn;

  return res;
}



int verify(Protected* pr) {
  char* msg = decrypt(pr->sgn->content, pr->sgn->size, pr->pKey->val, pr->pKey->n); //decrypt pour recuperer le message
  if (strcmp(msg, pr->mess) == 0) {//comparer l'egalité des 2 messages
      free(msg);
      return 1;
  }
  free(msg);
   return 0;
}



char* protected_to_str(Protected *pr) {
  char *res;
  char buffer[256];
  char*str=key_to_str(pr->pKey);
  char*str1=signature_to_str(pr->sgn);
  sprintf(buffer,"%s %s %s",str, pr->mess, str1); //recuperation de pr dans une chaine buffer
  free(str);
  free(str1);
  res=strdup(buffer);
  return res;
}



Protected *str_to_protected(char *str) {//renvoie une Protection
  char key[256];
  char mess[256];
  char sgn[256];
  sscanf(str," %s %s %s",key,mess,sgn);//recupere les valeurs et on les met dans key,mess,sgn
  Signature *s= str_to_signature(sgn);//creation d'une signature
  Key *cle= str_to_key(key);//creation d'une clé
  Protected *res=init_protected(cle,mess,s);

  return res;
  }



void delete_pr(Protected *p) {
  if (p==NULL) {
    return;
  }
  free(p->sgn->content); 
  free(p->sgn); 
  free(p->mess);
  free(p->pKey);
  free(p); 
}