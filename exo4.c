#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "exo1.h"
#include "exo2.h"
#include "exo3.h"
#include "exo4.h"


void generate_random_data(int nv, int nc) {
  srand(time(NULL));
  //creation de 3 tableau pour stocker
  char**Ptab=(char**)malloc(sizeof(char*)*nv);//tableau des clées publiques en chaine
  char**Stab=(char**)malloc(sizeof(char*)*nv);//tableau des clées secretes en chaine
  char**Ctab=(char**)malloc(sizeof(char*)*nc);//tableau des clées publiques en chaine des candidats

   
  for (int i=0;i<nv;i++) { //boucle pour recuperer les nv clées tels qu'ils sont tous differentes
    Key*sKey=(Key*)malloc(sizeof(Key));
    Key*pKey=(Key*)malloc(sizeof(Key));
    char*str1;
    char*str2;
    init_pair_keys(pKey,sKey, 3,7);//initialiser clées publiques et secrete

    int a=0;
    for(int e=0; e<i;e++){ // boucle pour verifier si les clées que nous avons initialisé existent deja
      str1=key_to_str(sKey); // conversion des clées en chaine
      str2=key_to_str(pKey); // conversion des clées en chaine
      if( a==0 && ( Ptab[e]==str2 || Stab[e]==str1 || Ptab[e]==Stab[e] )){ // le cas si les clées existe deja
        i--;
        a=1;
      }
      free(str1); //libération de l'allocation
      free(str2); //libération de l'allocation
    }
    if(a==0){// le cas si les clés n'existe pas dans les tableaux
      Stab[i]=key_to_str(sKey);
      Ptab[i]=key_to_str(pKey);
      }
      a=0;
      free(sKey);
      free(pKey);
    }

  FILE * f=fopen("keys.txt","w"); //ouverture/creation du fichier keys.txt
  for(int i=0; i< nv ; i++){ // boucle pour recuperer les clées publiques et secretes de chaque electeurs
    fprintf(f,"%s %s \n",Ptab[i],Stab[i]);
  }
  fclose(f);
  
  f=fopen("candidates.txt","w");
  int cpt=0;
  while(cpt<nc){ // recuperer les clées publiques des candidats selectionnés aléatoirement avec p
    int p=(int)(rand()%nv);
    fprintf(f,"%s \n",Ptab[p]);
    Ctab[cpt]=Ptab[p];
    cpt++;
  }
  fclose(f);

  f=fopen("declarations.txt","w");

  for(int e=0;e<nv;e++){
    int rdm=(int)(rand()%nc);
    char*c=Ctab[rdm];// clé publique du candidat
    Key *k=str_to_key(Stab[e]);
    Signature* s1=sign(c,k);//avoir la signature avec la clé publique du candidat en chaine et la clé secrete de l'electeur
    Key *kp=str_to_key(Ptab[e]);
    Protected*decla=init_protected(kp,c,s1); //avoir sa declaration avec le vote de l'electeur, la signature et la clé publique de l'electeur

 
    char*d=signature_to_str(decla->sgn);
    fprintf(f,"%s %s %s \n",Ptab[e],c,d);
    free(d);

    free(k);
    free(s1->content);
    free(s1);
    free(kp);
    free(decla->mess);
    free(decla);

    }
  fclose(f);
 
  for(int i=0; i<nv; i++) {//boucle pour liberer tous les elements des tableaux
    free(Ptab[i]);
    free(Stab[i]);
  }
  free(Stab);
  free(Ptab);
  free(Ctab);
}