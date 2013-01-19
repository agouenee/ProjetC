#ifndef layer
#define layer

typedef struct Layer {
	unsigned int id;
    struct Image* source;
    struct Layer* prev;
    struct Layer* next;
    float opacity;
    unsigned int mix;
    struct Lut* appliedLut;
    unsigned char* pixel; /* pixel = source->pixel, permet modification apparence calque tout en gardant valeurs pixels image originale */
} Layer;

Layer* addImgLayer(char* path, unsigned int id, float opacity, unsigned int mix, Layer* selected);
Layer* addEmptyLayer(unsigned int id, Layer* imgRoot, Layer* selected);
Layer* modifLayerOpacity(Layer* selected, float opacity);
Layer* modifLayerMix(Layer* selected, unsigned int mix);
Layer* modifLayer(Layer* selected);
int suppLayer(Layer* selected);

#endif
