#include "fonctions.h"

// Auteur :  Lisa
// Date :  27/12
// Résumé :  Fonction qui permet de récupérer les arguments de l'utilisateur
// Entrée(s) :  argv,argc,int_exclusivité,int_t,int_entree,int_sortie,char_entree,char_sortie,int_min,int_max,int_d,int_a,int_g(pointeurs)
// Sortie(s) :  Aucune mais modifie les pointeurs
void recuperation_arguments(char** argv,int argc,int* int_exclusivite,int* int_m,int* int_entree,int* int_sortie,char** char_entree,char** char_sortie,int* int_min,int* int_max,int* int_g,int* int_a,int* int_d){
  for(int int_i=0;int_i<argc;int_i++){
    if((strcmp(argv[int_i],"-t")==0)){
      //pour vérifier que argv[int_i+1] existe
      if(argv[int_i+1]!=NULL){
        //atoi pour vérifier que la chaine de caractère est un nombre
        if((atoi(argv[int_i+1]))!=0){
          //on valide le -t
          *int_exclusivite=*int_exclusivite+1;
          //convertis la chaine de caractère en nombre
          *int_m=atoi(argv[int_i+1]);
        }
      }
      //on vérifie le -p
    }if(strcmp(argv[int_i],"-p")==0){
      //pour vérifier que argv[int_i+1] existe
      if(argv[int_i+1]!=NULL){
        //atoi pour vérifier que la chaine de caractère est un nombre
        if((atoi(argv[int_i+1]))!=0){
          //on valide le -p
          *int_exclusivite=*int_exclusivite+1;
          //convertis la chaine de caractère en nombre
          *int_m=atoi(argv[int_i+1]);
        }
      }
      //on vérifie le -w
    }if(strcmp(argv[int_i],"-w")==0){
      *int_exclusivite=*int_exclusivite+1;
      //on vérifie le -h
    }if(strcmp(argv[int_i],"-h")==0){
      *int_exclusivite=*int_exclusivite+1;
      //on vérifie le -m
    }if(strcmp(argv[int_i],"-m")==0){
      *int_exclusivite=*int_exclusivite+1;
      //on vérifie l'entrée
    }if(strcmp(argv[int_i],"-i")==0){
      *int_entree=*int_entree+1;
      *char_entree = argv[int_i+1];
      //on vérifie la sortie
    }if(strcmp(argv[int_i],"-o")==0){
      *int_sortie=*int_sortie+1;
      *char_sortie = argv[int_i+1];
      //on vérifie le -g
    }if(strcmp(argv[int_i],"-g")==0){
      *int_g=-1;
      //on vérifie que les deux arguments suivants existent
      if((argv[int_i+1]!=NULL)&&(argv[int_i+2]!=NULL)){
        //on vérifie que les deux arguments suivants sont des nombres
        if((estnombre(argv[int_i+1])==0)&&(estnombre(argv[int_i+2])==0)){
          //on récupère les valeurs min max
          *int_min=atoi(argv[int_i+1]);
          *int_max=atoi(argv[int_i+2]);
          //on vérifie que le minimum est plus petit que le maximum
          if(*int_min<*int_max){
            *int_g=1;
          }
        }
      }
      //on vérifie le -a
    }if(strcmp(argv[int_i],"-a")==0){
      *int_a=-1;
      //on vérifie que les deux arguments suivants existent
      if((argv[int_i+1]!=NULL)&&(argv[int_i+2]!=NULL)){
        //on vérifie que les deux arguments suivants sont des nombres
        if((estnombre(argv[int_i+1])==0)&&(estnombre(argv[int_i+2])==0)){
          //on récupère les valeurs min max
          *int_min=atoi(argv[int_i+1]);
          *int_max=atoi(argv[int_i+2]);
          //on vérifie que le minimum est plus petit que le maximum
          if(*int_min<*int_max){
            *int_a=1;
          }
        }
      }
      //on vérifie le -d
    }if(strcmp(argv[int_i],"-d")==0){
      *int_d=-1;
      //on vérifie que les deux arguments suivants existent
      if((argv[int_i+1]!=NULL)&&(argv[int_i+2]!=NULL)){
        //on vérifie que les deux arguments suivants sont des nombres
        if((estdate(argv[int_i+1])==0)&&(estdate(argv[int_i+2])==0)){
          //on récupère les valeurs min max
          *int_min=dateInt(argv[int_i+1]);
          *int_max=dateInt(argv[int_i+2]);
          //on vérifie que le minimum est plus petit que le maximum
          if(*int_min<*int_max){
            *int_d=1;
          }
        }
      }
    }
  }
}

// Auteur :  Kennan
// Date :  27/12
// Résumé :  Fonction qui permet d'afficher l'aide
// Entrée(s) :  argv,argc
// Sortie(s) :  print le --help
int help(char** argv,int argc){
  int int_help;
  int_help=0;
  //on met à part le --help pour qu'il apparaisse malgré les erreurs pour l'utilisateur en difficulté
  for(int int_i=0;int_i<argc;int_i++){
    //mise en forme du --help
    if(strcmp(argv[int_i],"--help")==0){
      printf("- Aide - \n");
      printf("./meteo --help : affiche l'aide\n");
      printf("./meteo -t <mode> : affiche les températures\n");
      printf("./meteo -p <mode> : affiche les pressions atmosphériques\n");
      printf("Pour les deux options, il faut entrer une valeur dans <mode>\n");
      printf("1 : en fonction des valeurs minimales, maximales et moyennes ordre croissant\n");
      printf("2 : en fonction de la date/heure ordre chronologique \n");
      printf("3 : en fonction de la date/heure ordre chronologique puis croissant par id de station\n\n");
      printf("./meteo -w : affiche des vecteurs en fonction de la direction et vitesse du vent\n");
      printf("./meteo -m : affiche l'humidité maximale pour chaque station\n");
      printf("./meteo -h : affiche la hauteur de chaque station en ordre décroissant\n");
      printf("./meteo -a <min> <max>: réduit les résultats en fonction de l'altitude min max\n");
      printf("./meteo -g <min> <max>: réduit les résultats en fonction de la longitude min max\n");
      printf("./meteo -d <min> <max>: réduit les résultats en fonction de la date min max\n");
      printf("./meteo -i nomfichier.csv: permet de mettre le .csv d'entrée\n");
      printf("./meteo -o nomfichier.csv: permet de mettre le .csv de sortie\n");
      int_help = 1;
    }
  }
  return int_help;
}

// Auteur :  Lisa
// Date :  27/12
// Résumé :  Fonction qui permet de vérifier les arguments de l'utilisateur
// Entrée(s) :  argv,argc,int_exclusivité,int_t,int_entree,int_sortie,char_entree,char_sortie,int_min,int_max,int_d,int_a,int_g(pointeurs)
// Sortie(s) :  0 si tout va bien, un nombre positif sinon
int validation_arguments(char** argv,int argc,int* int_exclusivite,int* int_m,int* int_entree,int* int_sortie,char** char_entree,char** char_sortie,int* int_min,int* int_max,int* int_g,int* int_a,int* int_d,int* int_argument){
  int int_retour;
  int_retour=0;
  int int_i;
  int_i=0;
  //on vérifie si il y a des fonctions optionnelles
  if((*int_g!=-1)&&(*int_d!=-1)&&(*int_a!=-1)){
    //on vérifie si l'utilisateur a correctement entré les arguments
    if((*int_exclusivite==1)&&(*int_m==0)&&(*int_sortie==1)&&(*int_entree==1)){
      //on reparcours les arguments pour pouvoir les récupérer, puisqu'ils sont valides
      for(int_i=0;int_i<argc;int_i++){
        //on vérifie -w
        if((strcmp(argv[int_i],"-w")==0)){
          //Vent?
          *int_argument = 1;
          //on vérifie -h
        }if((strcmp(argv[int_i],"-h")==0)){
          //Hauteur?
          *int_argument = 2;
          //on vérifie -m
        }if((strcmp(argv[int_i],"-m")==0)){
          //Humidité?
          *int_argument = 3;
        }
      }
      //on vérifie si les mode de -t et de -p sont valides
    }else if((*int_exclusivite==1)&&(0<*int_m)&&(*int_m<4)&&(*int_sortie==1)&&(*int_entree==1)){
      //on reparcours les arguments pour pouvoir les récupérer, puisqu'ils sont valides
      for(int_i=0;int_i<argc;int_i++){
        //on vérifie -t
        if((strcmp(argv[int_i],"-t")==0)){
          //Température?
          *int_argument = 4;
          //on vérifie -p
        }if((strcmp(argv[int_i],"-p")==0)){
          //Pression?
          *int_argument = 5;
        }
      }
    }else{
      if(*int_exclusivite!=1){
        //erreur si il n'y a pas un argument exclusif
        int_retour=1;
      }else if(*int_entree!=1){
        //erreur si il y a un problème avec l'entrée
        int_retour=2;
      }else if(*int_sortie!=1){
        //erreur si il y a un problème avec la sortie
        int_retour=3;
      }else{
        //erreur général
        int_retour=4;
      }
    }
  }else{
    //erreur du min et max
    int_retour=5;
  }
  return int_retour;
}


// Auteur :  Khadija
// Date :  27/12
// Modifié par Kennan
// Résumé :  Fonction qui permet de vérifier si une chaine de caractère est une chaine de nombre
// Entrée(s) :  chaine de caractères
// Sortie(s) :  0 si c'est une chaine de nombre, nombre positif sinon
int estnombre(char* chaine){
  int a;
  a=0;
  //on parcours la chaine de caractère
  for(int i=0;i<strlen(chaine);i++){
    //on vérifie si chaque caractère est un nombre
    if(isdigit(chaine[i])==0){
      a=a+1;
    }
  }
  return a;
}

// Auteur :  Lisa
// Date :  27/12
// Modifié par Khadija
// Résumé :  Fonction qui permet de vérifier si le format de la date est bon
// Entrée(s) :  chaine de caractères
// Sortie(s) :  0 si c'est le bon format, 1 sinon
int estformatdate(char* date){
  int a,i;
  i=0;
  a=0;
  int scan = 0;
  //on détermine la taille de date
  while (date[scan] != '\0') {
    scan++;
  }
  //si la taille est 10, on fait les calculs
  if (scan == 10) {
    //on vérifie le premier -
    if(date[4]!='-'){
      a=1;
    }
    //on vérifie le deuxième -
    if(date[7]!='-'){
      a=1;
    }
    //on vérifie que les non - soient des nombres
    while( (a==0) && (i != 10)){
      if((date[i] != '-')&&(!isdigit(date[i]))){
        a=1;
      }
      i++;
    }
  }else{
    a=1;
  }
  return a;
}

// Auteur :  Lisa
// Date :  27/12
// Modifié par Kennan
// Résumé :  Fonction qui permet de vérifier si la date existe
// Entrée(s) :  chaine de caractères
// Sortie(s) :  0 si c'est le bon format, 1 sinon
int estdate(char* date){
  int int_retour;
  int_retour=0;
  //on alloue deux variables temporaires
  char* temp2 = malloc(2*sizeof temp2);
  char* temp1 = malloc(2*sizeof temp1);

  //on vérifie le format de la date
  if(estformatdate(date)==0){
    //temp1 représente les mois
    temp1[0] = date[5];
    temp1[1] = date[6];
    //temp2 représente les jours
    temp2[0] = date[8];
    temp2[1] = date[9];
    //les mois ne peuvent être inférieurs à 0 ou supérieurs à 12
    if((atoi(temp1)<0)||(atoi(temp1)>12)){
      int_retour = 1;
    //les jours ne peuvent être inférieurs à 0 ou supérieurs à 31
    }else if((atoi(temp2)<0)||(atoi(temp2)>31)){
      int_retour = 1;
    }
  }else{
    int_retour = 1;
  }
  //on libère la mémoire
  free(temp1);
  free(temp2);
  return int_retour;
}


// Auteur :  Lisa
// Modifié par Khadija
// Date :  27/12
// Résumé :  Fonction qui permet de transformer une date chaine de caractère en int
// Entrée(s) :  chaine de caractères
// Sortie(s) :  int date
int dateInt(char* date){
  int temp,decal;
  //on crée une variable de décalage
  decal=0;
  //on crée une variable temporaire
  char* temp1 = malloc(sizeof *temp1 * MAXCHAR);
  //on parcours la date
  for(int i=0;i<12;i++){
    //si c'est un "-" on l'ignore
    if(date[i] != '-'){
      //on met tous les nombres dans temp
      temp1[i-decal]=date[i];
    }else{
      //on décale de 1 lorsque il y a "-"
      decal=decal+1;
    }
  }
  //on transforme la chaine de caractère en int
  temp=atoi(temp1);
  free(temp1);
  return temp;
}

// Auteur :  Lisa
// Modifié par Khadija
// Date :  27/12
// Résumé :  Fonction qui permet de transformer une date chaine de caractère en int
// Entrée(s) :  chaine de caractères
// Sortie(s) :  int date
int dateIntGNU(char* date){
  int temp,decal;
  //on crée une variable de décalage
  decal=0;
  //on crée une variable temporaire
  char* temp1 = malloc(sizeof *temp1 * MAXCHAR);
  //on parcours la date
  for(int i=0;i<13;i++){
    //si c'est un "-" on l'ignore
    if((date[i] == '-')||(date[i] == 'T')){
      decal=decal+1;
    }else{
      //on met tous les nombres dans temp
      temp1[i-decal]=date[i];
    }
  }
  //on transforme la chaine de caractère en int
  temp=atoi(temp1);
  free(temp1);
  return temp;
}

// Auteur :  Khadija
// Date :  25/12
// Résumé :  Fonction qui permet d'avoir le nombre de ligne du fichier csv
// Entrée(s) :  fichier
// Sortie(s) :  nombre ligne
int nbLignes(FILE* file){
  //On alloue la mémoire pour la ligne lue
  char* ligne = malloc(sizeof ligne*MAXCHAR);
  //On initialise le compteur à 0
  int int_ligne = 0;
  //Tant qu'une ligne n'est pas nulle, on parcourt les lignes
  while (fgets(ligne,MAXCHAR,file) != NULL) {
    //On incrémente le compteur
    int_ligne++;
  }
  //On retourne le compteur
  free(ligne);
  return int_ligne;
}

// Auteur :  Lisa
// Modifié par Khadija
// Date :  27/12
//Renvoie un tableau contenant les stations et au choix,
Hauteur* recupHauteur(FILE* file, Hauteur* tab){
  //Déclaration des variables
  char* ligne;

  //Initialisation des variables
  ligne = malloc(sizeof *ligne*MAXCHAR);
  int i = 0; //On oublie bas d'initialiser i à 0
  printf("%s\n", "Hauteur...");
  //On parcourt chaque ligne tant qu'elle n'est pas nulle
  while(fgets(ligne,MAXCHAR,file) != NULL) {

    //NB : Les décomptes des colonnes commence à 1
    //ID station colonne 1
    char* tmp = recupColonne(ligne, 1);
    tab[i].station = atoi(tmp);
    free(tmp);
    //Hauteur
    char* tmp2 = recupColonne(ligne, 14);
    tab[i].hauteur = atof(tmp2);
    free(tmp2);

    //date
    char* tmp4 = recupColonne(ligne, 2);
    tab[i].date = dateIntGNU(tmp4);
    free(tmp4);

    char* tmp3 = recupColonne(ligne, 10);
    int j = 0;
    while (tmp3[j] != '\0') {
      if (tmp3[j] == ',') {
        tmp3[j] = ';';
      }
      if (tmp3[j+1] == '+') {
        tmp3[j+1] = '0';
        tmp3[j+2] = '0';
        tmp3[j+3] = '0';
      }
      if (tmp3[j+1] == ':') {
        tmp3[j+1] = '0';
        tmp3[j+2] = '0';
        tmp3[j+3] = '0';
      }
      j++;
    }
    tab[i].coords = tmp3;
    i++;
  }
  free(ligne);
  return tab;
}

// Auteur :  Lisa
// Date :  27/12
//Renvoie un tableau contenant les stations et au choix,
Humide* recupHumide(FILE* file, Humide* tab){
  //Déclaration des variables
  char* ligne;

  //Initialisation des variables
  ligne = malloc(sizeof *ligne*MAXCHAR);
  int i = 0; //On oublie bas d'initialiser i à 0
  printf("%s\n", "Humidité...");
  //On parcourt chaque ligne tant qu'elle n'est pas nulle
  while(fgets(ligne,MAXCHAR,file) != NULL) {

    //NB : Les décomptes des colonnes commence à 1
    //ID station colonne 1
    char* tmp = recupColonne(ligne, 1);
    tab[i].station = atoi(tmp);
    free(tmp);
    //date
    char* tmp2 = recupColonne(ligne, 2);
    tab[i].date = dateIntGNU(tmp2);
    free(tmp2);

    //humidité
    char* tmp4 = recupColonne(ligne, 6);
    tab[i].humide = atoi(tmp4);
    free(tmp4);

    char* tmp3 = recupColonne(ligne, 10);
    int j = 0;
    while (tmp3[j] != '\0') {
      if (tmp3[j] == ',') {
        tmp3[j] = ';';
      }
      if (tmp3[j+1] == '+') {
        tmp3[j+1] = '0';
        tmp3[j+2] = '0';
        tmp3[j+3] = '0';
      }
      if (tmp3[j+1] == ':') {
        tmp3[j+1] = '0';
        tmp3[j+2] = '0';
        tmp3[j+3] = '0';
      }
      j++;
    }
    tab[i].coords = tmp3;
    i++;
  }
  free(ligne);
  return tab;
}

// Auteur :  Lisa
// Date :  27/12
//Renvoie un tableau contenant les stations et au choix,
Wind* recupWind(FILE* file, Wind* tab){
  //Déclaration des variables
  char* ligne;

  //Initialisation des variables
  ligne = malloc(sizeof *ligne*MAXCHAR);
  int i = 0; //On oublie bas d'initialiser i à 0
  printf("%s\n", "Vent...");
  //On parcourt chaque ligne tant qu'elle n'est pas nulle
  while(fgets(ligne,MAXCHAR,file) != NULL) {

    //NB : Les décomptes des colonnes commence à 1
    //ID station colonne 1
    char* tmp = recupColonne(ligne, 1);
    tab[i].station = atoi(tmp);
    free(tmp);
    //direction vent
    char* tmp2 = recupColonne(ligne, 4);
    tab[i].orientation = atoi(tmp2);
    free(tmp2);

    char* tmp3 = recupColonne(ligne, 10);
    int j = 0;

    while (tmp3[j] != '\0') {
      if (tmp3[j] == ',') {
        tmp3[j] = ';';
      }
      if (tmp3[j+1] == '+') {
        tmp3[j+1] = '0';
        tmp3[j+2] = '0';
        tmp3[j+3] = '0';
      }
      if (tmp3[j+1] == ':') {
        tmp3[j+1] = '0';
        tmp3[j+2] = '0';
        tmp3[j+3] = '0';
      }

      j++;
    }
    tab[i].coords =tmp3;

    //direction vent
    char* tmp4 = recupColonne(ligne, 5);
    tab[i].vitesse = atof(tmp4);
    free(tmp4);

    //date
    char* tmp5 = recupColonne(ligne, 2);
    tab[i].date = dateIntGNU(tmp5);
    free(tmp5);
    i++;
  }
  free(ligne);
  return tab;
}

// Auteur :  Lisa
// Date :  27/12
//Renvoie un tableau contenant les stations et au choix,
TemperaturePression* recupPression(FILE* file, TemperaturePression* tab){
  //Déclaration des variables
  char* ligne;

  //Initialisation des variables
  ligne = malloc(sizeof *ligne*MAXCHAR);
  int i = 0; //On oublie bas d'initialiser i à 0
  printf("%s\n", "Pression...");

  //On parcourt chaque ligne tant qu'elle n'est pas nulle
  while(fgets(ligne,MAXCHAR,file) != NULL) {
    //On récupère l'information à la colonne qui correspond

    //NB : Les décomptes des colonnes commence à 1
    //ID station colonne 1
    char* tmp = recupColonne(ligne, 1);
    tab[i].station = atoi(tmp);
    free(tmp);
    //Date
    char* tmp2 = recupColonne(ligne, 2);
    tab[i].date = dateIntGNU(tmp2);
    free(tmp2);
    //pression Station colonne 11
    char* tmp3 = recupColonne(ligne, 7);
    tab[i].TemperaturePression = atof(tmp3);
    free(tmp3);

    char* tmp4 = recupColonne(ligne, 10);
    int j = 0;
    while (tmp3[j] != '\0') {
      if (tmp3[j] == ',') {
        tmp3[j] = ';';
      }
      if (tmp3[j+1] == '+') {
        tmp3[j+1] = '0';
        tmp3[j+2] = '0';
        tmp3[j+3] = '0';
      }
      if (tmp3[j+1] == ':') {
        tmp3[j+1] = '0';
        tmp3[j+2] = '0';
        tmp3[j+3] = '0';
      }
      j++;
    }
    tab[i].coords = tmp4;

    i++;
  }
  free(ligne);
  return tab;
}

// Auteur :  Lisa
// Date :  27/12
//Renvoie un tableau contenant les stations et au choix,
TemperaturePression* recupTemperature(FILE* file, TemperaturePression* tab){
  //Déclaration des variables
  char* ligne;

  //Initialisation des variables
  ligne = malloc(sizeof *ligne*MAXCHAR);
  int i = 0; //On oublie bas d'initialiser i à 0
  printf("%s\n", "Temperature ...");

  //On parcourt chaque ligne tant qu'elle n'est pas nulle
  while(fgets(ligne,MAXCHAR,file) != NULL) {
    //On alloue la mémoire à l'info que l'on veut récuperer
    //On récupère l'information à la colonne qui correspond

    //NB : Les décomptes des colonnes commence à 1
    //ID station colonne 1
    char* tmp = recupColonne(ligne, 1);
    tab[i].station = atoi(tmp);
    free(tmp);

    //date
    char* tmp4 = recupColonne(ligne, 2);
    tab[i].date = dateIntGNU(tmp4);
    free(tmp4);

    //pression Station colonne 11
    char* tmp2 = recupColonne(ligne, 11);
    tab[i].TemperaturePression = atof(tmp2);
    free(tmp2);

    char* tmp3 = recupColonne(ligne, 10);
    int j = 0;
    while (tmp3[j] != '\0') {
      if (tmp3[j] == ',') {
        tmp3[j] = ';';
      }
      if (tmp3[j+1] == '+') {
        tmp3[j+1] = '0';
        tmp3[j+2] = '0';
        tmp3[j+3] = '0';
      }
      if (tmp3[j+1] == ':') {
        tmp3[j+1] = '0';
        tmp3[j+2] = '0';
        tmp3[j+3] = '0';
      }
      j++;
    }
    tab[i].coords = tmp3;
    i++;
  }
  free(ligne);
  return tab;
}

// Auteur :  Lisa
// Modifié par Khadija
// Date :  27/12
//Elle permet de récuperer la chaine à la colonne prise en paramètre
char* recupColonne(char* ligne, int nbCol){
  //Déclaration des variables
  //Initialisation des variables
  int curseur = 0;
  int cmpt = 0;
  int i = 0;
  char* resChaine;

  //On alloue la mémoire de la chaine renvoyée
  resChaine = malloc(sizeof *resChaine*MAXCHAR);

  //Tant que notre compteur != du nb de la colonne entrée
  while ((cmpt != nbCol) && (ligne[curseur] != '\0')) {
    //On vérifie si on est dans la colonne choisie (en gros avant le ';' dans le csv)
    //On écrit pas le ;
    if ((cmpt == nbCol-1) && (ligne[curseur] != ';')) {
      //On rempli notre chaine retour
      resChaine[i] = ligne[curseur];
      i++;
    }
    //Et on compte si on passe sur un ;
    if (ligne[curseur] == ';') {
      cmpt++;
    }
    //On incrémente le curseur pour parcourir la ligne
    curseur++;
  }
  //On retourne la chaine
  return resChaine;
}

// Auteur :  Lisa
// Date :  27/12
// Le tri fusion par id station
void fusionTrieHauteur(Hauteur* tab, int debut, int fin) {
    if (debut < fin){
        int milieu = debut + (fin - debut) / 2;

        fusionTrieHauteur(tab, debut, milieu);
        fusionTrieHauteur(tab, milieu + 1, fin);

        fusionHauteur(tab, debut, milieu, fin);
    }
}

// Auteur :  Lisa
// Date :  27/12
void fusionTrieHauteurStation(Hauteur* tab, int debut, int fin) {
    if (debut < fin){
        int milieu = debut + (fin - debut) / 2;

        fusionTrieHauteurStation(tab, debut, milieu);
        fusionTrieHauteurStation(tab, milieu + 1, fin);

        fusionHauteurStation(tab, debut, milieu, fin);
    }
}

// Auteur :  Lisa
// Date :  27/12
void fusionHauteur(Hauteur* tab, int debut, int milieu, int fin) {
    int i, j, k;
    int n1 = milieu - debut + 1;
    int n2 = fin - milieu;

    Hauteur* G = malloc(sizeof *G * n1);
    Hauteur* D = malloc(sizeof *D * n2);

    for (i = 0; i < n1; i++){
      G[i] = tab[debut + i];
    }
    for (j = 0; j < n2; j++){
      D[j] = tab[milieu + 1 + j];
    }

    i = 0;
    j = 0;
    k = debut;

    while (i < n1 && j < n2) {
      if (G[i].hauteur >= D[j].hauteur){
          tab[k++] = G[i++];
      }else{
          tab[k++] = D[j++];
      }
    }

    while (i < n1){
        tab[k++] = G[i++];
    }while (j < n2){
        tab[k++] = D[j++];
    }

    free(G);
    free(D);
}

// Auteur :  Lisa
// Date :  27/12
void fusionHauteurStation(Hauteur* tab, int debut, int milieu, int fin) {
    int i, j, k;
    int n1 = milieu - debut + 1;
    int n2 = fin - milieu;

    Hauteur* G = malloc(sizeof *G * n1);
    Hauteur* D = malloc(sizeof *D * n2);

    for (i = 0; i < n1; i++){
      G[i] = tab[debut + i];
    }
    for (j = 0; j < n2; j++){
      D[j] = tab[milieu + 1 + j];
    }

    i = 0;
    j = 0;
    k = debut;

    while (i < n1 && j < n2) {
      if (G[i].station <= D[j].station){
          tab[k++] = G[i++];
      }else{
          tab[k++] = D[j++];
      }
    }

    while (i < n1){
        tab[k++] = G[i++];
    }while (j < n2){
        tab[k++] = D[j++];
    }

    free(G);
    free(D);
}

// Auteur :  Kennan
// Modifié par Khadija
// Le tri fusion par id station
void fusionTrieWind(Wind* tab, int debut, int fin) {
    if (debut < fin){
        int milieu = debut + (fin - debut) / 2;

        fusionTrieWind(tab, debut, milieu);
        fusionTrieWind(tab, milieu + 1, fin);

        fusionWind(tab, debut, milieu, fin);
    }
}

// Auteur :  Kennan
// Modifié par Khadija
// Date :  27/12
void fusionWind(Wind* tab, int debut, int milieu, int fin) {
    int i, j, k;
    int n1 = milieu - debut + 1;
    int n2 = fin - milieu;

    Wind* G = malloc(sizeof *G * n1);
    Wind* D = malloc(sizeof *D * n2);

    for (i = 0; i < n1; i++){
      G[i] = tab[debut + i];
    }
    for (j = 0; j < n2; j++){
      D[j] = tab[milieu + 1 + j];
    }

    i = 0;
    j = 0;
    k = debut;

    while (i < n1 && j < n2) {
      if (G[i].station <= D[j].station){
          tab[k++] = G[i++];
      }else{
          tab[k++] = D[j++];
      }
    }

    while (i < n1){
        tab[k++] = G[i++];
    }while (j < n2){
        tab[k++] = D[j++];
    }

    free(G);
    free(D);
}

// Auteur :  Khadija
// Modifié par Kennan
// Le tri fusion par id station
void fusionTrieHumide(Humide* tab, int debut, int fin) {
  if (debut < fin){
    int milieu = debut + (fin - debut) / 2;

    fusionTrieHumide(tab, debut, milieu);
    fusionTrieHumide(tab, milieu + 1, fin);

    fusionHumide(tab, debut, milieu, fin);
  }
}

// Auteur :  Khadija
// Modifié par Kennan
// Date :  27/12
void fusionHumide(Humide* tab, int debut, int milieu, int fin) {
    int i, j, k;
    int n1 = milieu - debut + 1;
    int n2 = fin - milieu;

    Humide* G = malloc(sizeof *G * n1);
    Humide* D = malloc(sizeof *D * n2);

    for (i = 0; i < n1; i++){
      G[i] = tab[debut + i];
    }
    for (j = 0; j < n2; j++){
      D[j] = tab[milieu + 1 + j];
    }

    i = 0;
    j = 0;
    k = debut;

    while (i < n1 && j < n2) {
      if (G[i].humide >= D[j].humide){
          tab[k++] = G[i++];
      }else{
          tab[k++] = D[j++];
      }
    }

    while (i < n1){
        tab[k++] = G[i++];
    }while (j < n2){
        tab[k++] = D[j++];
    }

    free(G);
    free(D);
}

// Auteur :  Khadija
// Date :  27/12
void fusionTrieHumideStation(Humide* tab, int debut, int fin) {
  if (debut < fin){
    int milieu = debut + (fin - debut) / 2;

    fusionTrieHumideStation(tab, debut, milieu);
    fusionTrieHumideStation(tab, milieu + 1, fin);

    fusionHumideStation(tab, debut, milieu, fin);
  }
}

// Auteur :  Khadija
// Modifié par Kennan
// Date :  27/12
void fusionHumideStation(Humide* tab, int debut, int milieu, int fin) {
    int i, j, k;
    int n1 = milieu - debut + 1;
    int n2 = fin - milieu;

    Humide* G = malloc(sizeof *G * n1);
    Humide* D = malloc(sizeof *D * n2);

    for (i = 0; i < n1; i++){
      G[i] = tab[debut + i];
    }
    for (j = 0; j < n2; j++){
      D[j] = tab[milieu + 1 + j];
    }

    i = 0;
    j = 0;
    k = debut;

    while (i < n1 && j < n2) {
      if (G[i].station >= D[j].station){
          tab[k++] = G[i++];
      }else{
          tab[k++] = D[j++];
      }
    }

    while (i < n1){
        tab[k++] = G[i++];
    }while (j < n2){
        tab[k++] = D[j++];
    }

    free(G);
    free(D);
}

// Auteur :  Lisa
// Modifié par Kennan
// Date :  27/12
// Le tri fusion par id station
void fusionTrieTemperaturePression1(TemperaturePression* tab, int debut, int fin) {
    if (debut < fin) {
        int milieu = debut + (fin - debut) / 2;

        fusionTrieTemperaturePression1(tab, debut, milieu);
        fusionTrieTemperaturePression1(tab, milieu + 1, fin);

        fusionTemperaturePression1(tab, debut, milieu, fin);
    }
}

// Auteur :  Lisa
// Date :  27/12
void fusionTemperaturePression1(TemperaturePression* tab, int debut, int milieu, int fin) {
    int i, j, k;
    int n1 = milieu - debut + 1;
    int n2 = fin - milieu;

    TemperaturePression* G = malloc(sizeof *G * n1);
    TemperaturePression* D = malloc(sizeof *D * n2);

    for (i = 0; i < n1; i++){
      G[i] = tab[debut + i];
    }
    for (j = 0; j < n2; j++){
      D[j] = tab[milieu + 1 + j];
    }

    i = 0;
    j = 0;
    k = debut;

    while (i < n1 && j < n2) {
      if (G[i].station <= D[j].station){
          tab[k++] = G[i++];
      }else{
          tab[k++] = D[j++];
      }
    }

    while (i < n1){
        tab[k++] = G[i++];
    }while (j < n2){
        tab[k++] = D[j++];
    }

    free(G);
    free(D);
}

// Auteur :  Khadija
// Modifié par Kennan
// Le tri fusion par date
void fusionTrieTemperaturePression2(TemperaturePression* tab, int debut, int fin) {
    if (debut < fin) {
        int milieu = debut + (fin - debut) / 2;

        fusionTrieTemperaturePression2(tab, debut, milieu);
        fusionTrieTemperaturePression2(tab, milieu + 1, fin);

        fusionTemperaturePression2(tab, debut, milieu, fin);
    }
}

// Auteur :  Khadija
// Modifié par Kennan
void fusionTemperaturePression2(TemperaturePression* tab, int debut, int milieu, int fin) {
    int i, j, k;
    int n1 = milieu - debut + 1;
    int n2 = fin - milieu;

    TemperaturePression* G = malloc(sizeof *G * n1);
    TemperaturePression* D = malloc(sizeof *D * n2);

    for (i = 0; i < n1; i++){
      G[i] = tab[debut + i];
    }
    for (j = 0; j < n2; j++){
      D[j] = tab[milieu + 1 + j];
    }

    i = 0;
    j = 0;
    k = debut;

    while (i < n1 && j < n2) {
      if (G[i].date <= D[j].date){
          tab[k++] = G[i++];
      }else{
          tab[k++] = D[j++];
      }
    }

    while (i < n1){
        tab[k++] = G[i++];
    }while (j < n2){
        tab[k++] = D[j++];
    }

    free(G);
    free(D);
}

// Auteur :  Khadija
// Le tri fusion par date
void fusionTrieTemperaturePression3(TemperaturePression* tab, int debut, int fin) {
    if (debut < fin) {
        int milieu = debut + (fin - debut) / 2;

        fusionTrieTemperaturePression3(tab, debut, milieu);
        fusionTrieTemperaturePression3(tab, milieu + 1, fin);

        fusionTemperaturePression3(tab, debut, milieu, fin);
    }
}

// Auteur :  Khadija
// Modifié par Kennan
void fusionTemperaturePression3(TemperaturePression* tab, int debut, int milieu, int fin) {
    int i, j, k;
    int n1 = milieu - debut + 1;
    int n2 = fin - milieu;

    TemperaturePression* G = malloc(sizeof *G * n1);
    TemperaturePression* D = malloc(sizeof *D * n2);

    for (i = 0; i < n1; i++){
      G[i] = tab[debut + i];
    }
    for (j = 0; j < n2; j++){
      D[j] = tab[milieu + 1 + j];
    }

    i = 0;
    j = 0;
    k = debut;

    while (i < n1 && j < n2) {
      if(G[i].date != D[j].date){
        if (G[i].date <= D[j].date){
          tab[k++] = G[i++];
        }else{
          tab[k++] = D[j++];
        }
      }else{
        if (G[i].station <= D[j].station){
          tab[k++] = G[i++];
        }else{
          tab[k++] = D[j++];
        }
      }
    }

    while (i < n1){
        tab[k++] = G[i++];
    }while (j < n2){
        tab[k++] = D[j++];
    }

    free(G);
    free(D);
}
