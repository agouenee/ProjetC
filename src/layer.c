/*************************************************/
/*         Katia Moreira & Audrey Guénée         */
/*                Projet C - 2012                */
/*************************************************/

// Calques de mêmes dimensions que l'image PPM source ouverte
// S'insèrent toujours en fin de liste
// Calque vide = image source totalement blanche, opacité nulle, mélange multiplicatif

/* CARACTERISTIQUES **************
- image source 
- calques précédent et suivant
- opacité 
- type de mélange
- liste de LUT
*********************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "layer.h"

// Ajout d'un calque vide (CAL_1)
Layer* addEmptyLayer(Image* img) {
	Layer* l = (Layer*) malloc(sizeof(Layer));
    if(l == NULL) {
    	// Problème allocation mémoire structure calque
        return NULL;
    }
    else {
        // Création d'une image blanche de mêmes dimensions que celle chargée en mémoire
        Image* white = (Image*) malloc(sizeof(Image));
        if(white == NULL) {
        	// Problème allocation mémoire structure image
        	return NULL;
        }
        else {
            // white->type ???
            white->width = img->width;
            white->height = img->height;
            white->max = 255;
            white->pixel = (unsigned char*) malloc((white->width)*(white->height)*3*sizeof(unsigned char));
            if(white->pixel == NULL) {
            	// Problème allocation mémoire tableau pixels
                return NULL;
            }
            else {
                int i;
                for(i = 0; i < (white->width)*(white->height)*3; i++) {
                    white->pixel[i] = 255;
                }

                l->source = white;
                l->prev = NULL;
                l->next = NULL;
                l->opacity = 0.0;
                l->add = 0;
                l->multi = 1;
            }
        }
    }

    return l;
}

    