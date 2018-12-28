#include "DIPs.h"
#include "Image.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
/* Example of DIP */
/* make the picture color black & white */
IMAGE *BlackNWhite(IMAGE *image)
{   assert(image);
    int x, y, tmp;
    unsigned int width, height;
    height=ImageHeight(image);
    width=ImageWidth(image);
    
    unsigned char pixelR,pixelG,pixelB;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {   pixelR=GetPixelR(image,x,y);
	    
	    pixelG=GetPixelG(image,x,y);
	    pixelB=GetPixelB(image,x,y);
	    //average R,G,B values	     
            tmp = (pixelR + pixelG + pixelB) / 3;
	    SetPixelR(image, x, y,  tmp);
	    SetPixelG(image, x, y, tmp);
	    SetPixelB(image, x, y, tmp);
        }
    }

    return image;
}

/* Add edge to the image*/
IMAGE *Edge(IMAGE *image) {
   assert(image); 
  
   int             x, y, m, n, a, b;
    unsigned int height, width;
    height=ImageHeight(image);
    width=ImageWidth(image);

    unsigned char   tmpR[width][height];
    unsigned char   tmpG[width][height];
    unsigned char   tmpB[width][height];
    unsigned char pixelR,pixelG,pixelB;    
    for (y = 0; y < height; y++){
        for (x = 0; x < width; x++) {

	    pixelR=GetPixelR(image,x,y);
            pixelG=GetPixelG(image,x,y);
            pixelB=GetPixelB(image,x,y);

            tmpR[x][y] = pixelR;
            tmpG[x][y] = pixelG;
            tmpB[x][y] = pixelB;
        }
    }
    int sumR = 0;   /* sum of the intensity differences with neighbors */
    int sumG = 0;
    int sumB = 0;
    for (y = 1; y < height - 1; y++){
        for (x = 1; x < width - 1; x++){
            for (n = -1; n <= 1; n++){
                for (m = -1; m <= 1; m++) {
                    a = (x + m >= width) ? width - 1 : (x + m < 0) ? 0 : x + m;
                    b = (y + n >= height) ? height - 1 : (y + n < 0) ? 0 : y + n;
                    sumR += (tmpR[x][y] - tmpR[a][b]);
                    sumG += (tmpG[x][y] - tmpG[a][b]);
                    sumB += (tmpB[x][y] - tmpB[a][b]);
                }
            }
	    if (sumR>MAX_PIXEL){
		SetPixelR(image,x,y,MAX_PIXEL);}
	    
            if (sumG>MAX_PIXEL){
                SetPixelG(image,x,y,MAX_PIXEL);}
            if (sumB>MAX_PIXEL){
                SetPixelB(image,x,y,MAX_PIXEL);}
            if (sumR<0){
                SetPixelR(image,x,y,0);}
            if (sumG<0){
                SetPixelG(image,x,y,0);}
            if (sumB<0){
                SetPixelB(image,x,y,0);}
	    if(sumR>=0 && sumR<MAX_PIXEL){
		SetPixelR(image,x,y,(unsigned char) sumR);}
	    if(sumG>=0 && sumG<MAX_PIXEL){
                SetPixelG(image,x,y,(unsigned char) sumG);}
	    if(sumB>=0 && sumB<MAX_PIXEL){
                SetPixelB(image,x,y,(unsigned char) sumB);}






           
            sumR = sumG = sumB = 0;
        }
    }
    /* set all four borders to 0 */
    for (y = 0; y < height; y++) {
        SetPixelR(image,0,y, 0);
	SetPixelG(image, 0, y, 0);
	SetPixelB(image, 0, y, 0);
	
	SetPixelR(image, width-1, y, 0);
	SetPixelG(image, width-1, y, 0);
	SetPixelB(image, width-1, y, 0);
    }
    for (x = 0; x < width; x++) {


	SetPixelR(image,x,0, 0);
        SetPixelG(image,x, 0, 0);
        SetPixelB(image,x, 0, 0);

        SetPixelR(image, x, height-1, 0);
        SetPixelG(image, x, height-1, 0);
        SetPixelB(image, x, height-1,0);
    }

   
    return image;
}

/* Shuffle the image */
IMAGE *Shuffle(IMAGE *image)
{   
    assert(image);	
    unsigned int height,width;
    height=ImageHeight(image);
    width=ImageWidth(image);    
    int block_cnt = SHUFF_HEIGHT_DIV * SHUFF_WIDTH_DIV;
    int block_width = width/SHUFF_WIDTH_DIV;
    int block_height = height/SHUFF_HEIGHT_DIV;
    int block[SHUFF_WIDTH_DIV][SHUFF_HEIGHT_DIV];
    int i, j;
    


    srand(time(NULL));
    /* Initialize block markers to not done (-1) */
    for (i = 0; i < SHUFF_WIDTH_DIV; i++) {
        for (j = 0; j< SHUFF_HEIGHT_DIV; j++) {
            block[i][j] = -1;
        }
    }

    while (block_cnt > 0) {
        /* Generate a random pair of blocks */
        int dest_height = rand() % SHUFF_HEIGHT_DIV;
        int dest_width = rand() % SHUFF_WIDTH_DIV;
        int src_height = rand() % SHUFF_HEIGHT_DIV;
        int src_width = rand() % SHUFF_WIDTH_DIV;

        /* Check if these blocks are already swaped, if not swap blocks */
        if ((block[dest_width][dest_height] == -1) && (block[src_width][src_height] == -1)) {
            /* Swap blocks */
            for (i = 0; i < block_height; i++) {
                /* Init src and dest height offset */
                int h_dest = ((dest_height * block_height) + i) % height;
                int h_src  = ((src_height * block_height) + i) % height;
                for (j = 0; j < block_width; j++) {
                    int temp;
		    unsigned char pixelR,pixelG,pixelB;
                    /* Init src and dest width offset */
                    int w_src  = ((src_width * block_width) + j) % width;
                    int w_dest = ((dest_width * block_width) + j) % width;

		    temp=GetPixelR(image,w_dest,h_dest);
		    pixelR=GetPixelR(image,w_src,h_src);	
		    SetPixelR(image,w_dest,h_dest,pixelR);
		    SetPixelR(image,w_src,h_src,temp);


		    temp=GetPixelG(image,w_dest,h_dest);
		    pixelG=GetPixelG(image,w_src,h_src);
                    SetPixelG(image,w_dest,h_dest,pixelG);
                    SetPixelG(image,w_src,h_src,temp);

                    
			
                    

                
                    
		    temp=GetPixelB(image,w_dest,h_dest);
		    pixelB=GetPixelB(image,w_src,h_src);
                    SetPixelB(image,w_dest,h_dest,pixelB);   
                    SetPixelB(image,w_src,h_src,temp);

                
                }
            }
            /* Set marker as done */
            block[dest_width][dest_height] = 1;
            block[src_width][src_height] = 1;
            /* Decrease block count */
            block_cnt -= 2; /* Two blocks are swapped */
        }

    }
	return image;
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
