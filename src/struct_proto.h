// Structures de données
// Historique
typedef struct maillonHistorique {
	struct Layer* myLayer;
	struct maillonHistorique* next;
	int code;
}maillonHistorique;

/*
	codes
	[1] - Ajout de LUT
	[2] - Ajout de calque
*/

typedef struct pileHistorique {
	maillonHistorique* first;
	int taille;
}pileHistorique;

// Image
typedef struct Image {
    unsigned int type;
    unsigned int height;
    unsigned int width;
    unsigned int max;
    unsigned char* pixel;
} Image;

// Calque
typedef struct Layer {
	unsigned int id;
    struct Image* source;
    struct Layer* prev;
    struct Layer* next;
    float opacity;
    unsigned int mix;
    struct Lut* appliedLut;
    unsigned char* pixel;
} Layer;

// LUT
typedef struct Lut {
	int type;
	unsigned char tabR[256];
	unsigned char tabV[256];
	unsigned char tabB[256];
	struct Lut* next;
	struct Lut* prev;
}Lut;

/* ---- TYPES ----
	[1] addLum
	[2] dimLum
	[3] sepia
	[4] addContrast
	[5] dimContrast
	[6] invert
	[7] greyScale
*/


/*------------------------------------------------------------------------*/


// Prototypes de fonctions
// Historique
void initHistory(pileHistorique* pile);
int addToHistory(pileHistorique *pile, Layer* selected, int code);
maillonHistorique* goBackHistorique(pileHistorique* pile, Layer* first);

// Image
Image* openImage(char* path);
Image* createFinalImage(Layer* l);
void saveFinalImage(Image* img, char* fileName);

// Calque
Layer* addImgLayer(char* path, unsigned int id, float opacity, unsigned int mix, Layer* selected);
Layer* addEmptyLayer(unsigned int id, Layer* imgRoot, Layer* selected);
Layer* modifLayerOpacity(Layer* selected, float opacity);
Layer* modifLayerMix(Layer* selected, unsigned int mix);
Layer* modifLayer(Layer* selected);
int suppLayer(Layer* selected);

// LUT
void initLUT(Lut* lutable);
Lut* addLut(int type, Lut* lutable, Layer* myLayer);
int suppLUT(Lut* appliedLut, Layer* myLayer);
void addLum(Lut* lutable, int val);
void dimLum(Lut* lutable, int val);
void greyScale(Layer* myLayer);
int sepia (Lut* lutable);
void color(Lut* lutable, int R, int V, int B);
void setModif(Layer* myLayer);
int addContrast(Lut* lutable, int param);
int dimContrast(Lut* lutable, int val);
void invert(Lut* lutable);
