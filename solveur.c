/* Fichier solveur.c contient les algorithmes de solveurs SAT 
 * Dans l'esapce des états
 * dérnière modification 28/03/2015	
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
	
	//Initialisation des données
	tabLitt=init("test.cnf",&nbClauses,&nbLitt,&etatInitial);
	
	
}

//Fonction de l'algorithem solveur SAT en profondeur
void profondeur()
{
	
}

//Fonction de l'algorithme sloveur SAT A*
void aEtoile(int h)
{
	
}
