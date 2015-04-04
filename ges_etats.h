#ifndef GES_ETATS
#define GES_ETATS

void afficherChemin(Entier *tete);
void afficherEtat(char *tab,int nbClauses);
Entier *nouveauChemin(Entier *source,int val);
int compteurNiveau(Entier *tete);
int compteurNbClausesSat(char *tab,int nbClauses);
Litteral *init(char *benchmark,int *nbClauses,int *nbLitteraux,Open **etatInit);
void ajouterAOpen(Open **tete,Open **queue,Open *etat);
Open *depiler(Open **tete);
void empilerEtat(Open **tete,Open *etat);
char typeEtat(Open *etat);
char *copieTable(char *source);
Open *genererEtat(Open *etatP,int val,Litteral *tabLitt,int nbLitt);
void libererEntier(Entier **tete);
void liberer(Open **e);
int visite(char *tab,int nbClause);
Open *f1(Open **tete,int nbClauses);
Open *f2(Open **tete,int nbClauses);
Open *f3(Open **tete,int nbClauses);

#endif

