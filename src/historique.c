#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include "lut.h"
#include "layer.h"
#include "historique.h"

void initHistory(pileHistorique* pile)
{
	pile->first = NULL;
	pile->taille = 0;
}

int addToHistory(pileHistorique *pile, Layer* selected, int code) {

	maillonHistorique* m;
	m = (maillonHistorique*)malloc(sizeof(maillonHistorique));
	if(m == NULL) {
		printf("Probleme allocation nouveau maillon\n");
		return 0;
	}

	m->next = pile->first;
	m->myLayer = selected;
	m->code = code;

	pile->first=m;
	pile->taille++;

	return 1;
}

maillonHistorique* goBackHistorique(pileHistorique* pile, Layer* first)
{
	Layer* tmp = (Layer*)malloc(sizeof(Layer));
	int test = 0;
	
	// Si la taille de la pile est à 0 on ne peut pas retourner en arrière
	if (pile->taille == 0) {
		printf("L'historique est vide\n");
		return NULL;
	}

	maillonHistorique* returnMaillon;
	returnMaillon = pile->first;

	tmp = first;
	while(returnMaillon->myLayer->id != tmp->id && tmp->next != NULL) {
		tmp = tmp->next;
	}

	if(pile->first->code == 1) {
		test = suppLUT(tmp->appliedLut, tmp);
		if(test == 1) {
			// Mise à jour du calque (avec une LUT en moins)
			setModif(tmp);
		}
	}
	else if(pile->first->code == 2) {
		test = suppLayer(tmp);
		
	}
	else if (pile->first->code == 3) {
		if(tmp->mix == 0) {
			tmp = modifLayerMix(tmp, 1);
			tmp = modifLayer(tmp);
		}
		else {
			tmp = modifLayerMix(tmp, 0);
			tmp = modifLayer(tmp);
		}
	}
	returnMaillon->next = NULL;
	pile->first = returnMaillon->next;
	pile->taille--;
	return returnMaillon;
}