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
// Compteur de calques (pour identifier chaque calque créé)
unsigned int idLayer = 0;

Layer* tmp = NULL;

// Initialisation des variables de saisie (variables que l'utilisateur peut modifier dans le programme)
char* fileNameRoot = NULL;
char* fileName = NULL;
float opacity = 1.0; /* par défaut, opaque */
unsigned int mix = 1; /* par défaut, multiplicatif */

// Personnalisation du rendu (IHM)
void menuLayer() {
    writeString(0.84, 0.93, "CALQUES");
    writeString(0.84, 0.1, "calque 0");
    writeString(0.82, 0.06, fileNameRoot);

    int i;
    char layerName[2];
    float y = 0.10;
    for(i = 1; i <= idLayer; i++) {
        sprintf(layerName, "calque %d", i);
        y += 0.08;
        writeString(0.84, y, layerName);
    }
}


int main(void) {
    printf("\n---------------------------- IMAGIMP 2012 ----------------------------\n\n");
    // Chargement et ouverture de l'image (IM_1)
    fileNameRoot = (char*) malloc(sizeof(char)*22);
    fileName = (char*) malloc(sizeof(char)*22);
    char path[100];
    printf("Saisir le nom du fichier à ouvrir (ex: portugal.ppm): ");
    scanf("%s", fileNameRoot);
    sprintf(path, "../images/%s", fileNameRoot);
    // Création du calque de départ avec l'image PPM ouverte (calque 0)
    Layer* imgRoot = addImgLayer(path, idLayer, opacity, mix, NULL);
    imgRoot->pixel = imgRoot->source->pixel;
    // Mise à jour du calque courant
    Layer* selected = imgRoot;

    // Interruptions clavier (c: caractère saisi; x,y: coordonnées du curseur)
    void kbdFunc(unsigned char c, int x, int y) {
        printf("(%c) ", c);
        switch(c) {
            case 'c':
                printf("Ajout d'un nouveau calque image (%d x %d)\n", imgRoot->source->width, imgRoot->source->height);
                printf("    Saisir le nom du fichier à ouvrir (ex: france.ppm): ");
                scanf("%s", fileName);
                sprintf(path, "../images/%s", fileName);
                // Ajout du calque
                imgPPM = addImgLayer(path, ++idLayer, opacity, mix, selected);
                // Affichage dans IHM
                actualiseImage(imgPPM->pixel);
                // Mise à jour du calque courant
                selected = imgPPM;
                break;
            case 'i': // Exemple d'utilisation des fonctions de la bibliotheque glimagimp
                printf("Information image et IHM\n");
                printInfo();
                break;
            case 'm':
                printf("Modification du type de mélange du calque\n");
                if(selected->prev != NULL) {
                    printf("    Mélange actuel du calque: ");
                    if(selected->mix == 1) {
                        printf("(1) multiplicatif\n");
                    }
                    else {
                        printf("(0) additif\n");
                    }
                    printf("    Saisir le nouveau mélange.\n");
                    printf("    0 (additif) ou 1 (multiplicatif): ");
                    scanf("%d", &mix);
                    selected = modifLayerMix(selected, mix);
                    // Modification de l'apparence du calque avec son nouveau mélange
                    selected = modifLayer(selected);
                    // Affichage dans IHM
                    actualiseImage(selected->pixel);
                }
                else {
                    printf("Impossible de modifier le mélange du calque initial :\nil n'y a aucun calque en dessous !\n");
                }
                break;
            case 'n':
                printf("Ajout d'un nouveau calque vide (%d x %d)\n", imgRoot->source->width, imgRoot->source->height);
                // Ajout du calque
                empty = addEmptyLayer(++idLayer, imgRoot, selected);
                // Affichage dans IHM
                actualiseImage(empty->pixel);
                // Mise à jour du calque courant
                selected = empty;
                break;
            case 'o':
                printf("Modification de l'opacité du calque\n");
                if(selected->prev != NULL) {
                    printf("    Opacité actuelle du calque: %f\n", selected->opacity);
                    printf("    Saisir la nouvelle opacité.\n");
                    printf("    Valeur comprise entre 0.0 (transparent) et 1.0 (opaque): ");
                    scanf("%f", &opacity);
                    selected = modifLayerOpacity(selected, opacity);
                    // Modification de l'apparence du calque avec sa nouvelle opacité
                    selected = modifLayer(selected);
                    // Affichage dans IHM
                    actualiseImage(selected->pixel);
                }
                else {
                    printf("Impossible de modifier l'opacité du calque initial :\nil n'y a aucun calque en dessous !\n");
                }
                break;
            /*case 'x':
                printf("Suppression du calque sélectionné (calque %d)\n", selected->id);
                tmp = suppLayer(selected, selected->prev);
                selected = tmp;
                break;*/
            case 27:
                printf("escap) Fin du programme\n");
                // Désallocation de la mémoire (IHM_4)
                free(imgRoot);
                free(imgPPM);
                free(empty);
                // Sortie du programme
                exit(0);
                break;
            default:
                printf("Touche non fonctionnelle\n");
        }
    }

    // Interruptions clavier spéciales (c: caractère saisi; x,y: coordonnées du curseur)
    void kbdSpFunc(int c, int x, int y) {
        switch(c) {
            // Navigation entre les calques (CAL_2)
            case GLUT_KEY_UP:
                if(selected->next == NULL) {
                    printf("    Calque sélectionné: calque %d (opacité: %f)\n", selected->id, selected->opacity);
                    break;
                }
                else if(selected->next != NULL) {
                    // Affichage dans IHM
                    actualiseImage(selected->next->pixel);
                    // Mise à jour du calque courant
                    selected = selected->next;
                    printf("    Calque sélectionné: calque %d (opacité: %f)\n", selected->id, selected->opacity);
                }
                break;
            case GLUT_KEY_DOWN:
                if(selected->prev == NULL) {
                    printf("    Calque sélectionné: calque %d (opacité: %f)\n", selected->id, selected->opacity);
                    break;
                }
                else if(selected->prev != NULL) {
                    // Affichage dans IHM
                    actualiseImage(selected->prev->pixel);
                    // Mise à jour du calque courant
                    selected = selected->prev;
                    printf("    Calque sélectionné: calque %d (opacité: %f)\n", selected->id, selected->opacity);
                }
                break;
            default:
                printf("Touche spéciale non fonctionnelle\n");
        }
    }

    // Loading IHM
    //fixeFonctionClicSouris(clickMouse);
    fixeFonctionClavier(kbdFunc);
    fixeFonctionClavierSpecial(kbdSpFunc);
    fixeFonctionDessin(menuLayer);

    // Affichage de l'image PPM dans l'IHM
    initGLIMAGIMP_IHM(imgRoot->source->width, imgRoot->source->height, imgRoot->pixel, imgRoot->source->width + 200, imgRoot->source->height);

	return 0;
}
