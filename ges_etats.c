/* Fichier de gestion des états 
 * dérnière modification 11/04/2015
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

//Fonction comptant le nombre de clauses SAT
int compteurNbClausesSat(char *tab,int nbClauses)
{
	//Déclaration de variables
	int i=0,nbClausesSat=0;


	for(i=0;i<nbClauses;i++)
	{
		if(tab[i]=='S') nbClausesSat++;
	}
	
	return nbClausesSat;
}

//Fonction d'initialisations des données 
Litteral* init(char *benchmark,int *nbClauses,int *nbLitt,Open **etatInit)
{
	//Déclarationd de variables 
	Litteral *tab=NULL;
	int i=0;
	extern int taille;//variable globale taille de table de clauses
	extern int nbClausesSatMax;//variable globale de nombre max de clauses SAT
	
	//Initialisation du nombre max de clauses SAT a 0
	nbClausesSatMax=0;
	
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
void ajouterAOpen(Open **tete,Open **queue,Open *etat)
{
	etat->suivant=NULL;
	if(*tete==NULL)
	{
		(*tete)=etat;
		(*queue)=etat;
	}
	else
	{
		(*queue)->suivant=etat;
		(*queue)=etat;
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

//Fonction d'ajout d'un état au début de la liste Open
void empilerEtat(Open **tete,Open *etat)
{
	//
	etat->suivant=(*tete);
	(*tete)=etat;
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
	int litteral=0,clause=0,nbClausesSat=0;
	Open *etat=NULL;
	extern int taille;
	extern int nbClausesSatMax;
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
			nbClausesSat++;
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
				case 'S':
					nbClausesSat++;
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
	
	//Comparer le nombre de clauses SAT du nouvle état avec le nombre max de clauses SAT
	if(nbClausesSat>nbClausesSatMax)
	{
		nbClausesSatMax=nbClausesSat;
	}
	
	return etat;
}

//Fonction de libération de liste d'entier
void libererEntier(Entier **tete)
{
	//Déclaration de variables
	Entier *tmp=NULL;
	
	//Parcourt de la liste 
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
	//Déclaration de variables
	Open *tmp=(*etat);
	
	//Si l'état n'est pas déjà vide
	if(*etat!=NULL)
	{
		//Libération de l'espace mémoir occupé par le chemin
		libererEntier(&(tmp->chemin));
		
		//Libération de la table de caractères d'états de clauses
		free(tmp->e);
		
		//Libération de l'état
		free(tmp);
		
		//Affectation de null a l'état
		(*etat)=NULL;
	}
}

//Fonction de calcule du nombre de visite de clauses (heuristique 2)
int visite(char *tab,int nbClause)
{
	//Déclaration de variables
	int i=0,visite;
	
	for(i=0;i<nbClause;i++)
	{
		switch(tab[i])
		{
			case '1':
				visite++;
				break;
			case '2':
				visite+=2;
				break;
		}
	}
	
	return visite;
}

//Fonction de récupération d'état en utilisant h1
Open *f1(Open **tete,int nbClauses)
{
	//Déclaration de variables
	Open *etat=NULL,*parcourt=*tete,*precedent=NULL,*tmp=NULL;
	int prio=0,niveau=0,nbClauseSat=0,prioMax=0;
	
	//Parcourt de la liste Open
	while(parcourt!=NULL)
	{
		//Récupération du niveau et du nombre de clauses SAT
		niveau=compteurNiveau(parcourt->chemin);//Fait office de G
		nbClauseSat=compteurNbClausesSat(parcourt->e,nbClauses);//Fait office de H
		prio=niveau+nbClauseSat;
		
		//Si le niveau + le nombre de clauses sont au niveau max
		if(prio>=prioMax)
		{
			etat=parcourt;
			precedent=tmp;
			prioMax=prio;
		}
		
		//Passage a l'élément suivant de la liste Open
		tmp=parcourt;
		parcourt=parcourt->suivant;
	}
	
	//Si precedent est null l'élement a retourner est la tete de liste
	if(precedent==NULL)
	{
		(*tete)=(*tete)->suivant;
	}
	else
	{
		precedent->suivant=etat->suivant;
	}
	
	return etat;
}

//Fonction de récupération d'état en utilsant h2
Open *f2(Open **tete,int nbClauses)
{
	//Déclaration de variables
	Open *etat=NULL,*parcourt=(*tete),*tmp=NULL,*precedent=NULL;
	int prio=0,prioMax=0,niveau=0,nbVisite=0;
	
	//Parcourt des états
	while(parcourt!=NULL)
	{
		//Récupération du niveau et du nombre de visite
		niveau=compteurNiveau(parcourt->chemin);//représente G
		nbVisite=visite(parcourt->e,nbClauses);//représente H2
		prio=niveau+nbVisite;
		
		//Si le niveau + le nombre de visite est max
		if(prio>=prioMax)
		{
			etat=parcourt;
			precedent=tmp;
			prioMax=prio;
		}
		
		//Passage a l'élément suivant de la liste Open
		tmp=parcourt;
		parcourt=parcourt->suivant;
	}
	
	//Si precedent est null l'élement a retourner est la tete de liste
	if(precedent==NULL)
	{
		(*tete)=(*tete)->suivant;
	}
	else
	{
		precedent->suivant=etat->suivant;
	}
	
	return etat;
}

//Fonction de récupération d'état en utilisant h3
Open *f3(Open **tete,int nbClauses)
{
	//Déclaration de variables
	Open *etat=NULL,*parcourt=(*tete),*tmp=NULL,*precedent=NULL;
	int prio=0,prioMax=0,niveau=0,nbVisite=0,nbClauseSat=0;
	
	//Parcourt des états
	while(parcourt!=NULL)
	{
		//Récupération du niveau et du nombre de visite
		niveau=compteurNiveau(parcourt->chemin);//représente G
		nbVisite=visite(parcourt->e,nbClauses);//représente H2
		nbClauseSat=compteurNbClausesSat(parcourt->e,nbClauses);//Représente H1
		/*H3 étant la somme de H1 et H3 */
		
		prio=niveau+nbVisite+nbClauseSat;
		
		//Si le niveau + le nombre de visite est max
		if(prio>=prioMax)
		{
			etat=parcourt;
			precedent=tmp;
			prioMax=prio;
		}
		
		//Passage a l'élément suivant de la liste Open
		tmp=parcourt;
		parcourt=parcourt->suivant;
	}
	
	//Si precedent est null l'élement a retourner est la tete de liste
	if(precedent==NULL)
	{
		(*tete)=(*tete)->suivant;
	}
	else
	{
		precedent->suivant=etat->suivant;
	}
	
	return etat;
}
		
		
