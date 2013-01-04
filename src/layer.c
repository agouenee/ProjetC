/*************************************************/
/*         Katia Moreira & Audrey Guénée         */
/*                Projet C - 2012                */
/*************************************************/

// Calques de mêmes dimensions que l'image PPM source ouverte
// S'insèrent toujours en fin de liste ???
// Calque vide = image source totalement blanche, opacité nulle, mélange multiplicatif

/* CARACTERISTIQUES **************
- image source (permet de garder une copie en mémoire du tableau de pixels original)
- calques précédent et suivant
- opacité 
- type de mélange (0: additif; 1: multiplicatif)
- liste de LUT
- tableau de pixel (reprend les valeurs des pixels de l'image source mais est modifié selon l'opacité et le type de mélange du calque)
*********************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "layer.h"

// Ajout d'un calque image
Layer* addImgLayer(char* path, unsigned int id, float opacity, unsigned int mix, Layer* selected) {
    Image* img = openImage(path);
    Layer* l = (Layer*) malloc(sizeof(Layer));
    if(img == NULL && l == NULL) {
        // Problème allocation mémoire structure
        return NULL;
    }
    else {
        l->id = id;
        l->source = img;
        l->opacity = opacity;
        l->mix = mix;

        if(selected == NULL) {
            l->prev = NULL;
            l->next = NULL;
        }
        else if(selected->next != NULL) {
            l->prev = selected;
            l->next = selected->next;

            selected->next->prev = l;
            selected->next = l;
        }
        else if(selected->next == NULL) {
            l->prev = selected;
            l->next = NULL;

            selected->next = l;
        }

        l->pixel = (unsigned char*) malloc((l->source->width)*(l->source->height)*3*sizeof(unsigned char));
        if(l->pixel == NULL) {
            // Problème allocation mémoire tableau pixels
            return NULL;
        }
        else {
            l = modifLayer(l);
        }
    }

    return l;
}

// Ajout d'un calque vide (CAL_1)
Layer* addEmptyLayer(unsigned int id, Layer* imgRoot, Layer* selected) {
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
            white->width = imgRoot->source->width;
            white->height = imgRoot->source->height;
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

                l->id = id;
                l->source = white;
                l->opacity = 0.0;
                l->mix = 1;

                if(selected == NULL) {
                    l->prev = NULL;
                    l->next = NULL;
                }
                else if(selected->next != NULL) {
                    l->prev = selected;
                    l->next = selected->next;

                    selected->next->prev = l;
                    selected->next = l;
                }
                else if(selected->next == NULL) {
                    l->prev = selected;
                    l->next = NULL;

                    selected->next = l;
                }

                l->pixel = (unsigned char*) malloc((l->source->width)*(l->source->height)*3*sizeof(unsigned char));
                if(l->pixel == NULL) {
                    // Problème allocation mémoire tableau pixels
                    return NULL;
                }
                else {
                    l = modifLayer(l);
                }

            }
        }
    }

    return l;
}

// Modification de l'opacité d'un calque (CAL_3)
Layer* modifLayerOpacity(Layer* selected, float opacity) {
    if(selected->prev != NULL) {
        if(opacity >= 0.0 && opacity <= 1.0) {
            selected->opacity = opacity;
        }
    }
    return selected;
}

// Modification du type de mélange (CAL_4)
Layer* modifLayerMix(Layer* selected, unsigned int mix) {
    if(selected->prev != NULL) {
        if(mix == 0 || mix == 1) {
            selected->mix = mix;
        }
    }
    return selected;
}

// Modification de l'apparence du calque après modification de l'opacité et/ou du type mélange
Layer* modifLayer(Layer* selected) {
    if(selected->prev != NULL) {
        int i;
        // Si le mélange est multiplicatif
        if(selected->mix == 1) {
            for(i = 0; i < selected->source->width*selected->source->height*3; i++) {
                selected->pixel[i] = (1 - selected->opacity)*selected->prev->pixel[i] + (selected->opacity*selected->source->pixel[i]);
            }
        }
        // Si le mélange est additif
        else if(selected->mix == 0) {
            for(i = 0; i < selected->source->width*selected->source->height*3; i++) {
                selected->pixel[i] = selected->prev->pixel[i] + (selected->opacity*selected->source->pixel[i]);
            }
        }
    }
    return selected;
}

// Supression d'un calque (CAL_5)
int suppLayer(Layer* selected) {
    // S'il n'y a pas de calque précédent
    if(selected->prev == NULL) {
        // S'il n'y a pas de calque suivant, le calque sélectionné est le calque initial, tout seul
        if(selected->next == NULL) {
            // Impossible de supprimer le calque sélectionné s'il ne reste plus que lui
            return 0;
        }
        // S'il y a un calque suivant
        else {
            selected->next->prev = NULL;
            selected->next = NULL;
            free(selected);
            return 1;
        }
    }
    // S'il y a un calque précédent
    else {
        // S'il n'y a pas de calque suivant
        if(selected->next == NULL) {
            selected->prev->next = NULL;
            selected->prev = NULL;
            free(selected);
            return 1;
        }
        // S'il y a un calque suivant
        else {
            selected->prev->next = selected->next;
            selected->next->prev = selected->prev;
            selected->next = NULL;
            selected->prev = NULL;
            free(selected);
            return 1;
        }
    }
}
