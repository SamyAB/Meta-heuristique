/* Fichier de gestion des états 
 * dérnière modification 30/03/2015
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
		fprintf(stderr,"erreur lors de l'alocation de la table d'états\n");
		exit(EXIT_FAILURE);
	}

	for(i=0;i<(*nbClauses);i++)
	{
		(*tabInit)[i].e='0';
	}	

	return tab;
}

//Fonction d'ajout d'état a la liste open, à la fin de celle ci
void AjouterAOpen(Open **tete,Etat *etat)
{
	//Déclaration de varaibles
	Open *tmp=NULL,Open *tmp2=NULL;
	
	//Si la tete est vide
	if(*tete==NULL)
	{
		//Allocation de la tête
		*tete=(Open*)malloc(sizeof(Open));
		if(*tete==NULL)
		{
			fprintf(stderr,"erreur lors de l'allocation de la tête de la liste Open\n");
			exit(EXIT_FAILURE);
		}
		
		//Affectation des valeurs a la tête
		(*tete)->e=etat;
		(*tete)->suivant=NULL;
	}
	else
	{
		//Initialisation des temporaires
		tmp=(*tete);
		tmp2=tmp->suivant;
		
		//Parcourt de la liste jusqu'à la fin
		while(tmp2!=NULL)
		{
			tmp=tmp->suivant;
			tmp2=tmp2->suivant;
		}
		
		//Allocation du nouvel élément
		tmp2=(Open*)malloc(sizeof(Open));
		if(tmp2==NULL)
		{
			fprintf(stderr,"erreur lors de l'allocation d'un élément de la liste Open\n");
			exit(EXIT_FAILURE);
		}
		
		//Affectation des valeurs du nouvel élément et chainage
		tmp2->e=etat;
		tmp2->suivant=NULL;
		tmp->suivant=tmp2;
	}
}
