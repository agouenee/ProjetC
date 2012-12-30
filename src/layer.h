#ifndef layer
#define layer

typedef struct Layer {
	unsigned int id;
    Image* source;
    struct Layer* prev;
    struct Layer* next;
    float opacity;
    unsigned int mix;
    //lut* lut;
} Layer;

Layer* addImgLayer(char* path, unsigned int id, float opacity, unsigned int mix, Layer* selected);
Layer* addEmptyLayer(unsigned int id, Layer* imgRoot, Layer* selected);
Layer* modifLayerOpacity(Layer* selected, float opacity);
Layer* modifLayerMix(Layer* selected, unsigned int mix);

#endif
