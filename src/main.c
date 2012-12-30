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

// Initialisation des calques
// Image/calque de base (celle que l'on ouvre en premier)
Layer* imgRoot = NULL;
// Calque image (autre image PPM que l'on peut ouvrir)
Layer* imgPPM = NULL;
// Calque vide (calque blanc)
Layer* empty = NULL;
// Calque courant (sélectionné)
Layer* selected = NULL;

int main(void) {
    printf("\n-------------------- IMAGIMP 2012 --------------------\n\n");
    // Chargement et ouverture de l'image (IM_1)
    char* fileName = (char*) malloc(sizeof(char)*22);
    char path[100];
    printf("Saisir le nom du fichier à ouvrir (ex: portugal.ppm) :\n");
    scanf("%s", fileName);
    sprintf(path, "../images/%s", fileName);
    // Création du calque de départ avec l'image PPM ouverte (arrière plan)
    Layer* imgRoot = addImgLayer(path, 1, 0, 0, NULL);
    // Mise à jour calque courant
    Layer* selected = imgRoot;

    // Interruptions clavier (c: caractère saisi; x,y: coordonnées du curseur)
    void kbdFunc(unsigned char c, int x, int y) {
        printf("(%c) ", c);
        switch(c) {
            case 'c':
                printf("Ajout d'un nouveau calque image (%d x %d)\n", imgRoot->source->width, imgRoot->source->height);
                printf("Saisir le nom du fichier à ouvrir (ex: france.ppm) :\n");
                scanf("%s", fileName);
                sprintf(path, "../images/%s", fileName);
                // Ajout du calque
                imgPPM = addImgLayer(path, 1, 0, 0, selected);
                // Affichage dans IHM
                actualiseImage(imgPPM->source->pixel);
                // Mise à jour du calque courant
                selected = imgPPM;
                break;
            case 'i': // Exemple d'utilisation des fonctions de la bibliotheque glimagimp
                printf("Information image et IHM\n");
                printInfo();
                break;
            case 'n':
                printf("Ajout d'un nouveau calque vide (%d x %d)\n", imgRoot->source->width, imgRoot->source->height);
                // Ajout du calque
                empty = addEmptyLayer(imgRoot, selected);
                // Affichage dans IHM
                actualiseImage(empty->source->pixel);
                // Mise à jour du calque courant
                selected = empty;
                break;
            case 27: 
                /* Touche escap */
                printf("Fin du programme\n");
                exit(0);
                break;
            default:
                printf("Touche non fonctionnelle\n");
        }
    }

    // Loading IHM
    //fixeFonctionClicSouris(clickMouse);
    fixeFonctionClavier(kbdFunc);
    //fixeFonctionClavierSpecial(kbdSpFunc);
    //fixeFonctionDessin(mondessin);

    // Affichage de l'image PPM dans l'IHM
    initGLIMAGIMP_IHM(imgRoot->source->width, imgRoot->source->height, imgRoot->source->pixel, imgRoot->source->width + 200, imgRoot->source->height);

    free(imgRoot->source->pixel);
	return 0;
}
