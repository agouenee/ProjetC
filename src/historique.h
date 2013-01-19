#ifndef history
#define history

typedef struct maillonHistorique {
	struct Layer* myLayer;
	struct maillonHistorique* next;
}maillonHistorique;

typedef struct pileHistorique {
	maillonHistorique* first;
	int taille;
}pileHistorique;

void initHistory(pileHistorique* pile);
int addToHistory(pileHistorique* pile, Layer* myLayer);

#endif