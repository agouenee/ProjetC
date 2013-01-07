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
// Calque temporaire (pour la mise à jour du calque courant après suppression)
Layer* tmp = NULL;
// Compteur de calques (pour identifier chaque calque créé)
unsigned int idLayer = 0;
unsigned int cptLayer = 0;

// Image
Image* finalImg = NULL;

// Lut
Lut lutable;

// Initialisation des variables de saisie (variables que l'utilisateur peut modifier dans le programme)
char* fileNameRoot = NULL;
char* fileName = NULL;
float opacity = 1.0; /* par défaut, opaque */
unsigned int mix = 1; /* par défaut, multiplicatif */
int val = 0;

// Initialisation de variables de test
int test = 0;
int view = 0;

// Personnalisation du rendu (IHM)
void menuLayer() {
    writeString(0.84, 0.93, "CALQUES");
    writeString(0.84, 0.1, "calque 0");
    writeString(0.82, 0.06, fileNameRoot);

    int i;
    char layerName[2];
    float y = 0.10;
    for(i = 1; i <= cptLayer; i++) {
        sprintf(layerName, "calque %d", i);
        y += 0.08;
        writeString(0.84, y, layerName);
    }
}

void mainMenu() {
    printf("\n----------------- Menu principal -----------------\n\n");
    printf("[i] Afficher les informations de l'image\n");
    printf("[1] Accéder au menu calque\n");
    printf("[2] Accéder au menu LUT\n");
    printf("[3] Changer de mode de vue\n");
    printf("\n--------------------------------------------------\n\n");
}
void layerMenu() {
    printf("\n------------------- Menu calque ------------------\n\n");
    printf("[a] Ajouter un nouveau calque image\n");
    printf("[b] Modifier le type de melange du calque\n");
    printf("[c] Modifier l'opacite du calque\n");
    printf("[d] Ajouter un calque vide\n");
    printf("[e] Supprimer un calque\n");
    printf("[r] Retour au menu principal\n");
    printf("\n--------------------------------------------------\n\n");
}
void lutMenu() {
    printf("\n-------------------- Menu LUT --------------------\n\n");
    printf("[m] Augmenter la luminosite\n");
    printf("[n] Diminuer la luminosite\n");
    printf("[o] Effet Sépia\n");
    printf("[r] Retour au menu principal\n");
    printf("\n--------------------------------------------------\n\n");
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
    //imgRoot->pixel = imgRoot->source->pixel;
    // Mise à jour du calque courant
    Layer* selected = imgRoot;
    mainMenu();

    // Interruptions clavier (c: caractère saisi; x,y: coordonnées du curseur)
    void kbdFunc(unsigned char c, int x, int y) {
        printf("(%c) ", c);
        switch(c) {
            case 'i': // Exemple d'utilisation des fonctions de la bibliotheque glimagimp
                printf("Information image et IHM\n");
                printInfo();
                mainMenu();
                break;
            case '1' :
                layerMenu();
                printf("(%c) ", c);
                break;
                    case 'a':
                        printf("Ajout d'un nouveau calque image (%d x %d)\n", imgRoot->source->width, imgRoot->source->height);
                        printf("    Saisir le nom du fichier à ouvrir (ex: france.ppm): ");
                        scanf("%s", fileName);
                        sprintf(path, "../images/%s", fileName);
                        // Ajout du calque
                        imgPPM = addImgLayer(path, ++idLayer, 1.0, 1, selected);
                        cptLayer++;
                        // Affichage dans IHM
                        actualiseImage(imgPPM->source->pixel);
                        // Mise à jour du calque courant
                        selected = imgPPM;
                        layerMenu();
                        break;
                    case 'b':
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
                            //selected = modifLayer(selected);
                            // Affichage dans IHM
                            actualiseImage(selected->source->pixel);
                        }
                        else {
                            printf("Impossible de modifier le mélange du calque initial :\nil n'y a aucun calque en dessous !\n");
                        }
                        layerMenu();
                        break;
                    case 'c':
                        printf("Modification de l'opacité du calque\n");
                        if(selected->prev != NULL) {
                            printf("    Opacité actuelle du calque: %f\n", selected->opacity);
                            printf("    Saisir la nouvelle opacité.\n");
                            printf("    Valeur comprise entre 0.0 (transparent) et 1.0 (opaque): ");
                            scanf("%f", &opacity);
                            selected = modifLayerOpacity(selected, opacity);
                            // Modification de l'apparence du calque avec sa nouvelle opacité
                            //selected = modifLayer(selected);
                            // Affichage dans IHM
                            actualiseImage(selected->source->pixel);
                        }
                        else {
                            printf("Impossible de modifier l'opacité du calque initial :\nil n'y a aucun calque en dessous !\n");
                        }
                        layerMenu();
                        break;
                    case 'd':
                        printf("Ajout d'un nouveau calque vide (%d x %d)\n", imgRoot->source->width, imgRoot->source->height);
                        // Ajout du calque
                        empty = addEmptyLayer(++idLayer, imgRoot, selected);
                        cptLayer++;
                        // Affichage dans IHM
                        actualiseImage(empty->source->pixel);
                        // Mise à jour du calque courant
                        selected = empty;
                        layerMenu();
                        break;
                    case 'e':
                        printf("Suppression du calque sélectionné (calque %d)\n", selected->id);
                        tmp = selected->prev;
                        test = suppLayer(selected);
                        if(test == 1) {
                            printf("Calque supprimé\n");
                            cptLayer--;
                            selected = tmp;
                            actualiseImage(selected->source->pixel);
                        }
                        else {
                            printf("Impossible de supprimer ce calque.\n");
                        }
                        layerMenu();
                        break;

            case '2' :
                lutMenu();
                break;
                    case 'm':
                        printf("Augmentation de la luminosite\n");
                        printf("    Entrez une valeur entre 0 et 255 : ");
                        scanf("%d", &val);
                        if(val < 0 || val > 255) {
                            printf("    Erreur : valeur non comprise entre 0 et 255\n");
                            printf("    Augmentation de la luminosite non effectuee.\n\n");
                            lutMenu();
                        }
                        else {
                            initLUT(&lutable);
                            addLum(&lutable, val);
                            //remplissage d'une image avec les nouveaux pixels modifiés
                            setModif(selected, &lutable);
                        }
                        lutMenu();
                        break;
                    case 'n':
                        printf("Diminution de la luminosite\n");
                        printf("    Entrez une valeur entre 0 et 255 : ");
                        scanf("%d", &val);
                        if(val < 0 || val > 255) {
                            printf("    Erreur : valeur non comprise entre 0 et 255\n");
                            printf("    Diminution de la luminosite non effectuee.\n\n");
                            lutMenu();
                        }
                        else {
                            initLUT(&lutable);
                            dimLum(&lutable, val);
                            //remplissage d'une image avec les nouveaux pixels modifiés
                            setModif(selected, &lutable);
                        }
                        lutMenu();
                        break;
                    case 'o' :
                        printf("Effet Sepia\n");
                        sepia(&lutable, selected->source);
                        setModif(selected, &lutable);
                        lutMenu();
                        break;

            case '3':
                // Changer de mode de vue (IHM_1)
                printf("Mode de vue \n");
                if(view == 0) {
                    printf("Image finale \n");
                    finalImg = createFinalImage(imgRoot);
                    actualiseImage(finalImg->pixel);
                    view = 1;
                }
                else {
                    printf("Image source \n");
                    actualiseImage(selected->source->pixel);
                    view = 0;
                }
                break;

            case '4' :
                // Enregistrement image finale (IM_2)
                printf("Enregistrer l'image finale\n");
                finalImg = createFinalImage(imgRoot);
                saveFinalImage(finalImg, "../images/test.ppm");
            case 'r' :
                mainMenu();
                break;
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
                mainMenu();
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
                    actualiseImage(selected->next->source->pixel);
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
                    actualiseImage(selected->prev->source->pixel);
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
    initGLIMAGIMP_IHM(imgRoot->source->width, imgRoot->source->height, imgRoot->source->pixel, imgRoot->source->width + 200, imgRoot->source->height);

	return 0;
}
