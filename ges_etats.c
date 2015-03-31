/* Fichier de gestion des états 
 * dérnière modification 31/03/2015
 * */
 
#include "main.h"
#include "ges_fichiers.h"

//Fonction d'affichage de chemin
void afficherChemin(Entier *tete)
{
	//Déclaration de variables
	Entier *tmp=tete;
	
	if(tmp==NULL)
	{
		printf("le chemin est vide, état initial\n");
	}
	else
	{
		printf("le chemin qui a mené a cet état est:\n");
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
	
	//Affichage du chemin menant a cet état 
	afficherChemin(etat->chemin)
	
	//Parcours de l'état
	for(i=0;i<nbClauses;i++)
	{
		printf("la clause %d à l'état: %c\n",i+1,tab[i]);
	}
}

//Ajout a la liste chemin d'un état, cette fonction ajoute au début
void ajoutChemin(Entier **tete,int val)
{
	//Déclaration de variables
	Entier *tmp=NULL;
	
	//Allocation du nouvel élément
	tmp=(Entier*)malloc(sizeof(Entier));
	if(tmp==NULL)
	{
		fprintf(stderr,"erreur lors de l'allocation d'un nouvel élément dans le chemin\n");
		exit(EXIT_FAILURE);
	}
	
	//Afectation des valeurs du nouvel élément et chainage
	tmp->id=val;
	tmp->suivant=*tete;
	*tete=tmp;
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

/*int hashInt(int nombre)
{
	
}*/

//Fonction d'initialisations des données 
Litteral* init(char *benchmark,int *nbClauses,int *nbLitt,Open **etatInit)
{
	//Déclarationd de variables 
	Litteral *tab=NULL;
	int i=0;
	
	//Lecteur du fichier de benchmark
	tab=lectureDeFichier(benchmark,nbClauses,nbLitt);
	
	//Allocation de l'état initial
	*etatInit=(Open*)malloc(sizeof(Open));
	if(*etatInit==NULL)
	{
		fprintf(stderr,"erreur lors de l'allocationd e l'état initial\n";
		exit(EXIT_FAILURE);
	}
	
	//Allocation de la table d'états de clauses de l'état initial
	(*etatInit)->e=(char*)malloc(*nbClauses*sizeof(char));
	if((*tabInit)->e==NULL)
	{
		fprintf(stderr,"erreur lors de l'alocation de la table d'états\n");
		exit(EXIT_FAILURE);
	}

	//Initialisation des valeurs d'états de clauses a '0' (0 visite)
	for(i=0;i<(*nbClauses);i++)
	{
		(*etatInit)->e[i]='0';
	}	
	
	//Initialisation du chemin qui a mené a l'état
	//l'état initial ne vient de nulle part
	*etatInit->chemin=NULL;
	
	return tab;
}

//Fonction d'ajout d'état a la liste open, à la fin de celle ci
void AjouterAOpen(Open **tete,Open *etat)
{
	//Déclaration de varaibles
	Open *tmp=NULL,Open *tmp2=NULL;
	
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
	
	//Si le nombre de clauses est nul la formule dans cet état est SAT
	if(etat->nbClauses==0)
	{
		return 'S';
	}
	
	//parcourt de l'état
	for(i=0;i<(etat->nbClauses);i++)
	{
		//Si une seule clause est fausse l'état est UNSAT
		if((etat->e)[i]=='U') return 'U';
	}
	
	return '';
}

//Fonction de génération d'un état fils selon la variable val
Open *genererEtat(Open *etatP,int val,Litteral *tabLitt,int nbLitt)
{
	//Déclaration de variable
	int litteral=-1;
	Open *etat=NULL;
	
	//Compter le niveau, et donc le littéral auquel on affecte la valeur
	litteral=compteurNiveau(etatP->chemin);
	
	
}

//Fonction de libération de liste d'entier
void libererEntier(Entier **tete)
{
	//Déclaration de variables
	Eniter *tmp=NULL;
	
	while(*tete!=NULL)
	{
		tmp=(*tete)->suivant;
		free(*tete);
		*tete=tmp;
	}
}

//Fonction de libération de l'espace mémoire qu'occupe un état
void liberer(Open **etat)
{
	if(*etat!=NULL)
	{
		libererEntier(&((*etat)->chemin));
		free((*etat)->e);
		free(*etat);
	}
}
