/* Fichier de gestion des états 
 * dérnière modification 28/03/2015
 * */
 
#include "main.h"
#include "ges_fichiers.h"

//Fonction d'initialisations des données 
Litteral* init(char *benchmark,int *nbClauses,int *nbLitt)
{
	//Déclarationd de variables 
	Litteral *tab=NULL;
	
	//Lecteur du fichier de benchmark
	tab=lectureDeFichier(benchmark,nbClauses,nbLitt);
	
	return tab;
}
