/* Fichier solveur.c contient les algorithmes de solveurs SAT 
 * Dans l'esapce des états
 * dérnière modification 30/03/2015	
 * */
 
#include "main.h"
#include "ges_etats.h"

//Fonction de l'algorithme solveur SAT en largeur
void largeur()
{
	//Déclaration de variables
	Litteral *tabLitt=NULL;
	int nbClauses=0,nbLitt=0;
	Etat *etatInitial=NULL;
	Open *tete=NULL;
	
	//Initialisation des données
	tabLitt=init("test.cnf",&nbClauses,&nbLitt,&etatInitial);
	
	//Alocation e la tête de la liste open
	tete=(Open*)malloc(sizeof(Open));
	if(tete==NULL)
	{
		fprintf(stderr,"erreur lors de l'allocation de la tête de liste open\n");
		exit(EXIT_FAILURE);
	}
	
	//Ajout de la tete a la liste open
	AjouterAOpen(&tete,etatInitial);
	
	//Boucle principale du solveur
	while(tete!=NULL)
	{
	}
	
}

//Fonction de l'algorithem solveur SAT en profondeur
void profondeur()
{
	
}

//Fonction de l'algorithme sloveur SAT A*
void aEtoile(int h)
{
	
}
