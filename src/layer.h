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

Layer* addEmptyLayer(Image* img);

#endif
