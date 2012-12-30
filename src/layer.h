#ifndef layer
#define layer

typedef struct Layer {
	unsigned int id;
    Image* source;
    struct Layer* prev;
    struct Layer* next;
    float opacity;
    char add;
    char multi;
    //lut* lut;
} Layer;

Layer* addImgLayer(char* path, unsigned int id, float opacity, char add, char multi, Layer* selected);
Layer* addEmptyLayer(unsigned int id, Layer* imgRoot, Layer* selected);

#endif
