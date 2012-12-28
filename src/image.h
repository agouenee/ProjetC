#ifndef image
#define image

typedef struct Image {
    unsigned int type;
    unsigned int height;
    unsigned int width;
    unsigned int max;
    unsigned char* pixel;
} Image;

Image* openImage(char* path);

#endif
