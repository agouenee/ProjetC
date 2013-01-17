#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include "historique.h"

void initHistory(pileHistorique* pile)
{
	pile->first = NULL;
	pile->taille = 0;
}

int addToHistory(pileHistorique* pile, Layer* myLayer)
{
	int i;
	maillonHistorique* newMaillon;

	Image* newImage = (Image*)malloc(sizeof(Image));
	if(newImage == NULL) {
		return 0;
	}
	newImage->height = myLayer->source->height;
	newImage->width = myLayer->source->width;

	int length = newImage->height * newImage->width * 3;
	newImage->pixel = (unsigned char*)malloc(length*sizeof(unsigned char));
	
	for(i=0; i<length; i++) {
		newImage->pixel[i] = myLayer->source->pixel[i];
	}
}