/* Fichier de gestion des états 
 * dérnière modification 31/03/2015
 * */
 
#include "main.h"
#include "ges_fichiers.h"
#include <string.h>

//Fonction d'affichage de chemin
void afficherChemin(Entier *tete)
{
	//Déclaration de variables
	Entier *tmp=tete;
	
	if(tmp==NULL)
	{
		printf("Le chemin est vide, état initial\n");
	}
	else
	{
		printf("\n\nLe chemin qui a mené a cet état est:\n");
		while(tmp!=NULL)
		{
			printf("%d ",tmp->id);
			tmp=tmp->suivant;
		}
		printf("\n");
	}
}

//Fonction d'affichage d'état
void afficherEtat(Open *etat)
{
	//Déclaration de variables
	int i=0;
	extern int taille;
	
	//Affichage du chemin menant a cet état 
	afficherChemin(etat->chemin);
	
	//Parcours de l'état
	printf("États des clauses:\n");
	for(i=0;i<taille;i++)
	{
		printf("la clause %d à l'état: %c\n",i+1,(etat->e)[i]);
	}
}

//Ajout a la liste chemin d'un état, cette fonction ajoute au début
Entier *nouveauChemin(Entier *source,int val)
{
	//Déclaration de variables
	Entier *tmp=NULL,*tmp2=NULL,*parcourt=source,*chemin=NULL;
	
	//Allocation de la tête du nouveau chemin
	chemin=(Entier*)malloc(sizeof(Entier));
	if(chemin==NULL)
	{
		fprintf(stderr,"erreur lors de la création de la tête du nouveau chemin\n");
		exit(EXIT_FAILURE);
	}
	
	//Si le chemin source est vide, le chemin est consititué de val seulement
	if(parcourt==NULL)
	{
		chemin->id=val;
		chemin->suivant=NULL;
	}
	else
	{
		//Copie du permier élément de la source a la nouvelle tête
		chemin->id=parcourt->id;
		chemin->suivant=NULL;
		parcourt=parcourt->suivant;
		tmp2=chemin;
		
		//Parcourt du reste de la source
		while(parcourt!=NULL)
		{
			//Copie et chainage
			tmp=(Entier*)malloc(sizeof(Entier));
			if(tmp==NULL)
			{
				fprintf(stderr,"erreur lors de la copie d'un élément de chemin\n");
				exit(EXIT_FAILURE);
			}
			
			tmp->id=parcourt->id;
			parcourt=parcourt->suivant;
			tmp->suivant=NULL;
			tmp2->suivant=tmp;
			tmp2=tmp;
		}
		
		//allocation du nouvel élément
		tmp=(Entier*)malloc(sizeof(Entier));
		if(tmp==NULL)
		{
			fprintf(stderr,"erreur lors de la copie d'un élément de chemin\n");
			exit(EXIT_FAILURE);
		}
		
		tmp->id=val;
		tmp->suivant=NULL;
		tmp2->suivant=tmp;	
	}
		
	return chemin;
}

//Fonction qui retourne le niveau actuel d'un état 
//En comptant le nombre d'éléments de la liste chemin
int compteurNiveau(Entier *tete)
{
	//Déclaration de variables
	int compteur=0;
	Entier *tmp=tete;
	
	//parcoure de la liste
	while(tmp!=NULL)
	{
		compteur++;
		tmp=tmp->suivant;
	}
	
	return compteur;
}

//Fonction d'initialisations des données 
Litteral* init(char *benchmark,int *nbClauses,int *nbLitt,Open **etatInit)
{
	//Déclarationd de variables 
	Litteral *tab=NULL;
	int i=0;
	extern int taille;//variable globale taille de table de clauses
	
	//Lecteur du fichier de benchmark
	tab=lectureDeFichier(benchmark,nbClauses,nbLitt);
	
	//Affectation du nombre de clauses de l'état initial à taille 
	taille=*nbClauses;
	
	//Allocation de l'état initial
	*etatInit=(Open*)malloc(sizeof(Open));
	if(*etatInit==NULL)
	{
		fprintf(stderr,"erreur lors de l'allocation de l'état initial\n");
		exit(EXIT_FAILURE);
	}
	
	//Allocation de la table d'états de clauses de l'état initial
	(*etatInit)->e=(char*)malloc(taille*sizeof(char));
	if((*etatInit)->e==NULL)
	{
		fprintf(stderr,"erreur lors de l'allocation de la table d'états de clauses de l'état initial\n");
		exit(EXIT_FAILURE);
	}

	//Initialisation des valeurs d'états de clauses a '0' (0 visite)
	for(i=0;i<taille;i++)
	{
		(*etatInit)->e[i]='0';
	}	
	
	//Initialisation du chemin qui a mené a l'état
	//l'état initial ne vient de nulle part
	(*etatInit)->chemin=NULL;
	
	return tab;
}

//Fonction d'ajout d'état a la liste open, à la fin de celle ci
void AjouterAOpen(Open **tete,Open *etat)
{
	//Déclaration de varaibles
	Open *tmp=NULL,*tmp2=NULL;
	
	//Si la tete est vide
	if(*tete==NULL)
	{
		(*tete)=etat;
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
		
		//Affectation des valeurs du nouvel élément et chainage
		tmp2=etat;
		tmp2->suivant=NULL;
		tmp->suivant=tmp2;
	}
}

//Fonction de dépiler état de la liste Open
Open *depiler(Open **tete)
{
	//Déclaration de variables
	Open *tmp=NULL;
	
	//Affectation de la tete au temporaire
	tmp=*tete;
	
	//Mise du suivant de la tête a la tête de la liste Open
	(*tete)=(*tete)->suivant;
	
	return tmp;
}

//Fonction de test si l'état en entrée est un état final ou faux
char typeEtat(Open *etat)
{
	//Déclaration de vairables
	int i=0;
	char type='S';
	extern int taille;
	
	//parcourt de l'état
	for(i=0;i<taille;i++)
	{
		//Si une seule clause est fausse l'état est UNSAT
		if((etat->e)[i]=='U') return 'U';
		
		//Si une clause n'est pas encore SAT et n'est pas UNSAT
		if((etat->e)[i]!='S') type=' ';
	}
	
	return type;
}

//Fonction d'allocation et de copie d'une table d'état de clause
char* copieTable(char *source)
{
	//Déclaration de variables
	int i=0;
	char *table=NULL;
	extern int taille;
	
	//Allocation de la table
	table=(char*)malloc(sizeof(char)*taille);
	if(table==NULL)
	{
		fprintf(stderr,"erreur lors de l'allocation de la table d'état de clauses\n");
		exit(EXIT_FAILURE);
	}
	
	//Copie des élément de la source a table
	for(i=0;i<taille;i++)
	{
		table[i]=source[i];
	}
	
	return table;
}

//Fonction de génération d'un état fils selon la variable val
Open *genererEtat(Open *etatP,int val,Litteral *tabLitt,int nbLitt)
{
	//Déclaration de variable
	int litteral=0,clause=0;
	Open *etat=NULL;
	extern int taille;
	char *tableau=NULL;
	Entier *tmp=NULL;
	int i=0;
		
	//Compter le niveau, et donc le littéral auquel on affecte la valeur
	litteral=compteurNiveau(etatP->chemin);
		
	//Copie de la table d'état de l'état père dans tableau	
	tableau=copieTable(etatP->e);
		
	//Affectation des nouveaux états dans la table d'états 
	tmp=tabLitt[litteral].tete;
	while(tmp!=NULL)
	{
		clause=tmp->id;
		
		if((clause*val)>0)
		{
			tableau[(abs(clause))-1]='S';
		}
		else
		{
			switch(tableau[(abs(clause))-1])
			{
				case '0':
					tableau[(abs(clause))-1]='1';
					break;
				case '1':
					tableau[(abs(clause))-1]='2';
					break;
				case '2':
					tableau[(abs(clause))-1]='U';
					break;
			}
		}
		tmp=tmp->suivant;
	}
			
	//Allocation du nouvel état
	etat=(Open*)malloc(sizeof(Open));
	if(etat==NULL)
	{
		fprintf(stderr,"erreur lors de l'allocation du nouvel état\n");
		exit(EXIT_FAILURE);
	}
	
	//Affectation des valeurs au nouvel état
	etat->chemin=nouveauChemin(etatP->chemin,(litteral+1)*val);	
	etat->e=tableau;	
	etat->suivant=NULL;
	
	return etat;
}

//Fonction de libération de liste d'entier
void libererEntier(Entier **tete)
{
	//Déclaration de variables
	Entier *tmp=NULL;
	
	while(*tete!=NULL)
	{
		tmp=(*tete);
		*tete=(*tete)->suivant;
		free(tmp);
	}
}

//Fonction de libération de l'espace mémoire qu'occupe un état
void liberer(Open **etat)
{
	Open *tmp=(*etat);
	
	if(*etat!=NULL)
	{
		libererEntier(&(tmp->chemin));
		free(tmp->e);
		free(tmp);
		(*etat)=NULL;
	}
}
