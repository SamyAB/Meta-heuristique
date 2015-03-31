/* Fichier main.h
 * Inclut les structures de données utilisées dans le projet
 * Dernière modification 30-03-2015
 * */
#ifndef MAIN
#define MAIN 
  
#include <stdlib.h>
#include <stdio.h>

//Structure d'un élément d'une liste chainée d'entiers
typedef struct Entier{
	int id;
	struct Entier *suivant;
}Entier;

//Structure d'un élément d'une liste chainée de caractères
/*typeDef struct Char{
	char c;
	struct Char suivant;
}Char;*/

//Structure de Littéraux 
typedef struct Litteral{
	Entier* tete;
}Litteral;

//Structure d'OPEN
typedef struct Open{
	int nbClauses;
	char *e;
	Entier *chemin;
	struct Open *suivant;
}Open;

#endif


