/*************************************************/
/*         Katia Moreira & Audrey Guénée         */
/*                Projet C - 2012                */
/*************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "layer.h"

#include "outils.h"
#include "interface.h"

int main(void) {
    // Chargement et ouverture de l'image (IM_1)
    char* fileName = (char*) malloc(sizeof(char)*22);
    char path[100];
    printf("Saisir le nom du fichier à ouvrir (ex: portugal.ppm) :\n");
    scanf("%s", fileName);
    sprintf(path, "../images/%s", fileName);
    Image* img = openImage(path);


    // Création d'un calque vide (CAL_1)
    Layer* l = addEmptyLayer(img);


    // Affichage de l'image PPM dans l'IHM
    initGLIMAGIMP_IHM(img->width, img->height, img->pixel, img->width + 200, img->height);
    // Affichage du calque vide dans l'IHM
    // initGLIMAGIMP_IHM(l->source->width, l->source->height, l->source->pixel, l->source->width + 200, l->source->height);

    free(img->pixel);
	return 0;
}
