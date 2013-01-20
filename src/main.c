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
#include "historique.h"

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
Lut* appliedLut = NULL;

/* Historique
pileHistorique* pile = (pileHistorique*)malloc(sizeof(pileHistorique));
pile->first = NULL;
pile->taille = 0;*/

// Initialisation des variables de saisie (variables que l'utilisateur peut modifier dans le programme)
char* fileNameRoot = NULL;
char* fileName = NULL;
float opacity = 1.0; /* par défaut, opaque */
unsigned int mix = 1; /* par défaut, multiplicatif */
int val = 0;

// Initialisation de variables de test
int test = 0;
int view = 0; /* par défaut, mode de vue "image finale" */

// Personnalisation du rendu (IHM)
void menuLayer() {
    writeString(0.823, 0.95, "Mode de vue");
    if(view == 0) {
        writeString(0.818, 0.90, "IMAGE FINALE");
    }
    else {
        writeString(0.818, 0.90, "IMAGE SOURCE");
    }
    writeString(0.84, 0.75, "CALQUES");
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
    printf("[4] Sauvegarder l'image finale\n");
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
    printf("[o] Mettre en niveaux de gris\n");
    printf("[p] Appliquer l'effet sépia\n");
    printf("[q] Augmenter le contraste\n");
    printf("[s] Diminuer le contraste\n");
    printf("[t] Inversion de couleurs\n");
    printf("[u] Suppression de la dernière LUT\n");
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
    // Mise à jour du calque courant
    Layer* selected = imgRoot;
    mainMenu();

    // Interruptions clavier (c: caractère saisi; x,y: coordonnées du curseur)
    void kbdFunc(unsigned char c, int x, int y) {
        printf("(%c) ", c);
        switch(c) {
            case 'i':
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
                        if(mix == 0 || mix == 1) {
                            selected = modifLayerMix(selected, mix);
                            // Modification de l'apparence du calque avec son nouveau mélange
                            selected = modifLayer(selected);
                            // Affichage dans IHM
                            if(view == 0) {
                                actualiseImage(selected->pixel);
                            }
                            else {
                                actualiseImage(selected->source->pixel);
                            }
                        }
                        else {
                            printf("    Erreur : valeur incorrecte\n");
                            printf("    Modification du type de mélange non effectuee.\n\n");
                        }
                        layerMenu();
                        break;
                    case 'c':
                        printf("Modification de l'opacité du calque\n");
                        printf("    Opacité actuelle du calque: %f\n", selected->opacity);
                        printf("    Saisir la nouvelle opacité.\n");
                        printf("    Valeur comprise entre 0.0 (transparent) et 1.0 (opaque): ");
                        scanf("%f", &opacity);
                        if(opacity < 0.0 || opacity > 1.0) {
                            printf("    Erreur : valeur non comprise entre 0.0 et 1.0\n");
                            printf("    Modification de l'opacité non effectuee.\n\n");
                        }
                        else {
                            selected = modifLayerOpacity(selected, opacity);
                            // Modification de l'apparence du calque avec sa nouvelle opacité
                            selected = modifLayer(selected);
                            // Affichage dans IHM
                            if(view == 0) {
                                actualiseImage(selected->pixel);
                            }
                            else {
                                actualiseImage(selected->source->pixel);
                            }   
                        }
                        layerMenu();
                        break;
                    case 'd':
                        printf("Ajout d'un nouveau calque vide (%d x %d)\n", imgRoot->source->width, imgRoot->source->height);
                        // Ajout du calque
                        empty = addEmptyLayer(++idLayer, imgRoot, selected);
                        cptLayer++;
                        // Affichage dans IHM
                        actualiseImage(empty->pixel);
                        // Mise à jour du calque courant
                        selected = empty;
                        layerMenu();
                        break;
                    case 'e':
                        printf("Suppression du calque sélectionné (calque %d)\n", selected->id);
                        if(selected->prev != NULL) {
                            tmp = selected->prev;
                        }
                        else {
                            tmp = selected->next;
                        }
                        test = suppLayer(selected);
                        if(test == 1) {
                            printf("Calque supprimé\n");
                            cptLayer--;
                            selected = tmp;
                            // Affichage dans IHM
                            if(view == 0) {
                                actualiseImage(selected->pixel);
                            }
                            else {
                                actualiseImage(selected->source->pixel);
                            }
                        }
                        else {
                            printf("Impossible de supprimer le dernier calque.\n");
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
                        }
                        else {
                            initLUT(&lutable);
                            addLum(&lutable, val);
                            // Ajout de la LUT au calque
                            appliedLut = addLut(1, &lutable, selected);
                            // Remplissage d'une image avec les nouveaux pixels modifiés
                            setModif(selected);
                            //addToHistory(pile, selected);
                            // Affichage IHM
                            if(view == 0) {
                                actualiseImage(selected->pixel);
                            }
                            else {
                                actualiseImage(selected->source->pixel);
                            }
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
                        }
                        else {
                            initLUT(&lutable);
                            dimLum(&lutable, val);
                            // Ajout de la LUT au calque
                            appliedLut = addLut(2, &lutable, selected);
                            // Remplissage d'une image avec les nouveaux pixels modifiés
                            setModif(selected);
                            // Affichage IHM
                            if(view == 0) {
                                actualiseImage(selected->pixel);
                            }
                            else {
                                actualiseImage(selected->source->pixel);
                            }
                        }
                        lutMenu();
                        break;
                    case 'o' :
                        printf("Effet noir et blanc\n");
                        initLUT(&lutable);
                        // Ajout de la LUT au calque
                        appliedLut = addLut(7, &lutable, selected);
                        // Remplissage d'une image avec les nouveaux pixels modifiés
                        setModif(selected);
                        // Affichage IHM
                        if(view == 0) {
                            actualiseImage(selected->pixel);
                        }
                        else {
                            actualiseImage(selected->source->pixel);
                        }
                        lutMenu();
                        break;
                    case 'p' :
                        printf("Effet sepia\n");
                        int sepiaEffect = sepia(&lutable);
                        if(sepiaEffect == 0) {
                            printf(" Erreur effet sepia non effectue\n");
                        }
                        else {
                            // Ajout de la LUT au calque
                            appliedLut = addLut(3, &lutable, selected);
                            // Remplissage d'une image avec les nouveaux pixels modifiés
                            setModif(selected);
                            // Affichage IHM
                            if(view == 0) {
                                actualiseImage(selected->pixel);
                            }
                            else {
                                actualiseImage(selected->source->pixel);
                            }
                        }
                        lutMenu();
                        break;
                    case 'q' :
                        printf("Augmentation du contraste\n");
                        printf("    Entrez une valeur entre 0 et 255 : ");
                        scanf("%d", &val);
                        int addContrastEffect = addContrast(&lutable, val);
                        if(addContrastEffect == 0) {
                            printf(" Erreur augmentation du contraste non effectue\n");
                        }
                        else if((val<0) || (val>255)) {
                            printf("    Erreur : valeur non comprise entre 0 et 255\n");
                            printf("    Augmentation du contraste non effectue.\n\n");
                        }
                        else {
                            // Ajout de la LUT au calque
                            appliedLut = addLut(4, &lutable, selected);
                            // Remplissage d'une image avec les nouveaux pixels modifiés
                            setModif(selected);
                            // Affichage IHM
                            if(view == 0) {
                                actualiseImage(selected->pixel);
                            }
                            else {
                                actualiseImage(selected->source->pixel);
                            }
                        }
                        lutMenu();
                        break;
                    case 's' :
                        printf("Diminution du contraste\n");
                        printf("    Entrez une valeur entre 0 et 255 : ");
                        scanf("%d", &val);
                        int dimContrastEffect = dimContrast(&lutable, val);
                        if(dimContrastEffect == 0) {
                            printf(" Erreur diminution du contraste non effectuee\n");
                        }
                        else if((val<0) || (val>255)) {
                            printf("    Erreur : valeur non comprise entre 0 et 255\n");
                            printf("    Diminution du contraste non effectuee.\n\n");
                        }
                        else {
                            // Ajout de la LUT au calque
                            appliedLut = addLut(5, &lutable, selected);
                            // Remplissage d'une image avec les nouveaux pixels modifiés
                            setModif(selected);
                            // Affichage IHM
                            if(view == 0) {
                                actualiseImage(selected->pixel);
                            }
                            else {
                                actualiseImage(selected->source->pixel);
                            }
                        }
                        lutMenu();
                        break;
                    case 't' :
                        printf("Inversion des couleurs\n");
                        initLUT(&lutable);
                        invert(&lutable);
                        // Ajout de la LUT au calque
                        appliedLut = addLut(6, &lutable, selected);
                        // Remplissage d'une image avec les nouveaux pixels modifiés
                        setModif(selected);
                        // Affichage IHM
                        if(view == 0) {
                            actualiseImage(selected->pixel);
                        }
                        else {
                             actualiseImage(selected->source->pixel);
                        }
                        lutMenu();
                        break;
                    case 'u' :
                        printf("Suppression de la dernière LUT appliquée\n");
                        // Suppression de la LUT
                        test = suppLUT(selected->appliedLut, selected);
                        if(test == 1) {
                            // Mise à jour du calque (avec une LUT en moins)
                            setModif(selected);
                        }
                        else {
                            printf("Aucune LUT n'est appliquée à ce calque !\n");
                        }
                        // Affichage IHM
                        if(view == 0) {
                            actualiseImage(selected->pixel);
                        }
                        else {
                             actualiseImage(selected->source->pixel);
                        }
                        lutMenu();
                        break;

            case '3':
                // Changer de mode de vue (IHM_1)
                printf("Mode de vue : ");
                if(view == 0) { /* Mode de vue "image finale" (par défaut) */
                    printf("Image source \n");
                    view = 1;
                    actualiseImage(selected->source->pixel);
                }
                else { /* Mode de vue "image source" */
                    printf("Image finale \n");
                    view = 0;
                    actualiseImage(selected->pixel);
                }
                break;

            case '4' :
                // Enregistrement image finale (IM_2)
                printf("Enregistrement de l'image finale\n");
                // Création de l'image finale
                finalImg = createFinalImage(imgRoot);
                printf("Saisir le nom du fichier à enregistrer (fichier.ppm)\n");
                scanf("%s", fileName);
                sprintf(path, "../images/%s", fileName);
                // Sauvegarde de l'image finale
                saveFinalImage(finalImg, path);
            case 'r' :
                mainMenu();
                break;
            case 27:
                printf("escap) Fin du programme\n");
                // Désallocation de la mémoire (IHM_4)
                free(finalImg);
                free(fileNameRoot);
                free(fileName);
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
                    if(view == 0) {
                        actualiseImage(selected->next->pixel);
                    }
                    else {
                        actualiseImage(selected->next->source->pixel);
                    }
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
                    if(view == 0) {
                        actualiseImage(selected->prev->pixel);
                    }
                    else {
                        actualiseImage(selected->prev->source->pixel);
                    }
                    // Mise à jour du calque courant
                    selected = selected->prev;
                    printf("    Calque sélectionné: calque %d (opacité: %f)\n", selected->id, selected->opacity);
                }
                break;
            /*
            case GLUT_KEY_LEFT :
                tmp = (Layer*)malloc(sizeof(layer));
                tmp = goBackHistorique(pile, calqueDepart);
                
                if(tmp != NULL) {
                    if(retourneImage(temp, tabInverseEffet) != 0) {
                        printf("Erreur : invertion tableau \n");
                    }
                    actualiseImage(tabInverseEffet);
                    calqueCourant = temp;
                }
                break;
            */
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
