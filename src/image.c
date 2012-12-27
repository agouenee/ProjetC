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

#include "image.h"

int openImage(char* path, Image* img) {
    // Ouverture fichier (r: lecture seule)
    FILE* file = fopen(path, "r");
    if(file == NULL) {
        // Erreur ouverture fichier
        return 0;
    }
    // Création d'une structure de type Image
    else {
        // Vérification du type de l'image (P6)
        int type;
        fscanf(file, "P%d\n", &type);
        if(type != 6) {
            return 0;
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
                return 0;
            }
            // Récupération des pixels de l'image
            else {
                fread(img->pixel, sizeof(unsigned char), (img->width)*(img->height)*3, file);
            }
        }
    }

    //fflush(stdin);
    fclose(file);
    return 1;
}
