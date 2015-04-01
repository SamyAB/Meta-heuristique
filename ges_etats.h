#ifndef GES_ETATS
#define GES_ETATS

void afficherChemin(Entier *tete);
void afficherEtat(char *tab,int nbClauses);
Entier *nouveauChemin(Entier *source,int val);
int compteurNiveau(Entier *tete);
Litteral *init(char *benchmark,int *nbClauses,int *nbLitteraux,Open **etatInit);
void ajouterAOpen(Open **tete,char *etat,int nbClauses);
Open *depiler(Open **tete);
char typeEtat(Open *etat);
char *copieTable(char *source);
Open *genererEtat(Open *etatP,int val,Litteral *tabLitt,int nbLitt);
void libererEntier(Entier **tete);
void liberer(Open **e);

#endif

