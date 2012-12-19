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
************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Image {
    unsigned int type;
    unsigned int height;
    unsigned int width;
    unsigned int max;
    unsigned char* pixel;
} Image;

//!\\ GESTION DES COMMENTAIRES # //!\\
void suppComm() {
    // fgets
    // fputs
}

int openImage(char* path, Image* img) {
    // Ouverture fichier (r: lecture seule)
    FILE* file = fopen(path, "r");
    if(file == NULL) {
        // ERREUR OUVERTURE FICHIER
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

            //!\\ GESTION DES COMMENTAIRES # //!\\

            // Récupération des dimensions de l'image (width, height)
            fscanf(file, "%d %d\n", &(img->width), &(img->height));

            // Récupération de la valeur maximale utilisée pour coder une couleur (ex: 255)
            fscanf(file, "%d\n", &(img->max));

            // Allocation du tableau de pixels
            img->pixel = (unsigned char*) malloc((img->width)*(img->height)*3*sizeof(unsigned char));
            if(img->pixel == NULL) {
                // ERREUR ALLOCATION MEMOIRE TABLEAU DE PIXEL
                return 0;
            }
            // Récupération des pixels de l'image
            else {
                fread(img->pixel, sizeof(unsigned char), (img->width)*(img->height)*3, file);
            }
        }
    }
    return 1;
}

void main() {
    char* path = "../images/france.ppm";
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
        }
        else {
            // Problème mémoire ou format fichier
            printf("Problème ouverture fichier.\n");
        }
    }
}
