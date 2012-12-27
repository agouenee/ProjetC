#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "outils.h"
#include "interface.h"

int main(void) {
	char* path = "../images/portugal.ppm";
    Image* img = (Image*) malloc(sizeof(Image));
    if(img == NULL) {
        printf("Problème allocation mémoire structure image.\n");
    }
    else {
        int opening = openImage(path, img);
        if(opening == 1) {
            printf("type: %d\n", img->type);
            printf("width: %d    height: %d\n", img->width, img->height);
            printf("max: %d\n", img->max);

            initGLIMAGIMP_IHM(img->width, img->height, img->pixel, img->width, img->height);
        }
        else {
            // Problème mémoire ou format fichier
            printf("Problème ouverture fichier.\n");
        }
    }

	return 0;
}
