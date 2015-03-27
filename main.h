/* Fichier main.h
 * Inclut les structures de données utilisées dans le projet
 * Dernière modification 27-03-2015
 * */
#ifndef MAIN
#define MAIN 
  
#include <stdlib.h>
#include <stdio.h>

//Structure d'état
typedef struct Etat{
	char e; //état de la clause
	struct Etat *suivant; //pointeur sur état suivant
}Etat;

//Structure d'une élément d'une liste chainée d'entiers
typedef struct Entier{
	int id;
	struct Entier *suivant;
}Entier;

//Structure de Littéraux 
typedef struct Litteral{
	Entier* tete;
}Litteral;

#endif


