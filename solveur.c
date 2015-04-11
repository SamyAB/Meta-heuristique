/* Fichier solveur.c contient les algorithmes de solveurs SAT 
 * Dans l'esapce des états
 * dérnière modification 11/04/2015	
 * */
 
#include "main.h"
#include "ges_etats.h"
#include <time.h>
#include <sys/resource.h>

//Fonction de l'algorithme solveur SAT en largeur
void largeur()
{
	//Déclaration de variables
	Litteral *tabLitt=NULL;
	int nbClauses=0,nbLitt=0;
	Open *etatInitial=NULL,*etatActuel=NULL,*queue=NULL;
	Open *tete=NULL;
	char typeE=' ';
	extern int nbClausesSatMax;//Variable globale (nombre max de clauses SAT)
	int nbEtatGenere=0,nbEtatEchec=0,tailleListeOpen=1,tailleMaxListOpen=1;//Métriques
	struct rusage rusage; //Structure contenant les informations sur les recources utilisées par le processus 
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
		tailleListeOpen--;
		
		//Récupération du type de l'état acutel
		typeE=typeEtat(etatActuel);
		
		//Test si l'état actuel est un état final (SAT)
		if(typeE=='S')
		{
			printf("La formule est SAT\n");
			printf("Le nombre d'états générés est %d\n",nbEtatGenere);
			printf("Le nombre d'états d'échec est %d\n",nbEtatEchec);
			printf("La taille maximal de la liste open est %d\n",tailleMaxListOpen);
			printf("Le temps passé est %lf\n",((double)(clock()-debut)/CLOCKS_PER_SEC));
			afficherChemin(etatActuel->chemin);
			break;
		}
		
		//Test si l'état est faux (UNSAT)
		if(typeE=='U')
		{
			liberer(&etatActuel);
			nbEtatEchec++;
			typeE=' ';
			continue;
		}
		
		//Récupération de la quantité de RAM utilisée
		getrusage(RUSAGE_SELF,&rusage);
		if((rusage.ru_maxrss)>RAM_MAX)
		{
			printf("Quantitée de RAM maximale dépassée\n");
			printf("Le nombre d'états générés est %d\n",nbEtatGenere);
			printf("Le nombre d'états d'échec est %d\n",nbEtatEchec);
			printf("Le nombre maximum de clauses SAT est %d/%d\n",nbClausesSatMax,nbClauses);
			printf("La taille maximal de la liste open est %d\n",tailleMaxListOpen);
			printf("Le niveau maximum atteint est %d\n",compteurNiveau(etatActuel->chemin));
			printf("Le temps passé est %lf\n",((double)(clock()-debut)/CLOCKS_PER_SEC));		
			exit(EXIT_SUCCESS);
		}
		
		//Génération des états fils et leurs ajouts a la liste OPEN
		ajouterAOpen(&tete,&queue,genererEtat(etatActuel,1,tabLitt,nbLitt));
		ajouterAOpen(&tete,&queue,genererEtat(etatActuel,-1,tabLitt,nbLitt));
		nbEtatGenere+=2;
		tailleListeOpen+=2;
		if(tailleListeOpen>tailleMaxListOpen) tailleMaxListOpen=tailleListeOpen;
		
		//Libération de l'espace mémoir occupé par l'état actuel
		liberer(&etatActuel);

	}
	
	//Si l'état de sorti n'est pas SAT
	if(typeE!='S') 
	{
		printf("La formule est UNSAT\n");
		printf("Le nombre d'état généré est : %d\n",nbEtatGenere);
		printf("Le nombre d'état d'echec est : %d\n",nbEtatEchec);
		printf("La Taille max de la liste Open est : %d\n",tailleMaxListOpen);
		printf("Le temps passé est %lf\n",((double)(clock()-debut)/CLOCKS_PER_SEC));
	}
	
}

//Fonction de l'algorithem solveur SAT en profondeur
void profondeur()
{
	//Déclaration de variables
	Litteral *tabLitt=NULL;
	int nbClauses=0,nbLitt=0;
	Open *etatInitial=NULL,*etatActuel=NULL,*queue=NULL;
	Open *tete=NULL;
	char typeE=' ';
	int nbEtatGenere=0,nbEtatEchec=0,tailleListeOpen=1,tailleMaxListOpen=1;//Métriques
	clock_t debut=clock();
	
	//Initialisation des données
	tabLitt=init("test.cnf",&nbClauses,&nbLitt,&etatInitial);
	
	//Ajout de la tete a la liste open
	empilerEtat(&tete,etatInitial);
	
	//Boucle principale du solveur
	while(tete!=NULL)
	{
		//Récupérer l'état a explorer
		etatActuel=depiler(&tete);
		tailleListeOpen--;
		
		//Récupération du type de l'état acutel
		typeE=typeEtat(etatActuel);
		
		//Test si l'état actuel est un état final (SAT)
		if(typeE=='S')
		{
			printf("La formule est SAT\n");
			printf("Le nombre d'états générés est %d\n",nbEtatGenere);
			printf("Le nombre d'états d'échec est %d\n",nbEtatEchec);
			printf("La taille maximal de la liste open est %d\n",tailleMaxListOpen);
			printf("Le temps passé est %lf\n",((double)(clock()-debut)/CLOCKS_PER_SEC));
			afficherChemin(etatActuel->chemin);
			break;
		}
		
		//Test si l'état est faux (UNSAT)
		if(typeE=='U')
		{
			typeE=' ';
			liberer(&etatActuel);
			continue;
		}
		
		//Test de limite du temps d'éxecution
		if(((double)(clock()-debut)/CLOCKS_PER_SEC)>TEMPS_MAX)
		{
			printf("Le temps max d'éxecution est dépassé\n");
			printf("Le nombre d'états générés est %d\n",nbEtatGenere);
			printf("Le nombre d'états d'échec est %d\n",nbEtatEchec);
			printf("Le nombre maximum de clauses SAT est %d/%d\n",nbClausesSatMax,nbClauses);
			printf("La taille maximal de la liste open est %d\n",tailleMaxListOpen);
			printf("Le temps passé est %lf\n",((double)(clock()-debut)/CLOCKS_PER_SEC));		
			exit(EXIT_SUCCESS);
		}
		
		//Génération des états fils et leurs ajouts a la liste OPEN
		empilerEtat(&tete,genererEtat(etatActuel,-1,tabLitt,nbLitt));
		empilerEtat(&tete,genererEtat(etatActuel,1,tabLitt,nbLitt));
		nbEtatGenere+=2;
		tailleListeOpen+=2;
		if(tailleListeOpen>tailleMaxListOpen) tailleMaxListOpen=tailleListeOpen;
		
		//Libération de l'espace mémoir occupé par l'état actuel
		liberer(&etatActuel);

	}
	
	//Si l'état de sorti n'est pas SAT
	if(typeE!='S') 
	{
		printf("La formule est UNSAT\n");
		printf("Le nombre d'état généré est : %d\n",nbEtatGenere);
		printf("Le nombre d'état d'echec est : %d\n",nbEtatEchec);
		printf("La Taille max de la liste Open est : %d\n",tailleMaxListOpen);
		printf("Le temps passé est %lf\n",((double)(clock()-debut)/CLOCKS_PER_SEC));
	}
}

//Fonction de de l'algorithme de solveur A* avec l'heuristique 1
void aEtoileH1()
{
	//Déclaration de variables
	Litteral *tabLitt=NULL;
	int nbClauses,nbLitt;
	Open *tete=NULL,*etatActuel=NULL,*etatInitial=NULL;
	char typeE=' ';
	int nbEtatGenere=0,nbEtatEchec=0,tailleListeOpen=1,tailleMaxListOpen=1;//Métriques
	clock_t debut=clock();
	
	//Initialisation des données
	tabLitt=init("test.cnf",&nbClauses,&nbLitt,&etatInitial);
	
	//Ajout de l'état intial a la liste Open
	empilerEtat(&tete,etatInitial);
	
	//Début de la boucle principale de l'algorithme
	while(tete!=NULL)
	{
		//Retrouver l'état actuel
		etatActuel=f1(&tete,nbClauses);
		tailleListeOpen--;
		
		//Récupération du type de l'état acutel
		typeE=typeEtat(etatActuel);
		
		//Test si l'état actuel est un état final (SAT)
		if(typeE=='S')
		{
			printf("La formule est SAT\n");
			printf("Le nombre d'états générés est %d\n",nbEtatGenere);
			printf("Le nombre d'états d'échec est %d\n",nbEtatEchec);
			printf("La taille maximal de la liste open est %d\n",tailleMaxListOpen);
			printf("Le temps passé est %lf\n",((double)(clock()-debut)/CLOCKS_PER_SEC));
			afficherChemin(etatActuel->chemin);
			break;
		}
		
		//Test si l'état est faux (UNSAT)
		if(typeE=='U')
		{
			liberer(&etatActuel);
			typeE=' ';
			continue;
		}
		
		//Test de limite du temps d'éxecution
		if(((double)(clock()-debut)/CLOCKS_PER_SEC)>TEMPS_MAX)
		{
			printf("Le temps max d'éxecution est dépassé\n");
			printf("Le nombre d'états générés est %d\n",nbEtatGenere);
			printf("Le nombre d'états d'échec est %d\n",nbEtatEchec);
			printf("Le nombre maximum de clauses SAT est %d/%d\n",nbClausesSatMax,nbClauses);
			printf("La taille maximal de la liste open est %d\n",tailleMaxListOpen);
			printf("Le temps passé est %lf\n",((double)(clock()-debut)/CLOCKS_PER_SEC));		
			exit(EXIT_SUCCESS);
		}
		
		//Génération des états fils et leurs ajouts a la liste OPEN
		empilerEtat(&tete,genererEtat(etatActuel,-1,tabLitt,nbLitt));
		empilerEtat(&tete,genererEtat(etatActuel,1,tabLitt,nbLitt));
		nbEtatGenere+=2;
		tailleListeOpen+=2;
		if(tailleListeOpen>tailleMaxListOpen) tailleMaxListOpen=tailleListeOpen;
		
		//Libération de l'espace mémoir occupé par l'état actuel
		liberer(&etatActuel);
	}
	
	//Si l'état de sorti n'est pas SAT
	if(typeE!='S') 
	{
		printf("La formule est UNSAT\n");
		printf("Le nombre d'état généré est : %d\n",nbEtatGenere);
		printf("Le nombre d'état d'echec est : %d\n",nbEtatEchec);
		printf("La Taille max de la liste Open est : %d\n",tailleMaxListOpen);
		printf("Le temps passé est %lf\n",((double)(clock()-debut)/CLOCKS_PER_SEC));
	}
}
	
//Fonction de de l'algorithme de solveur A* avec l'heuristique 2
void aEtoileH2()
{
	//Déclaration de variables
	Litteral *tabLitt=NULL;
	int nbClauses,nbLitt;
	Open *tete=NULL,*etatActuel=NULL,*etatInitial=NULL;
	char typeE=' ';
	int nbEtatGenere=0,nbEtatEchec=0,tailleListeOpen=1,tailleMaxListOpen=1;//Métriques
	clock_t debut=clock();
	
	//Initialisation des données
	tabLitt=init("test.cnf",&nbClauses,&nbLitt,&etatInitial);
	
	//Ajout de l'état intial a la liste Open
	empilerEtat(&tete,etatInitial);
	
	//Début de la boucle principale de l'algorithme
	while(tete!=NULL)
	{
		//Retrouver l'état actuel
		etatActuel=f2(&tete,nbClauses);
		tailleListeOpen--;
		
		//Récupération du type de l'état acutel
		typeE=typeEtat(etatActuel);
		
		//Test si l'état actuel est un état final (SAT)
		if(typeE=='S')
		{
			typeE=' ';
			printf("La formule est SAT\n");
			printf("Le nombre d'états générés est %d\n",nbEtatGenere);
			printf("Le nombre d'états d'échec est %d\n",nbEtatEchec);
			printf("La taille maximal de la liste open est %d\n",tailleMaxListOpen);
			printf("Le temps passé est %lf\n",((double)(clock()-debut)/CLOCKS_PER_SEC));
			afficherChemin(etatActuel->chemin);
			break;
		}
		
		//Test si l'état est faux (UNSAT)
		if(typeE=='U')
		{
			typeE=' ';
			liberer(&etatActuel);
			continue;
		}
		
		//Test de limite du temps d'éxecution
		if(((double)(clock()-debut)/CLOCKS_PER_SEC)>TEMPS_MAX)
		{
			printf("Le temps max d'éxecution est dépassé\n");
			printf("Le nombre d'états générés est %d\n",nbEtatGenere);
			printf("Le nombre d'états d'échec est %d\n",nbEtatEchec);
			printf("Le nombre maximum de clauses SAT est %d/%d\n",nbClausesSatMax,nbClauses);
			printf("La taille maximal de la liste open est %d\n",tailleMaxListOpen);
			printf("Le temps passé est %lf\n",((double)(clock()-debut)/CLOCKS_PER_SEC));		
			exit(EXIT_SUCCESS);
		}
		
		//Génération des états fils et leurs ajouts a la liste OPEN
		empilerEtat(&tete,genererEtat(etatActuel,-1,tabLitt,nbLitt));
		empilerEtat(&tete,genererEtat(etatActuel,1,tabLitt,nbLitt));
		nbEtatGenere+=2;
		tailleListeOpen+=2;
		if(tailleListeOpen>tailleMaxListOpen) tailleMaxListOpen=tailleListeOpen;
		
		//Libération de l'espace mémoir occupé par l'état actuel
		liberer(&etatActuel);
	}
	
	//Si l'état de sorti n'est pas SAT
	if(typeE!='S') 
	{
		printf("La formule est UNSAT\n");
		printf("Le nombre d'état généré est : %d\n",nbEtatGenere);
		printf("Le nombre d'état d'echec est : %d\n",nbEtatEchec);
		printf("La Taille max de la liste Open est : %d\n",tailleMaxListOpen);
		printf("Le temps passé est %lf\n",((double)(clock()-debut)/CLOCKS_PER_SEC));
	}
}

//Fonction de de l'algorithme de solveur A* avec l'heuristique 3
void aEtoileH3()
{
	//Déclaration de variables
	Litteral *tabLitt=NULL;
	int nbClauses,nbLitt;
	Open *tete=NULL,*etatActuel=NULL,*etatInitial=NULL;
	char typeE=' ';
	int nbEtatGenere=0,nbEtatEchec=0,tailleListeOpen=1,tailleMaxListOpen=1;//Métriques
	clock_t debut=clock();
	
	//Initialisation des données
	tabLitt=init("test.cnf",&nbClauses,&nbLitt,&etatInitial);
	
	//Ajout de l'état intial a la liste Open
	empilerEtat(&tete,etatInitial);
	
	//Début de la boucle principale de l'algorithme
	while(tete!=NULL)
	{
		//Retrouver l'état actuel
		etatActuel=f3(&tete,nbClauses);
		tailleListeOpen--;
	
		//Récupération du type de l'état acutel
		typeE=typeEtat(etatActuel);
		
		//Test si l'état actuel est un état final (SAT)
		if(typeE=='S')
		{
			typeE=' ';
			printf("La formule est SAT\n");
			printf("Le nombre d'états générés est %d\n",nbEtatGenere);
			printf("Le nombre d'états d'échec est %d\n",nbEtatEchec);
			printf("La taille maximal de la liste open est %d\n",tailleMaxListOpen);
			printf("Le temps passé est %lf\n",((double)(clock()-debut)/CLOCKS_PER_SEC));
			afficherChemin(etatActuel->chemin);
			break;
		}
		
		//Test si l'état est faux (UNSAT)
		if(typeE=='U')
		{
			nbEtatEchec++;
			liberer(&etatActuel);
			typeE=' ';
			continue;
		}
		
		//Test de limite du temps d'éxecution
		if(((double)(clock()-debut)/CLOCKS_PER_SEC)>TEMPS_MAX)
		{
			printf("Le temps max d'éxecution est dépassé\n");
			printf("Le nombre d'états générés est %d\n",nbEtatGenere);
			printf("Le nombre d'états d'échec est %d\n",nbEtatEchec);
			printf("Le nombre maximum de clauses SAT est %d/%d\n",nbClausesSatMax,nbClauses);
			printf("La taille maximal de la liste open est %d\n",tailleMaxListOpen);
			printf("Le temps passé est %lf\n",((double)(clock()-debut)/CLOCKS_PER_SEC));		
			exit(EXIT_SUCCESS);
		}
		
		//Génération des états fils et leurs ajouts a la liste OPEN
		empilerEtat(&tete,genererEtat(etatActuel,-1,tabLitt,nbLitt));
		empilerEtat(&tete,genererEtat(etatActuel,1,tabLitt,nbLitt));
		nbEtatGenere+=2;
		tailleListeOpen+=2;
		if(tailleListeOpen>tailleMaxListOpen) tailleMaxListOpen=tailleListeOpen;
		
		//Libération de l'espace mémoir occupé par l'état actuel
		liberer(&etatActuel);
	}
	
	//Si l'état de sorti n'est pas SAT
	if(typeE!='S') 
	{
		printf("La formule est UNSAT\n");
		printf("Le nombre d'état généré est : %d\n",nbEtatGenere);
		printf("Le nombre d'état d'echec est : %d\n",nbEtatEchec);
		printf("La Taille max de la liste Open est : %d\n",tailleMaxListOpen);
		printf("Le temps passé est %lf\n",((double)(clock()-debut)/CLOCKS_PER_SEC));
	}
}


