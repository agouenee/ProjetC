#ifndef historique
#define historique

typedef struct maillonHistorique {
	Calque* calque;
	maillonHistorique* next;
}maillonHistorique;

typedef struct pileHistorique {
	maillonHistorique* first;
	int taille;
}pileHistorique;

#endif