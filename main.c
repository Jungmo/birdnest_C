#include <stdio.h>
#include "roi.h"
#include "kmeans.h"

int main(int argc, char** argv)
{
    FILE* image;
    int roi = 0;
    image = fopen("/Users/jungmo/ClionProjects/kmeans/image.bmp", "rb");
    //roi = findROI(image, 80);
    kmeans(image,8,4);
    //printf("roi : %d", roi);

    fclose(image);
    return 0;
}