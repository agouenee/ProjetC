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
void greyScale(Image* img)
{
	int i;
	int length = (img->width)*(img->height) *3;
	for (i=0; i<length; i+=3) {
		int r = img->pixel[i];
		int v = img->pixel[i+1];
		int b = img->pixel[i+2];
		int grey = (r + v + b) / 3;

		r = v = b = grey;

		if (r>255) 
			r = 255;
		if (v>255) 
			v = 255;
		if (b>255) 
			b = 255;

		img->pixel[i] = r;
		img->pixel[i+1]= v;
		img->pixel[i+2] = b;
	}
}
void sepia (Lut* lutable, Image* img)
{
	int i;
	int length = (img->width)*(img->height) *3;
	for (i=0; i<length; i+=3) {
		int r = img->pixel[i];
		int rf = r;
		int v = img->pixel[i+1];
		int vf = v;
		int b = img->pixel[i+2];
		int bf = b;

		//int grey = (r + v + b) / 3;
		//r = v = b = grey;

		rf = (r * 0.393 + v * 0.769 + b * 0.189);
		vf = (r * 0.349 + v * 0.686 + b * 0.168);
		bf = (r * 0.272 + v * 0.534 + b * 0.131);

		if (rf>255) 
			rf = 255;
		if (vf>255) 
			vf = 255;
		if (bf>255) 
			bf = 255;

		img->pixel[i] = rf;
		img->pixel[i+1]= vf;
		img->pixel[i+2] = bf;
	}
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

		myLayer->pixel[i]=(unsigned char)(lutable->tabR[myLayer->source->pixel[i]]);
		myLayer->pixel[i+1]=(unsigned char)(lutable->tabV[myLayer->source->pixel[i+1]]);
		myLayer->pixel[i+2]=(unsigned char)(lutable->tabB[myLayer->source->pixel[i+2]]);
	}
}