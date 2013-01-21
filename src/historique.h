#ifndef history
#define history

typedef struct maillonHistorique {
	struct Layer* myLayer;
	struct maillonHistorique* next;
	int code;
}maillonHistorique;

/*
	codes
	[1] - Ajout de LUT
	[2] - Ajout de calque
*/

typedef struct pileHistorique {
	maillonHistorique* first;
	int taille;
}pileHistorique;

void initHistory(pileHistorique* pile);
int addToHistory(pileHistorique *pile, Layer* selected, int code);
maillonHistorique* goBackHistorique(pileHistorique* pile, Layer* first);

#endif