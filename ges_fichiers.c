/* Fichier ges_fichier.c contient les fonctions de gestino de fichiers
 * Dernière modification 27-03-2015
 * */

#include "main.h"

//Affichage du tableau de littéraux
void afficherLitt(Litteral* tabLitt,int nbLitt)
{
	//Déclaration de variables
	int i=0;
	Entier *tmp=NULL;
	
	for(i=0;i<nbLitt;i++)
	{
		printf("Le littéral %d apparait dans les clauses:\n",i+1);
		tmp=tabLitt[i].tete;
		while(tmp!=NULL)
		{
			printf("%d ",tmp->id);
			tmp=tmp->suivant;
		}
		printf("\n");
	}
}	

//Ajoute un élément à la liste chainée de clauses qui compose un littéral
Litteral *ajouterClause(Litteral* tabLitt,int aAjouter,int index)
{
	//Déclaration de variables
	Entier *clause=NULL;
	
	//Décrémentation de l'index
	//Les index de tableaux commencent par 0 alors que les littéraux commencent par 1
	index--;
	
	//Allocation du nouvel élément de la liste
	clause=(Entier*) malloc(sizeof(Entier));
	if(clause==NULL)
	{
		fprintf(stderr,"erreur lors de l'allocation d'un élément entier pour la clause %d\n",aAjouter);
		exit(EXIT_FAILURE);
	}
	
	//Affectation des valeurs du nouvel élément
	clause->id=aAjouter;
	clause->suivant=tabLitt[index].tete;
	
	//Ajout du nouvel élément au début de la liste
	tabLitt[index].tete=clause;
	
	return tabLitt;
}	

//Fonction de décomposition d'une ligne représentant une clause dans le fichier de benchmark
//Cette fonction ajoute le numéro de la clause en entrée a tout les littéraux ou il apparait
Litteral *decomposerLigne(Litteral *tabLitt,char *ligne,int numClause)
{
	//Déclaration de variables
	int i=0,j=0,valeurLitteral;
	char nombre[10];
	
	//Décomposition de la ligne
	while(ligne[i]!='\n')
	{
		if(ligne[i]==' ')//Si le caractère actuel est un blanc
		{
			if((i>0)&&(ligne[i-1]>='0'&&ligne[i-1]<='9')) //Si l'espace n'est pas en début de ligne et si il est précédé par un chiffre.
			{
				//Ajouter le numéro de clause a la liste du littéral nombre 
				nombre[j]='\0';
				valeurLitteral=(int)strtol(nombre,NULL,10);
				if(valeurLitteral>0)//est > 0
				{
					tabLitt=ajouterClause(tabLitt,numClause,valeurLitteral);
				}
				else if(valeurLitteral<0)// est < 0
				{
					tabLitt=ajouterClause(tabLitt,(numClause*-1),(-1*valeurLitteral));
				} 
				j=0;
			}
		} 
		else if(((ligne[i]>='0')&&(ligne[i]<='9'))||(ligne[i]=='-'))//si c'est un chiffre ou '-'
		{
			if(ligne[i]=='-')
			{
				if((i-1>0)&&(ligne[i-1]!=' ')) //Afin d'éviter d'avoir des '-' au mileu d'un nombre
				{
					fprintf(stderr,"Fichier erronné (- précédé par autre chose que blanc), clause %d erronée\n",numClause);
					break;
				}
				else
				{
					j=1;
					nombre[0]='-';
				}
			}
			else //C'est un chiffre
			{
				nombre[j]=ligne[i];
				j++;
			}	
		}
		
		i++; //Avancer au caractère suivant de la ligne
	}
	
	return tabLitt;
}

//Fonction de lecture de fichier de benchmark
Litteral *lectureDeFichier(char *chemin,int *nbClauses,int *nbLitteraux)
{
	//Déclaration de variables 
	FILE *fichier=NULL;
	char ligne[256]="vide";//Limitation du nombre de caractère par ligne à 255 caractères
	char nombre[10],nombre2[10];//Limitation du nombre de chiffres dans le nombre de clauses et de littéraux a 9 chiffres
	int i=1,j=0;
	Litteral *tabLitt=NULL;//La table de littéraux 
	
	printf("Début de la lécture du fichier %s\n",chemin);
	
	//Ouverture du fichier en mode lecture
	fichier=fopen(chemin,"r");
	if(fichier==NULL)
	{
		fprintf(stderr,"erreur lors de l'ouverture du fichier de benchmark\n");
		exit(EXIT_FAILURE);
	}
	
	//Ignorer les lignes précédant la ligne commançant par p
	while(ligne[0]!='p')
	{
		fgets(ligne,255,fichier);
	}
	
	//Saut des caractères non-numériques et des zéros
	while(ligne[i]<'1' || ligne[i]>'9') i++;
	
	//Lecture du nombre de littéraux
	while(ligne[i]!=' ')
	{
		nombre[j]=ligne[i];
		i++;
		j++;
	}
	nombre[j]='\0';
	*nbLitteraux=(int)strtol(nombre,NULL,10);
	
	//Saut des caractères non-numériques et des zéros
	while(ligne[i]<'1' || ligne[i]>'9') i++;
	
	//Lecture du nombre de clauses
	j=0;
	while(ligne[i]!=' ')
	{
		nombre2[j]=ligne[i];
		i++;
		j++;
	}
	nombre2[j]='\0';
	*nbClauses=(int)strtol(nombre2,NULL,10);
	
	//Allocation de la table de littéraux
	tabLitt=(Litteral*)malloc(*nbLitteraux*sizeof(Litteral));
	
	//Initialisation des éléments tête de chaque littéral a null
	for(i=0;i<*nbLitteraux;i++)
	{
		tabLitt[i].tete=NULL;
	}
	
	//Lecture des clauses et variables 
	for(i=0;i<*nbClauses;i++)
	{
		fgets(ligne,255,fichier);
		tabLitt=decomposerLigne(tabLitt,ligne,i+1);
	}
	
	printf("Fin de la lécture du fichier %s\n",chemin);

	//Fermeture du fichier de benchmark
	fclose(fichier);
	
	return tabLitt;
}
