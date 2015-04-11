/* Fichier main.h
 * Inclut les structures de données utilisées dans le projet
 * Dernière modification 30-03-2015
 * */
#ifndef MAIN
#define MAIN 
  
#include <stdlib.h>
#include <stdio.h>

//Macros
#define RAM_MAX 3000000 //En KO
#define TEMPS_MAX 3600 //temps maximum : En secondes

//Structure d'un élément d'une liste chainée d'entiers
typedef struct Entier{
	short id;
	struct Entier *suivant;
}Entier;

//Structure de Littéraux 
typedef struct Litteral{
	Entier* tete;
}Litteral;

//Structure d'OPEN
typedef struct Open{
	char *e;
	Entier *chemin;
	struct Open *suivant;
}Open;

//Déclarationde la taille des tables e de la structure Open
int taille;
int nbClausesSatMax;

#endif


