/* Fichier de gestion des états 
 * dérnière modification 28/03/2015
 * */
 
#include "main.h"
#include "ges_fichiers.h"

//Fonction d'affichage d'état
void afficherEtat(Etat *tab,int nbClauses)
{
	//Déclaration de variables
	int i=0;

	//Parcours de l'état
	for(i=0;i<nbClauses;i++)
	{
		printf("la clause %d à l'état: %c\n",i+1,tab[i].e);
	}
}

//Fonction d'initialisations des données 
Litteral* init(char *benchmark,int *nbClauses,int *nbLitt,Etat **tabInit)
{
	//Déclarationd de variables 
	Litteral *tab=NULL;
	int i=0;
	
	//Lecteur du fichier de benchmark
	tab=lectureDeFichier(benchmark,nbClauses,nbLitt);
	
	//Allocation de l'état initial
	*tabInit=(Etat*)malloc(*nbClauses*sizeof(Etat));
	if(tabInit==NULL)
	{
		fprintf(stderr,"erreur lors de l'aalocation de la table d'états\n");
		exit(EXIT_FAILURE);
	}

	for(i=0;i<(*nbClauses);i++)
	{
		(*tabInit)[i].e='0';
	}	

	return tab;
}
