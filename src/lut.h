#ifndef lut
#define lut

typedef struct Lut {
	unsigned char tabR[256];
	unsigned char tabV[256];
	unsigned char tabB[256];
}Lut;

void initLUT(Lut* lutable);
void addLum(Lut* lutable, int val);
void dimLum(Lut* lutable, int val);
void setModif(Layer* myLayer, Lut* lutable);

#endif