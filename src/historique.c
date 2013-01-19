#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include "layer.h"
#include "historique.h"

void initHistory(pileHistorique* pile)
{
	pile->first = NULL;
	pile->taille = 0;
}

int addToHistory(pileHistorique* pile, Layer* myLayer)
{
	int i;

	maillonHistorique* m;

	Image* newImage = (Image*)malloc(sizeof(Image));
	if(newImage == NULL) {
		printf("Erreur allocation nouvelle image\n");
		return 0;
	}
	newImage->height = myLayer->source->height;
	newImage->width = myLayer->source->width;

	int length = newImage->height * newImage->width * 3;
	newImage->pixel = (unsigned char*)malloc(length*sizeof(unsigned char));
	if(newImage->pixel == NULL) {
		printf("Erreur allocation du tableau de pixels de l'image\n");
		return 0;
	}
	
	for(i=0; i<length; i++) {
		newImage->pixel[i] = myLayer->source->pixel[i];
	}

	Layer* newLayer = (Layer*)malloc(sizeof(Layer));
	if(newLayer == NULL) {
		printf("Erreur allocation nouveau calque\n");
		return 0;
	}
	newLayer->source =  (Image*)malloc(sizeof(Image));
	if(newLayer->source == NULL) {
		printf("Erreur allocation nouvelle image \n");
		return 0;
	}
	newLayer->source->pixel = (unsigned char*)malloc(sizeof(unsigned char));
	newLayer->source->pixel = newImage->pixel;
	newLayer->source->width = newImage->width;
	newLayer->source->height = newImage->height;

	newLayer->opacity = myLayer->opacity;
	newLayer->mix = myLayer->mix;
	newLayer->id = myLayer->id;
	
	newLayer->prev = myLayer->prev;
	newLayer->next = myLayer->next;


	// Ajouter le maillon à la pile
	m = (maillonHistorique*)malloc(sizeof(maillonHistorique));
	m->myLayer = (Layer*)malloc(sizeof(Layer));
	
	m->myLayer = newLayer;
	m->next = pile->first;
	pile->first = m;
	pile->taille++;
	
	free(newImage);
	return 1;
}