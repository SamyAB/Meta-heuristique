#ifndef GES_FICHIERS
#define GES_FICHIERS

Litteral *ajouterClause(Litteral* tabLitt,int aAjouter,int index);
Litteral *decomposerLigne(Litteral *tabLitt,char *ligne,int numClause);
Litteral *lectureDeFichier(char *chemin,int *nbClauses,int *nbLitteraux);

#endif

