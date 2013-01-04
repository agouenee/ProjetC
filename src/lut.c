/*************************************************/
/*         Katia Moreira & Audrey Guénée         */
/*                Projet C - 2012                */
/*************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "layer.h"
#include "lut.h"
#include "image.h"


// Initialisation de la LUT
void initLUT(Lut* lutable) {
	int i;
	for (i=0; i<256; i++) {
		lutable->tabR[i] = i;
		lutable->tabV[i] = i;
		lutable->tabB[i] = i;
	}
}

//Augmenter la luminosité
void addLum(Lut* lutable, int val) 
{
	int i;
 
 	for(i=0; i<256; i++) {
 		// Tab Rouge
 		// Si valeur actuelle + valeur entree < 0 on affecte la valeur minimale 0
 		if((lutable->tabR[i]+val)<0)
 			lutable->tabR[i] = 0;
 		// Si valeur actuelle + valeur entree > 255 on affecte la valeur maximale 255
 		else if((lutable->tabR[i]+val)>255)
 			lutable->tabR[i] = 255;
 		// Sinon on affecte valeur actuelle + valeur entree
 		else
 			lutable->tabR[i] = lutable->tabR[i]+val;
 			
 		// Tab Vert
 		if((lutable->tabV[i]+val)<0)
 			lutable->tabV[i] = 0;
 		else if((lutable->tabV[i]+val)>255)
 			lutable->tabV[i] = 255;
 		else
 			lutable->tabV[i] = lutable->tabV[i]+val;
 		
 		// Tab Bleu	
 		if((lutable->tabB[i]+val)<0)
 			lutable->tabB[i] = 0;
 		else if((lutable->tabB[i]+val)>255)
 			lutable->tabB[i] = 255;
 		else
   			lutable->tabB[i] = lutable->tabB[i]+val;
	}
}

// Appliquer les modifications à l'image grâce à la LUT
void setModif(Layer* myLayer, Lut* lutable)
{
	int i;
	int length = (myLayer->source->height) * (myLayer->source->width) * 3;
	for(i=0; i<length; i+=3) {
		myLayer->source->pixel[i]=(unsigned char)(lutable->tabR[myLayer->source->pixel[i]]);
		myLayer->source->pixel[i+1]=(unsigned char)(lutable->tabV[myLayer->source->pixel[i+1]]);
		myLayer->source->pixel[i+2]=(unsigned char)(lutable->tabB[myLayer->source->pixel[i+2]]);
	}
}