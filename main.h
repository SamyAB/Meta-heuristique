/* Fichier main.h
 * Inclut les structures de données utilisées dans le projet
 * Dernière modification 27-03-2015
 * */
#ifndef MAIN
#define MAIN 
  
#include <stdlib.h>
#include <stdio.h>

//Structure d'état
typedef struct etat{
	char e; //état de la clause
	struct etat *suivant; //pointeur sur état suivant
}etat;

#endif


