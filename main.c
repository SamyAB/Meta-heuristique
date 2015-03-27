/* Fichier principal du projet de Méta-heuristique
 * Dérnière modification 27-03-2015
 * Crée par SamyAB
 * */
 
#include "main.h"

//Fonction main
int main(int argc,char** argv)
{
	//Déclaration de variables
	int choix=0,quitter=0;
	
	//Boucle principale du programme
	while(!quitter)
	{
		//Affichage du menu
		printf("==== Bienvenu, faites votres choix ====\n");
		printf("1.Solveur largeur d'abord\n");
		printf("2.Solveur profondeur d'abord\n");
		printf("3.Solveur A* \n");
		printf("4.Quitter");
		printf("1, 2, 3, ou 4");
		scanf("%d",&choix);
		
		//Choix d'une tache
		switch(choix)
		{
			case 1:
				//Solveur largeur d'abord
				
				break;
			case 2:
				//Solveur profondeur d'abord
				
				break;
			case 3:
				//Solveur A*
				
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
