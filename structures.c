typedef struct Image {
    unsigned int type;
    unsigned int height;
    unsigned int width;
    unsigned int max;
    unsigned char* pixel;
} Image;

typedef struct Layer {
    unsigned int id;
    Image* source;
    struct Layer* prev;
    struct Layer* next;
    float opacity;
    char add;
    char multi;
    // lut* lut;
} Layer;

typedef struct lut {
	lut* next;
	unsigned char tabR[256];
	unsigned char tabV[256];
	unsigned char tabB[256];
}lut;

typedef struct maillonHistorique {
	Calque* calque;
	maillonHistorique* next;
}maillonHistorique;
typedef struct pileHistorique {
	maillonHistorique* first;
	int taille;
}pileHistorique;