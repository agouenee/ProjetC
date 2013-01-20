#ifndef lut
#define lut

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

void initLUT(Lut* lutable);
//Lut* addLut(int type, Lut* previous);
Lut* addLut(int type, Lut* lutable, Layer* myLayer);
int suppLUT(Lut* appliedLut, Layer* myLayer);
void addLum(Lut* lutable, int val);
void dimLum(Lut* lutable, int val);
void greyScale(Layer* myLayer);
int sepia (Lut* lutable);
void color(Lut* lutable, int R, int V, int B);
//void setModif(Layer* myLayer, Lut* lutable);
void setModif(Layer* myLayer);
int addContrast(Lut* lutable, int param);
int dimContrast(Lut* lutable, int val);
void invert(Lut* lutable);

#endif