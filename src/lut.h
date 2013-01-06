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
void greyScale(Image* img);
void sepia (Lut* lutable, Image* img);
void color(Lut* lutable, int R, int V, int B);
void setModif(Layer* myLayer, Lut* lutable);

#endif