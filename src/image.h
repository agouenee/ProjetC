#ifndef image
#define image

typedef struct Image {
    unsigned int type;
    unsigned int height;
    unsigned int width;
    unsigned int max;
    unsigned char* pixel;
} Image;

int openImage(char* path, Image* img);

#endif
