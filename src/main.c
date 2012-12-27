/*************************************************/
/*         Katia Moreira & Audrey Guénée         */
/*                Projet C - 2012                */
/*************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "outils.h"
#include "interface.h"

int main(void) {
    // Ouverture image
    char* path = (char*) malloc(sizeof(char)*22);
    printf("Saisir le chemin du fichier à ouvrir (ex: ../images/portugal.ppm) :\n");
    scanf("%s", path);

    Image* img = (Image*) malloc(sizeof(Image));
    if(img == NULL) {
        printf("Problème allocation mémoire structure image.\n");
    }
    else {
        int opening = openImage(path, img);
        if(opening == 1) {
            initGLIMAGIMP_IHM(img->width, img->height, img->pixel, img->width, img->height);
        }
        else {
            // Problème mémoire ou format fichier
            printf("Problème ouverture fichier.\n");
        }
    }

    free(img->pixel);
	return 0;
}
