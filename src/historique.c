#include <stdlib.h>
#include <stdio.h>
#include "struct_proto.h"

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

	// Ajout du maillon à la pile
	m->next = pile->first;
	m->myLayer = selected;
	m->code = code;

	// Le maillon devient mon premier élément
	pile->first=m;
	// Augmentation de la taille de la pile
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

	// On doit enlever le premier maillon de la pile
	maillonHistorique* returnMaillon;
	returnMaillon = pile->first;

	tmp = first;
	while(returnMaillon->myLayer->id != tmp->id && tmp->next != NULL) {
		tmp = tmp->next;
	}

	// Code application de LUT --> on la supprime
	if(pile->first->code == 1) {
		test = suppLUT(tmp->appliedLut, tmp);
		if(test == 1) {
			// Mise à jour du calque (avec une LUT en moins)
			setModif(tmp);
		}
	}
	// Code ajout de calque --> on le supprime
	else if(pile->first->code == 2) {
		test = suppLayer(tmp);
		
	}
	// Code modification du type de mélange --> on applique l'autre melange
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
	// On depile notre element
	pile->first = returnMaillon->next;
	returnMaillon->next = NULL;
	pile->taille--;
	
	return returnMaillon;
}
