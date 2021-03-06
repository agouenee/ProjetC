/*************************************************/
/*         Katia Moreira & Audrey Guénée         */
/*                Projet C - 2012                */
/*************************************************/

// Utilisation d'image couleur au format .ppm au de type P6 (binaire)
// Chaque niveau de couleur R, V, B est codé sur 8 bits (valeurs comprises entre 0 et 255)

/* AUTOPSIE D'UN FICHIER PPM BINAIRE *************************
P6
# Commentaires
largeur
hauteur
valeur maximale pour un niveau de couleur (généralement 255)
Pixels de l'image
*************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "struct_proto.h"

// Chargement et ouverture de l'image (IM_1)
Image* openImage(char* path) {
    // Ouverture fichier (r: lecture seule)
    FILE* file = fopen(path, "r");
    if(file == NULL) {
        // Erreur ouverture fichier
        return NULL;
    }
    // Création d'une structure de type Image
    else {
        // Vérification du type de l'image (P6)
        int type;
        fscanf(file, "P%d\n", &type);
        if(type != 6) {
            return NULL;
        }
        else {
            Image* img = (Image*) malloc(sizeof(Image));
            if(img == NULL) {
                // Problème allocation mémoire structure image
                return NULL;
            }
            else {
                // Récupération du type de l'image
                img->type = type;

                // Gestion des commentaires
                char header[70];
                header[0] = '#';
                while(header[0] == '#') {
                    fgets(header, 70, file);
                }
                // Ré-ajustement de la position courante dans le fichier juste après les lignes de commentaires
                fseek(file, -4, SEEK_CUR);

                // Récupération des dimensions de l'image (width, height)
                fscanf(file, "%d %d\n", &(img->width), &(img->height));

                // Récupération de la valeur maximale utilisée pour coder une couleur (ex: 255)
                fscanf(file, "%d\n", &(img->max));

                // Allocation du tableau de pixels
                img->pixel = (unsigned char*) malloc((img->width)*(img->height)*3*sizeof(unsigned char));
                if(img->pixel == NULL) {
                    // Erreur allocation mémoire tableau de pixels
                    return NULL;
                }
                // Récupération des pixels de l'image
                else {
                    fread(img->pixel, sizeof(unsigned char), (img->width)*(img->height)*3, file);
                }
            }
            fclose(file);
            return img;
        }
    }  
}

// Création de l'image finale
Image* createFinalImage(Layer* l) {
    Image* finalImg = (Image*) malloc(sizeof(Image));
    if(finalImg == NULL) {
        // Problème allocation mémoire structure image
        return NULL;
    }
    else {
        finalImg->type = '6';
        finalImg->width = l->source->width;
        finalImg->height = l->source->height;
        finalImg->max = l->source->max;
        finalImg->pixel = (unsigned char*) malloc((finalImg->width)*(finalImg->height)*3*sizeof(unsigned char));
        if(finalImg->pixel == NULL) {
            // Erreur allocation mémoire tableau de pixels
            return NULL;
        }
        else {
            // Initialisation du tableau de pixels de l'image finale avec les valeurs du tableau du calque initial (image de départ)
            int i;
            for(i = 0; i < (finalImg->width)*(finalImg->height)*3; i++) {
                finalImg->pixel[i] = l->pixel[i];
            }

            Layer* selected = (Layer*) malloc(sizeof(Layer));
            if(selected == NULL) {
                // Problème allocation mémoire structure calque
                return NULL;
            }
            else {
                selected = l;
                // Positionnement sur le dernier calque de la pile
                while(selected->next != NULL) {
                    selected = selected->next;
                }
                // Remplissage de l'image finale avec les pixels du dernier calque
                int j;
                for(j = 0; j < (finalImg->width)*(finalImg->height)*3; j++) {
                    finalImg->pixel[j] = selected->pixel[j];
                }
            }  
        }
    }
    return finalImg;
}

// Sauvegarde de l'image finale
void saveFinalImage(Image* img, char* fileName) {
    // Création et ouverture en écriture du fichier final (vide)
    FILE* finalImgFile = fopen(fileName, "w");
    if(finalImgFile == NULL) {
        // Erreur ouverture fichier
        return;
    }
    // Ecriture des données de l'image
    else {
        // Ecriture de l'en-tête (type, commentaire, dimensions, valeur max)
        fprintf(finalImgFile, "P6\n# Image Imagimp par Katia et Audrey\n%d %d\n%d\n", img->width, img->height, img->max);
        // Ecriture des pixels
        fwrite(img->pixel, sizeof(unsigned char), (img->height)*(img->width)*3, finalImgFile);
    }
    fflush(finalImgFile);
    fclose(finalImgFile);
}
