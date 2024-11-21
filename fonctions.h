#ifndef __fonctions_H_
#define __fonctions_H_

//Inclusions des librairies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <time.h>
#define MAXCHAR 1000

//structure hauteur
typedef struct Hauteur{
  int station;
  int date;
  char* coords;
  float hauteur;
}Hauteur;

//structure température et pression
typedef struct TemperaturePression{
  int station;
  int date;
  float TemperaturePression;
  char* coords;
}TemperaturePression;

//structure wind
typedef struct Wind{
  int station;
  int date;
  int orientation;
  float vitesse;
  char* coords;
}Wind;

//structure humide
typedef struct Humide{
  int station;
  int date;
  float humide;
  char* coords;
}Humide;


int nbLignes(FILE* file);

Hauteur* recupHauteur(FILE* file, Hauteur* tab);

Wind* recupWind(FILE* file, Wind* tab);

TemperaturePression* recupPression(FILE* file, TemperaturePression* tab);

TemperaturePression* recupTemperature(FILE* file, TemperaturePression* tab);

char* recupColonne(char* chaine, int nbCol);

Humide* recupHumide(FILE* file, Humide* tab);

void fusionTrieHauteur(Hauteur* tab, int debut, int fin);
void fusionHauteur(Hauteur* tab, int debut, int milieu, int fin);
void fusionHauteurStation(Hauteur* tab, int debut, int milieu, int fin);
void fusionTrieHauteurStation(Hauteur* tab, int debut, int fin);


void fusionTrieTemperaturePression1(TemperaturePression* tab, int debut, int fin);
void fusionTemperaturePression1(TemperaturePression* tab, int debut, int milieu, int fin);
void fusionTrieTemperaturePression2(TemperaturePression* tab, int debut, int fin);
void fusionTemperaturePression2(TemperaturePression* tab, int debut, int milieu, int fin);
void fusionTemperaturePression3(TemperaturePression* tab, int debut, int milieu, int fin);
void fusionTrieTemperaturePression3(TemperaturePression* tab, int debut, int fin);

void fusionTrieWind(Wind* tab, int debut, int fin);
void fusionWind(Wind* tab, int debut, int milieu, int fin);

void fusionTrieHumide(Humide* tab, int debut, int fin);
void fusionHumide(Humide* tab, int debut, int milieu, int fin);
void fusionTrieHumideStation(Humide* tab, int debut, int fin);
void fusionHumideStation(Humide* tab, int debut, int milieu, int fin);

int estnombre(char* chaine);
int estformatdate(char* date);
int estdate(char* date);
int dateInt(char* date);
void recuperation_arguments(char** argv,int argc,int* int_exclusivite,int* int_m,int* int_entree,int* int_sortie,char** entree,char** sortie,int* int_min,int* int_max,int* int_g,int* int_a,int* int_d);
int validation_arguments(char** argv,int argc,int* int_exclusivite,int* int_m,int* int_entree,int* int_sortie,char** entree,char** sortie,int* int_min,int* int_max,int* int_g,int* int_a,int* int_d,int* int_argument);
int help(char** argv,int argc);
#endif
