/*************************************************/
/*         Katia Moreira & Audrey Guénée         */
/*                Projet C - 2012                */
/*************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "layer.h"
#include "image.h"
#include "lut.h"


// Initialisation de la LUT
void initLUT(Lut* lutable) {
	int i;
	for (i=0; i<256; i++) {
		lutable->tabR[i] = i;
		lutable->tabV[i] = i;
		lutable->tabB[i] = i;
	}
}
Lut* addLut(int type, Lut* previous) {
	Lut* newLut;

	newLut= (Lut*)malloc(sizeof(Lut));
	newLut->type = type;

	if(previous != NULL) {
		previous->next= newLut;
	}
	newLut->next= NULL;
	
	return newLut;
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
void dimLum(Lut* lutable, int val) 
{
	int i;
 
	for(i=0; i<256; i++) {
		// Tab Rouge
		// Si valeur actuelle - valeur entree < 0 on affecte la valeur minimale 0
		if((lutable->tabR[i]-val)<0)
			lutable->tabR[i] = 0;
		// Si valeur actuelle - valeur entree > 255 on affecte la valeur maximale 255
		else if((lutable->tabR[i]-val)>255)
			lutable->tabR[i] = 255;
		// Sinon on affecte valeur actuelle - valeur entree
		else
			lutable->tabR[i] = lutable->tabR[i]-val;
		
		// Tab Vert
		if((lutable->tabV[i]-val)<0)
			lutable->tabV[i] = 0;
		else if((lutable->tabV[i]-val)>255)
			lutable->tabV[i] = 255;
		else
			lutable->tabV[i] = lutable->tabV[i]-val;
		
		// Tab Bleu
		if((lutable->tabB[i]-val)<0)
			lutable->tabB[i] = 0;
		else if((lutable->tabB[i]-val)>255)
			lutable->tabB[i] = 255;
		else
			lutable->tabB[i] = lutable->tabB[i]-val;
	}
}
void greyScale(Layer* myLayer) {
	int i;
	int length = (myLayer->source->width)*(myLayer->source->height)*3;
	for (i=0; i<length; i+=3) {
		int r = myLayer->pixel[i];
		int v = myLayer->pixel[i+1];
		int b = myLayer->pixel[i+2];
		int grey = (r + v + b) / 3;

		r = v = b = grey;

		if (r>255) 
			r = 255;
		if (v>255) 
			v = 255;
		if (b>255) 
			b = 255;

		myLayer->pixel[i] = r;
		myLayer->pixel[i+1] = v;
		myLayer->pixel[i+2] = b;
	}
}
int sepia(Lut* lutable) {

	int i = 0;
	int valR = 0, valV = 0, valB = 0;
	
	if(lutable == NULL) {
		return 0;
	}
	
	for(i=0; i<256; i++) {
		// Rouge
		valR= i + 80;
		if(valR > 255){
			valR = 255;
		}
		lutable->tabR[i] = valR;

		// Vert
		valV= i + 30;
		if(valV > 255){
			valV = 255;
		}
		lutable->tabV[i] = valV;

		// Bleu
		valB= i - 40;
		if(valB < 0){
			valB = 0;
		}
		lutable->tabB[i] = valB;
	}
	return 1;
}
int addContrast(Lut* lutable, int val) {
	int i = 0;
	int newVal = 0;
	
	if(lutable == NULL) {
		return 0;
	}
	
	for(i=0; i<128; i++) {
		// Rouge
		newVal=lutable->tabR[i] - val;
		if(newVal < 0) {
			newVal = 0;
		}
		lutable->tabR[i] = newVal;

		// Vert
		newVal=lutable->tabV[i] - val;
		if(newVal < 0) {
			newVal = 0;
		}
		lutable->tabV[i] = newVal;

		// Bleau
		newVal=lutable->tabB[i] - val;
		if(newVal < 0) {
			newVal = 0;
		}
		lutable->tabB[i] = newVal;
	}
	for(i=128; i<255; i++) {
		// Rouge
		newVal=lutable->tabR[i] + val;
		if(newVal > 255) {
			newVal = 255;
		}
		lutable->tabR[i] = newVal;

		// Vert
		newVal=lutable->tabV[i] + val;
		if(newVal > 255) {
			newVal = 255;
		}
		lutable->tabV[i] = newVal;

		// Bleau
		newVal=lutable->tabB[i] + val;
		if(newVal > 255) {
			newVal = 255;
		}
		lutable->tabB[i] = newVal;
	}
	return 1;
}
int dimContrast(Lut* lutable, int val) {
	int i = 0;
	int newVal = 0;
	
	if(lutable == NULL) {
		return 0;
	}
	
	for(i=0; i<128; i++) {
		// Rouge
		newVal=lutable->tabR[i] + val;
		if(newVal > 128) {
			newVal = 128;
		}
		lutable->tabR[i] = newVal;

		// Vert
		newVal=lutable->tabV[i] + val;
		if(newVal > 128) {
			newVal = 128;
		}
		lutable->tabV[i] = newVal;

		// Bleau
		newVal=lutable->tabB[i] + val;
		if(newVal > 128) {
			newVal = 128;
		}
		lutable->tabB[i] = newVal;
	}
	for(i=128; i<255; i++) {
		// Rouge
		newVal=lutable->tabR[i] - val;
		if(newVal < 128) {
			newVal = 128;
		}
		lutable->tabR[i] = newVal;

		// Vert
		newVal=lutable->tabV[i] - val;
		if(newVal < 128) {
			newVal = 128;
		}
		lutable->tabV[i] = newVal;

		// Bleau
		newVal=lutable->tabB[i] - val;
		if(newVal < 128) {
			newVal = 128;
		}
		lutable->tabB[i] = newVal;
	}
	return 1;
}
void color(Lut* lutable, int R, int V, int B)
{
	int i;
	for (i=0; i<256; i++) {		
	if((lutable->tabR[i]+R)<0)
			lutable->tabR[i] = 0;
		else if((lutable->tabR[i]+R)>255)
			lutable->tabR[i] = 255;
		else
			lutable->tabR[i] = lutable->tabR[i]+R;
			
		if((lutable->tabV[i]+V)<0)
			lutable->tabV[i] = 0;
		else if((lutable->tabV[i]+V)>255)
			lutable->tabV[i] = 255;
		else
			lutable->tabV[i] = lutable->tabV[i]+V;
			
		if((lutable->tabB[i]+B)<0)
			lutable->tabB[i] = 0;
		else if((lutable->tabB[i]+B)>255)
			lutable->tabB[i] = 255;
		else
			lutable->tabB[i] = lutable->tabB[i]+B;
	}
}

// Appliquer les modifications à l'image grâce à la LUT
void setModif(Layer* myLayer, Lut* lutable)
{
	int i;
	int length = (myLayer->source->height) * (myLayer->source->width) * 3;
	for(i=0; i<length; i+=3) {
		/*myLayer->source->pixel[i]=(unsigned char)(lutable->tabR[myLayer->source->pixel[i]]);
		myLayer->source->pixel[i+1]=(unsigned char)(lutable->tabV[myLayer->source->pixel[i+1]]);
		myLayer->source->pixel[i+2]=(unsigned char)(lutable->tabB[myLayer->source->pixel[i+2]]);*/

		myLayer->pixel[i]=(unsigned char)(lutable->tabR[myLayer->pixel[i]]);
		myLayer->pixel[i+1]=(unsigned char)(lutable->tabV[myLayer->pixel[i+1]]);
		myLayer->pixel[i+2]=(unsigned char)(lutable->tabB[myLayer->pixel[i+2]]);
	}
}