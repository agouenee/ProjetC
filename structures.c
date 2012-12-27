typedef struct Image {
    unsigned int type;
    unsigned int height;
    unsigned int width;
    unsigned int max;
    unsigned char* pixel;
} Image;

typedef struct Calque {
	Image* source;
	Calque* prev;
	Calque* next;
	float opacity;
	smallint add;
	smallint multi;
	lut* lut;
}Calque;

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