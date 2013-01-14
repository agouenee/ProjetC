#ifndef image
#define image

typedef struct Image {
    unsigned int type;
    unsigned int height;
    unsigned int width;
    unsigned int max;
    unsigned char* pixel;
} Image;

typedef struct Layer Layer;

Image* openImage(char* path);
Image* createFinalImage(Layer* l);
void saveFinalImage(Image* img, char* fileName);

#endif
