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
	int nbClauses=0,nbLitt=0,niveau=0;
	Open *etatInitial=NULL,*etatActuel=NULL;
	Open *tete=NULL;
	char typeE=' ';
	
	//Initialisation des données
	tabLitt=init("test.cnf",&nbClauses,&nbLitt,&etatInitial);
	
	//Ajout de la tete a la liste open
	AjouterAOpen(&tete,etatInitial);
	
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
		AjouterAOpen(&tete,genererEtat(etatActuel,1,tabLitt,nbLitt));
		AjouterAOpen(&tete,genererEtat(etatActuel,-1,tabLitt,nbLitt));
		
		//Libération de l'espace mémoir occupé par l'état actuel
		liberer(&etatActuel);

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
