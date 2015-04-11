/* Fichier principal du projet de Méta-heuristique
 * Dernière modification 04-04-2015
 * */
 
#include "main.h"
#include "solveur.h"

//Fonction main
int main(int argc,char** argv)
{
	//Déclaration de variables
	int choix=0,quitter=0;
	int nbClauses=0,nbLitt=0;
	int heuristique=0;
	Litteral *tabLitt=NULL;	
	
	//Boucle principale du programme
	while(!quitter)
	{
		//Affichage du menu
		printf("==== Bienvenu, faites votres choix ====\n");
		printf("1.Solveur largeur d'abord\n");
		printf("2.Solveur profondeur d'abord\n");
		printf("3.Solveur A* \n");
		printf("4.Quitter\n");
		printf("1, 2, 3, ou 4\n");
		scanf("%d",&choix);
		
		//Choix d'une tache
		switch(choix)
		{
			case 1:
				//Solveur largeur d'abord
				largeur(argv[1]);
				break;
			case 2:
				//Solveur profondeur d'abord
				profondeur(argv[1]);
				break;
			case 3:
				//Solveur A*
				printf("quelle heuristique voulez utiliser?\n");
				printf("1.Heuristique 1\n");
				printf("2.Heuristique 2\n");
				printf("3.Heuristique 3\n");
				scanf("%d",&heuristique);
				switch(heuristique)
				{
					case 1:
						aEtoileH1(argv[1]);
						break;
					case 2:
						aEtoileH2(argv[1]);
						break;
					case 3:
						aEtoileH3(argv[1]);
						break;
					default:
						printf("heuristique non éxistante\n");
						break;
				}
				break;
			case 4:
				//Quitter le programme
				quitter=1;
				break;
			default:
				printf("Choix incorrect, veuillez introduire un choix correct\n");
				break;
		}
		choix=0;
	}
	
	return EXIT_SUCCESS;
}	
