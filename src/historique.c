#include <stdlib.h>
#include <stdio.h>
#include "historique.h"

void initHistory(pileHistorique* pile)
{
	pile->first = NULL;
	pile->taille = 0;
}

void addToHistory(pileHistorique* pile, Layer* myLayer)
{
	int i;
	maillonHistorique* newMaillon;
}