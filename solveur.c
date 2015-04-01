/* Fichier solveur.c contient les algorithmes de solveurs SAT 
 * Dans l'esapce des états
 * dérnière modification 01/04/2015	
 * */
 
#include "main.h"
#include "ges_etats.h"
#include <time.h>

//Fonction de l'algorithme solveur SAT en largeur
void largeur()
{
	//Déclaration de variables
	Litteral *tabLitt=NULL;
	int nbClauses=0,nbLitt=0,niveau=0;
	Open *etatInitial=NULL,*etatActuel=NULL,*queue=NULL;
	Open *tete=NULL;
	char typeE=' ';
	clock_t debut=clock();
	
	//Initialisation des données
	tabLitt=init("test.cnf",&nbClauses,&nbLitt,&etatInitial);
	
	//Ajout de la tete a la liste open
	ajouterAOpen(&tete,&queue,etatInitial);
	
	//Boucle principale du solveur
	while(tete!=NULL)
	{
		//Récupérer l'état a explorer
		etatActuel=depiler(&tete);
		
		//Récupération du type de l'état acutel
		typeE=typeEtat(etatActuel);
		
		//Test si l'état actuel est un état final (SAT)
		if(typeE=='S')
		{
			typeE=' ';
			printf("la formule est SAT\n");
			printf("Le temps passé est %lf",((double)(clock()-debut)/CLOCKS_PER_SEC));
			afficherChemin(etatActuel->chemin);
			break;
		}
		
		//Test si l'état est faux (UNSAT)
		if(typeE=='U')
		{
			typeE=' ';
			continue;
		}
		
		//Génération des états fils et leurs ajouts a la liste OPEN
		ajouterAOpen(&tete,&queue,genererEtat(etatActuel,1,tabLitt,nbLitt));
		ajouterAOpen(&tete,&queue,genererEtat(etatActuel,-1,tabLitt,nbLitt));
		
		//Libération de l'espace mémoir occupé par l'état actuel
		liberer(&etatActuel);

	}
	
	printf("La formule est UNSAT\n");
	
}

//Fonction de l'algorithem solveur SAT en profondeur
void profondeur()
{
	
}

//Fonction de l'algorithme sloveur SAT A*
void aEtoile(int h)
{
	
}
