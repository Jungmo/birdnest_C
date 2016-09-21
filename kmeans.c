//
// Created by Jungmo on 9/21/16.
//
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256

int centroid[8] = {15,47,79,111,143,175,207,239};

void kmeans(FILE* image, int K, int I)
{
    __uint8_t buf[BUFSIZE];
    int count = 0;
    int i = 0;
    int j = 0;

    fseek(image,  1078,SEEK_SET);

    while(1) {

        count = fread(buf, BUFSIZE, sizeof(__uint8_t), image);
        printf("count : %d", count);
        for(i = 0; i < count; i++)
        {
            for(j = 0; j < K; j++)
            {
                printf("buf : %d, j : %d, buf-j = %d\n",buf[i],centroid[j], abs(buf[i] - centroid[j]));
            }
        }

        if(count < BUFSIZE)
        {
            break;
        }
    }
}

