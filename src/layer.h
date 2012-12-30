#ifndef layer
#define layer

typedef struct Layer {
    Image* source;
    struct Layer* prev;
    struct Layer* next;
    float opacity;
    char add;
    char multi;
    //lut* lut;
} Layer;

Layer* addImgLayer(char* path, float opacity, char add, char multi, Layer* selected);
Layer* addEmptyLayer(Layer* imgRoot, Layer* selected);

#endif
