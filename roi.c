#include <stdio.h>
#include <stdint.h>

#define BUFFERSIZEROI 100


unsigned char findROI(FILE* image, int threshold)
{
    unsigned char 	i, j;
    unsigned char 	line = 0;
    unsigned char 	idx1 = 0;
    unsigned char 	idx2 = 0;
    unsigned int 	origin = ftell(image);
    uint8_t 	buf[BUFFERSIZEROI];
    unsigned int 	temp = 0;
    unsigned int 	plane[2][2] = {0,};
    unsigned int 	count = 0;
    unsigned char 	maxplace = 0;
    unsigned int 	max = 0;

    j=0;
    fseek(image, 1078, SEEK_SET);
    int read = 0;

    // count pixels which are higher than threshold in each part of image
    while(1) {
        count = fread(buf, sizeof(uint8_t), BUFFERSIZEROI, image);
        read ++;
        for(i = 0; i < count; i++)
        {
            if(buf[i] <= threshold)
            {
                temp++;
            }
        }

        idx2 = line % 2;
        //printf("idx1 : %d idx2 : %d\n", idx1, idx2);
        idx1 = 1 - (j / 100);
        plane[idx1][idx2] += temp;
        temp = 0;
        line++;
        if(line % 2 == 0)
        {
            j++;
        }

        if(count < BUFFERSIZEROI || j == 200)
        {
            break;
        }
    }

    //Find the darkest part of image
    //Quadrant
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
        {
            if(plane[i][j] >= max)
            {
                max = plane[i][j];
                maxplace = j + 2*(i);
            }
        }
    }

    temp = 0;
    int mid = 0;
    fseek(image, 1078+200*50+50, SEEK_SET);

    //mid
    for(i=0;i<100;i++)
    {
        count = fread(buf, sizeof(uint8_t), BUFFERSIZEROI, image);
        read ++;
        for(j = 0; j < count; j++)
        {
            if(buf[j] <= threshold)
            {
                temp++;
            }
        }

        mid += temp;
        temp = 0;
        fseek(image, 100, SEEK_CUR);
    }

    //return ROI
    if(max < mid)
    {
        max=mid;
        maxplace = 5;
    }
    for(i=0;i<2;i++){
        for(j=0;j<2;j++){
            printf("%5d", plane[i][j]);
        }
        printf("\n");
    }
    printf("mid : %d\n", mid);

    fseek(image, origin, SEEK_SET);

    //1~4 indicate each quadrant, 5 is middle of image (x,y) = (50,50)
    return maxplace;
}
