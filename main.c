#include "fonctions.h"

int main(int argc,char** argv){

  int retour = 0;
  FILE* csv; //fichier d'entrée
  FILE* sortie; //fichier de sortie
  time_t debut, fin; //variable pour le temps d'execution
  int int_exclusivite; //varible qui contient l'argument entre -t/-w/-m/-p
  int int_m; //variable qui contient le mode de -t et de -p
  int int_entree; //variable qui contient l'argument de -i
  int int_sortie; //variable qui contient l'argument de -o
  int int_g; //variable qui contient l'argument de -g
  int int_a; //variable qui contient l'argument de -a
  int int_d; //variable qui contient l'argument de -d
  int int_min; //variable qui contient le minimum
  int int_max; //variable qui contient le maximum
  int int_retour; //variable qui contient la réussite ou l'échec de la fonction
  int int_argument; //pour garder l'argument souhaité
  int verif;
  int int_help;

  char* char_entree; //variable qui contient l'argument de -i
  char* char_sortie; //variable qui contient l'argument de -o
  char* tmp;
  char* tmp1;
  //Initialisation des variables
  char_entree = '\0';
  char_sortie = '\0';
  int_g = 0;
  int_a = 0;
  int_d = 0;
  int_exclusivite = 0;
  int_m = 0;
  int_sortie = 0;
  int_entree = 0;
  int_min = 0;
  int_max = 0;
  int_retour = 0;
  int_argument = 0;
  int_help = 0;
  debut = time(NULL); //Prend le temps au lancement du programme.

  recuperation_arguments(argv,argc,&int_exclusivite,&int_m,&int_entree,&int_sortie,&char_entree,&char_sortie,&int_min,&int_max,&int_g,&int_a,&int_d);
  int_retour = validation_arguments(argv,argc,&int_exclusivite,&int_m,&int_entree,&int_sortie,&char_entree,&char_sortie,&int_min,&int_max,&int_g,&int_a,&int_d,&int_argument);
  int_help = help(argv,argc);

  if(int_retour==0){
    //on vérifie le retour pour pas d'erreur de segmentation
    csv = fopen(char_entree,"r"); //Ouvre le csv source
    sortie = fopen(char_sortie,"w+"); //créé le csv en sortie

    if ((csv == NULL || sortie == NULL)){
      //erreur de fichier
      int_retour = 6;

    }else{
      printf("%s\n", "calcul des lignes...");
      //On récup le nombre de lignes
      int lignes = nbLignes(csv);
      //On créer notre tableau pour stocker
      if(int_argument==1){
        //VENT
        Wind* tab = malloc(sizeof *tab * lignes);
        //Rewind permet de replacer le curseur au début du csv
        //Comme on l'a parcouru dans nbLignes(), on doit l'appeler ici
        rewind(csv);
        //On récupère les données voulue pour -p
        tab = recupWind(csv,tab);
        //Tri fusion
        printf("%s\n", "Tri des valeurs...");
        fusionTrieWind(tab,0,lignes-1);
        //Ecriture des valeurs triées
        printf("%s\n", "Ecriture des valeurs...");

        float moyVitesse = 0;
        float moyOrient = 0;
        int cmpt = 1;

        //On parcourt notre tableau
        for (int i = 1; i < lignes-1; i++) {
          verif = 0;
          //On s'assure qu'il n'écrive aucune valeurs nulles
          if (tab[i].station != 0) {
            //on récupère les coordonnées
            tmp = recupColonne(tab[i].coords,1);
            tmp1 = recupColonne(tab[i].coords,2);
            //on vérifie les options
            if(int_d==1){
              if(((int_min*100)>tab[i].date)||((int_max*100)<tab[i].date)){
                verif=1;
              }
            }if(int_a==1){
              if((int_min>atof(tmp)||(int_max<atof(tmp)))){
                verif=1;
              }
            }if(int_g==1){
              if((int_min>atof(tmp1))||(int_max<atof(tmp1))){
                verif=1;
              }
            }
            //on fait les moyennes
            moyVitesse += tab[i].vitesse;
            moyOrient += tab[i].orientation;
            //le diviseur des moyennes
            cmpt++;
            if((verif==0) && (tab[i-1].station != tab[i].station)){
              //fprintf pour écrire dans le csv sortie
              fprintf(sortie,"%d;%d;%f;%f;%s\n", tab[i].station,tab[i].date,moyOrient/cmpt,moyVitesse/cmpt,tab[i].coords);
              moyVitesse = 0;
              moyOrient = 0;
              cmpt = 1;
            }
            //on free tout en boucle
            free(tmp);
            free(tmp1);
            free(tab[i].coords);
        }
      }
  }else if(int_argument==2){
      //HAUTEUR
      Hauteur* tab = malloc(sizeof *tab * lignes);
      //Rewind permet de replacer le curseur au début du csv
      //Comme on l'a parcouru dans nbLignes(), on doit l'appeler ici
      rewind(csv);
      //On récupère les données voulue pour -p
      tab = recupHauteur(csv,tab);
      //Tri fusion
      printf("%s\n", "Tri des valeurs...");
      fusionTrieHauteurStation(tab,0,lignes-1);
      fusionTrieHauteur(tab,0,lignes-1);
      //Ecriture des valeurs triées
      printf("%s\n", "Ecriture des valeurs...");
      //On parcourt notre tableau
      for (int i = 1; i < lignes-1; i++) {
        verif = 0;
        //On s'assure qu'il n'écrive aucune valeurs nulles
        if (tab[i].hauteur != 0) {
          //on récupère les coordonnées
          tmp = recupColonne(tab[i].coords,1);
          tmp1 = recupColonne(tab[i].coords,2);
          //on vérifie les options
          if(int_d==1){
            if(((int_min*100)>tab[i].date)||((int_max*100)<tab[i].date)){
              verif=1;
            }
          }if(int_a==1){
            if((int_min>atof(tmp)||(int_max<atof(tmp)))){
              verif=1;
            }
          }if(int_g==1){
            if((int_min>atof(tmp1))||(int_max<atof(tmp1))){
              verif=1;
            }
          }
          if(verif==0){
            //on vérifie qu'on ai pas deux fois la même station
            if(tab[i-1].station!=tab[i].station){
              fprintf(sortie,"%d;%d;%f;%s\n", tab[i].station,tab[i].date,tab[i].hauteur,tab[i].coords);
            }
          }
          //on free tout
          free(tmp);
          free(tmp1);
          free(tab[i].coords);
        }
      }
    }else if(int_argument==3){
      //HUMIDITE
      Humide* tab = malloc(sizeof *tab * lignes);
      //Rewind permet de replacer le curseur au début du csv
      //Comme on l'a parcouru dans nbLignes(), on doit l'appeler ici
      rewind(csv);
      //On récupère les données voulue pour -p
      tab = recupHumide(csv,tab);

      //Tri fusion
      printf("%s\n", "Tri des valeurs...");
      fusionTrieHumide(tab,0,lignes-1);
      fusionTrieHumideStation(tab,0,lignes-1);
      //fusionTrieHumide(tab,0,lignes-1);
      //Ecriture des valeurs triées
      printf("%s\n", "Ecriture des valeurs...");
      //On parcourt notre tableau
      int stationActuel = -1;
      for (int i = 1; i < lignes-1; i++) {
        //On s'assure qu'il n'écrive aucune valeurs nulles
        //fprintf pour écrire dans le csv sortie
        verif=0;
        //on récup les coordonnées
        tmp = recupColonne(tab[i].coords,1);
        tmp1 = recupColonne(tab[i].coords,2);
        if(int_d==1){
          //on vérifie les options
          if(((int_min*100)>tab[i].date)||((int_max*100)<tab[i].date)){

            verif=1;
          }
        }if(int_a==1){
          if((int_min>atof(tmp)||(int_max<atof(tmp)))){
            verif=1;
          }
        }if(int_g==1){
          if((int_min>atof(tmp1))||(int_max<atof(tmp1))){
            verif=1;
          }
        }
        //on vérifie que deux stations ne sont pas pareil et les options
        if((verif==0) && (tab[i].station != stationActuel)){
          //fprintf pour écrire dans le csv sortie
          fprintf(sortie,"%d;%d;%f;%s\n", tab[i].station,tab[i].date,tab[i].humide,tab[i].coords);
          stationActuel = tab[i].station;
        }
        //on free tout
        free(tmp);
        free(tmp1);
        free(tab[i].coords);
      }
    }else if(int_argument==4){
      //TEMPERATURE
      if(int_m==1){
        //TEMPERATURE 1
        float min,max,moyen,compteur;
        compteur = 0;
        TemperaturePression* tab = malloc(sizeof *tab * lignes);
        //Rewind permet de replacer le curseur au début du csv
        //Comme on l'a parcouru dans nbLignes(), on doit l'appeler ici
        rewind(csv);
        //On récupère les données voulue pour -p
        tab = recupTemperature(csv,tab);
        min=tab[2].TemperaturePression;
        max=tab[2].TemperaturePression;
        moyen=tab[2].TemperaturePression;
        //Tri fusion
        printf("%s\n", "Tri des valeurs...");
        fusionTrieTemperaturePression1(tab,0,lignes-1);
        //Ecriture des valeurs triées
        printf("%s\n", "Ecriture des valeurs...");
        //On parcourt notre tableau
        for (int i = 2; i < lignes-1; i++) {
          //On s'assure qu'il n'écrive aucune valeurs nulles
          if (tab[i].TemperaturePression != 0) {
            if(tab[i-1].station==tab[i].station){
              if(min>tab[i].TemperaturePression){
                min = tab[i].TemperaturePression;
              }
              if(tab[i].TemperaturePression>max){
                max = tab[i].TemperaturePression;
              }
              moyen = moyen + tab[i].TemperaturePression;
              compteur = compteur +1;
            }else{
              //fprintf pour écrire dans le csv sortie
              fprintf(sortie,"%d;%d;%f;%f;%f;%s\n", tab[i-1].station,tab[i-1].date,min,max,(moyen/compteur),tab[i].coords);
              free(tab[i].coords);
              //on remet à 0 la moyenne et compteur
              compteur = 0;
              moyen = 0;
            }
          }
        }
      }else if(int_m==2){
        //TEMPERATURE 2
        float moyenne;
        float compteur;
        moyenne = 0;
        compteur = 0;
        TemperaturePression* tab = malloc(sizeof *tab * lignes);
        //Rewind permet de replacer le curseur au début du csv
        //Comme on l'a parcouru dans nbLignes(), on doit l'appeler ici
        rewind(csv);
        //On récupère les données voulue pour -p
        tab = recupTemperature(csv,tab);
        //Tri fusion
        printf("%s\n", "Tri des valeurs...");
        fusionTrieTemperaturePression2(tab,0,lignes-1);
        //Ecriture des valeurs triées
        printf("%s\n", "Ecriture des valeurs...");
        //On parcourt notre tableau
        for (int i = 1; i < lignes-1; i++) {
          //On s'assure qu'il n'écrive aucune valeurs nulles
          if (tab[i].date != 0) {
            if(tab[i-1].date==tab[i].date){
              moyenne = moyenne + tab[i].TemperaturePression;
              compteur = compteur + 1;
            }
            if(tab[i-1].date!=tab[i].date){
              fprintf(sortie,"%d;%f;%s\n",tab[i-1].date,(moyenne/compteur),tab[i].coords);
              free(tab[i].coords);
              //fprintf pour écrire dans le csv sortie
              moyenne = 0;
              compteur = 0;
              //on remet les compteurs à 0
            }
          }
        }
      }else if(int_m==3){
        //TEMPERATURE 3
        TemperaturePression* tab = malloc(sizeof *tab * lignes);
        //Rewind permet de replacer le curseur au début du csv
        //Comme on l'a parcouru dans nbLignes(), on doit l'appeler ici
        rewind(csv);
        //On récupère les données voulue pour -p
        tab = recupTemperature(csv,tab);
        //Tri fusion
        printf("%s\n", "Tri des valeurs...");
        fusionTrieTemperaturePression3(tab,0,lignes-1);
        //Ecriture des valeurs triées
        printf("%s\n", "Ecriture des valeurs...");
        //On parcourt notre tableau
        for (int i = 1; i < lignes-1; i++) {
          verif=0;
          //On s'assure qu'il n'écrive aucune valeurs nulles
          if (tab[i].date != 0) {
            tmp = recupColonne(tab[i].coords,1);
            tmp1 = recupColonne(tab[i].coords,2);
            //on vérifie les options
            if(int_d==1){
              if(((int_min*100)>tab[i].date)||((int_max*100)<tab[i].date)){
                verif=1;
              }
            }if(int_a==1){
              if((int_min>atof(tmp)||(int_max<atof(tmp)))){
                verif=1;
              }
            }if(int_g==1){
              if((int_min>atof(tmp1))||(int_max<atof(tmp1))){
                verif=1;
              }
            }
            if(verif==0){
              //fprintf pour écrire dans le csv sortie
              fprintf(sortie,"%d;%d;%f;%s\n",tab[i].date,tab[i].station,tab[i].TemperaturePression,tab[i].coords);
            }
            //on libère
            free(tmp);
            free(tmp1);
            free(tab[i].coords);
            }
          }
        }
    }else if(int_argument==5){
      //PRESSION
      if(int_m==1){
        //PRESSION 1
        float min,max,moyen,compteur;
        compteur = 0;
        TemperaturePression* tab = malloc(sizeof *tab * lignes);
        //Rewind permet de replacer le curseur au début du csv
        //Comme on l'a parcouru dans nbLignes(), on doit l'appeler ici
        rewind(csv);
        //On récupère les données voulue pour -p
        tab = recupPression(csv,tab);
        min=tab[2].TemperaturePression;
        max=tab[2].TemperaturePression;
        moyen=tab[2].TemperaturePression;
        //Tri fusion
        printf("%s\n", "Tri des valeurs...");
        fusionTrieTemperaturePression1(tab,0,lignes-1);
        //Ecriture des valeurs triées
        printf("%s\n", "Ecriture des valeurs...");
        //On parcourt notre tableau
        for (int i = 1; i < lignes-1; i++) {
          //On s'assure qu'il n'écrive aucune valeurs nulles
          if (tab[i].TemperaturePression != 0) {
            if(tab[i-1].station==tab[i].station){
              if(min>tab[i].TemperaturePression){
                min = tab[i].TemperaturePression;
              }
              if(tab[i].TemperaturePression>max){
                max = tab[i].TemperaturePression;
              }
              moyen = moyen + tab[i].TemperaturePression;
              compteur = compteur +1;
            }else{
              //fprintf pour écrire dans le csv sortie
              fprintf(sortie,"%d;%d;%f;%f;%f;%s\n", tab[i-1].station,tab[i-1].date,min,max,(moyen/compteur),tab[i-1].coords);
              free(tab[i].coords);
              //on remet à 0 la moyenne et compteur
              compteur = 0;
              moyen = 0;
            }
          }
        }
      }else if(int_m==2){
        //PRESSION 2
        float moyenne;
        float compteur;
        moyenne = 0;
        compteur = 0;
        TemperaturePression* tab = malloc(sizeof *tab * lignes);
        //Rewind permet de replacer le curseur au début du csv
        //Comme on l'a parcouru dans nbLignes(), on doit l'appeler ici
        rewind(csv);
        //On récupère les données voulue pour -p
        tab = recupPression(csv,tab);
        //Tri fusion
        printf("%s\n", "Tri des valeurs...");
        fusionTrieTemperaturePression2(tab,0,lignes-1);
        //Ecriture des valeurs triées
        printf("%s\n", "Ecriture des valeurs...");
        //On parcourt notre tableau
        for (int i = 1; i < lignes-1; i++) {
          //On s'assure qu'il n'écrive aucune valeurs nulles
          if (tab[i].date != 0) {
            if(tab[i-1].date==tab[i].date){
              moyenne = moyenne + tab[i].TemperaturePression;
              compteur = compteur + 1;
            }
            if(tab[i-1].date!=tab[i].date){
              fprintf(sortie,"%d;%f;%s\n",tab[i-1].date,(moyenne/compteur),tab[i].coords);
              free(tab[i].coords);
              //fprintf pour écrire dans le csv sortie
              moyenne = 0;
              compteur = 0;
              //on remet les compteurs à 0
            }
          }
        }
      }else if(int_m==3){
        //PRESSION 3
        TemperaturePression* tab = malloc(sizeof *tab * lignes);
        //Rewind permet de replacer le curseur au début du csv
        //Comme on l'a parcouru dans nbLignes(), on doit l'appeler ici
        rewind(csv);
        //On récupère les données voulue pour -p
        tab = recupPression(csv,tab);
        //Tri fusion
        printf("%s\n", "Tri des valeurs...");
        fusionTrieTemperaturePression3(tab,0,lignes-1);
        //Ecriture des valeurs triées
        printf("%s\n", "Ecriture des valeurs...");
        //On parcourt notre tableau
        for (int i = 1; i < lignes-1; i++) {
          verif=0;
          //On s'assure qu'il n'écrive aucune valeurs nulles
          if (tab[i].date != 0) {
            //récup coordonnées
            tmp = recupColonne(tab[i].coords,1);
            tmp1 = recupColonne(tab[i].coords,2);
            //on vérifie les options
            if(int_d==1){
              if(((int_min*100)>tab[i].date)||((int_max*100)<tab[i].date)){
                verif=1;
              }
            }if(int_a==1){
              if((int_min>atof(tmp)||(int_max<atof(tmp)))){
                verif=1;
              }
            }if(int_g==1){
              if((int_min>atof(tmp1))||(int_max<atof(tmp1))){
                verif=1;
              }
            }
            //on écrit seulement si les options sont vérifiées
            if(verif==0){
              //fprintf pour écrire dans le csv sortie
              fprintf(sortie,"%d;%d;%f;%s\n",tab[i].date,tab[i].station,tab[i].TemperaturePression,tab[i].coords);
            }
            //on libère
            free(tmp);
            free(tmp1);
            free(tab[i].coords);
          }
        }
      }
    }
  }
}

  if(int_help==1){
    int_retour=7;
  }

//les cas d'erreurs
  switch (int_retour) {
    case 0:
    printf("La compilation s'est bien éxécutée\n");
    break;

    case 1:
    printf("L'argument unique tel que /-t <1/2/3>/-p/-w/-h/-m/ a mal été saisi\n");
    break;

    case 2:
    printf("L'entrée -i a mal été saisie\n");
    break;

    case 3:
    printf("La sortie -o a mal été saisie\n");
    break;

    case 4:
    printf("Il y a une erreur de saisie des arguments\n");
    break;

    case 5:
    printf("Il y a une erreur de saisie du minimum et du maximum\n");
    break;

    case 6:
    printf("%s\n", "Pas réussi à ouvrir le fichier");
    break;

    case 7:
    printf("%s\n", "Besoin d'un coup de pouce? ;)");
    break;

    default:
    printf("Le code C n'a rien rendu d'espéré");
    break;
  }

  fin = time(NULL); //Prend le temps à la fin du programme.
  printf("terminé:%lds\n", fin-debut); // affiche la différence

  return retour;
}
